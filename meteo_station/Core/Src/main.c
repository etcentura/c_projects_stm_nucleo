/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "main.h"
#include "stm32f103xb.h"
#include <math.h>

// Custom functions and defines
#include "custom_rcc_functions.h"
#include "custom_gpio_functions.h"
#include "custom_usart_functions.h"
#include "custom_afio_functions.h"

////////////////////////////////////////////////////////////////
// --- BH1750: КОНСТАНТЫ И ПРОТОТИПЫ ---
#define BH1750_ADDR        (0x23 << 1)  // Адрес 0x23, сдвинутый для I2C
// Если не работает, попробуй (0x5C << 1)

// Команды BH1750 (из даташита)
#define BH1750_POWER_ON    0x01
#define BH1750_CONT_HIRES  0x10  // Непрерывный режим, высокое разрешение (1 lx)
#define BH1750_ONE_HIRES   0x20  // Однократный режим, высокое разрешение (1 lx)
#define BH1750_CONT_HIRES2 0x11  // Непрерывный режим, 0.5 lx
#define BH1750_ONE_HIRES2  0x21  // Однократный режим, 0.5 lx
#define BH1750_CONT_LORES  0x13  // Непрерывный режим, низкое разрешение (4 lx)
#define BH1750_ONE_LORES   0x23  // Однократный режим, низкое разрешение (4 lx)

// Прототипы
void I2C2_Init(void);
uint8_t BH1750_WriteCmd(uint8_t cmd);
uint8_t BH1750_ReadRaw(uint16_t *raw);
float BH1750_ReadLux(void);
void I2C2_Recovery(void);
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// --- BME280: КОНСТАНТЫ И ПРОТОТИПЫ ---
#define BME280_ADDR        (0x76 << 1)  // Адрес 0x76, сдвинутый для I2C

// Регистры BME280
#define BME280_REG_CALIB00  0x88
#define BME280_REG_CALIB26  0xE1
#define BME280_REG_CHIPID   0xD0
#define BME280_REG_RESET    0xE0
#define BME280_REG_CTRL_HUM 0xF2
#define BME280_REG_STATUS   0xF3
#define BME280_REG_CTRL_MEAS 0xF4
#define BME280_REG_CONFIG   0xF5
#define BME280_REG_DATA     0xF7  // 0xF7..0xFE (8 байт)

// Калибровочные коэффициенты
static uint16_t dig_T1;
static int16_t  dig_T2, dig_T3;
static uint16_t dig_P1;
static int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
static uint8_t  dig_H1, dig_H3;
static int16_t  dig_H2;
static int16_t  dig_H4, dig_H5;
static int8_t   dig_H6;

// Глобальные переменные для t_fine (нужен для компенсации давления)
static int32_t t_fine;

typedef struct {
    float temperature; // °C
    float pressure;    // Pa
    float humidity;    // %
} BME280_Data;

void SystemClock_Config(void);
void I2C1_Init(void);
static uint8_t I2C_WaitFlag(unsigned int flag, unsigned int timeout);
uint8_t BME280_WriteReg(uint8_t reg, uint8_t value);
uint8_t BME280_ReadRegs(uint8_t reg, uint8_t *buf, uint8_t len);
uint8_t BME280_Init(void);
static int32_t BME280_CompensateT(int32_t adc_T);
static unsigned int BME280_CompensateP(int32_t adc_P);
static unsigned int BME280_CompensateH(int32_t adc_H);
uint8_t BME280_Read(BME280_Data *out);
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// --- MQ-135: КОНСТАНТЫ И ПРОТОТИПЫ ---
void ADC1_Init_PA0(void);
uint16_t ADC1_Read_PA0(void);
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// --- USART3: КОНСТАНТЫ И ПРОТОТИПЫ ---
void USART2_SendChar(char c);
void USART2_SendString(const char *s);
void USART2_SendInt(int32_t value);
void USART2_SendFloat2(float value);
void USART2_SendNewline(void);
////////////////////////////////////////////////////////////////



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  //Setting common RCC registers
  init_RCC(RCC);
//   set_RCC_CFGR_field  (RCC, RCC_CFGR_SW_PLL);
//   set_RCC_CFGR_field  (RCC, RCC_CFGR_PLLMULL9);
//   set_RCC_CFGR_field  (RCC, RCC_CFGR_MCO_PLLCLK_DIV2);
  
//   set_RCC_CR_field    (RCC, RCC_CR_PLLON);

  // 1. Настраиваем PLL, пока он выключен
  RCC->CFGR &= ~RCC_CFGR_PLLMULL;
  RCC->CFGR |= RCC_CFGR_PLLMULL9;      // x9
  RCC->CFGR &= ~RCC_CFGR_PLLSRC;       // PLLSRC = 0 → HSI/2 = 4 МГц
  // (если хотите HSE: RCC->CFGR |= RCC_CFGR_PLLSRC;)

  // 2. Включаем PLL
  RCC->CR |= RCC_CR_PLLON;
  while (!(RCC->CR & RCC_CR_PLLRDY));

  // 3. Переключаем SYSCLK на PLL
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  // 4. Делители
  RCC->CFGR &= ~RCC_CFGR_PPRE1;
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;    // APB1 = SYSCLK / 2

  while(1)
  {
    int captured_sws_value = get_RCC_CFGR_field(RCC, RCC_CFGR_SWS_Pos, RCC_CFGR_SWS_Msk);
    if(captured_sws_value == 2) break;
  }

  RCC->CFGR &= ~RCC_CFGR_PPRE1;
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;   // APB1 = 36 МГц

  // //Resetting apb2 domain
  set_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPARST);
  set_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPBRST);
  set_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_AFIORST);
  
  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPARST_Msk);
  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPBRST_Msk);
  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_AFIORST_Msk);

  // //Resetting apb1 domain
  set_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_USART2RST);
  set_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_I2C1RST);
  set_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_I2C2RST);
  clear_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_USART2RST_Msk);
  clear_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_I2C1RST_Msk);
  clear_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_I2C2RST_Msk);

  // //Enable apb2 domain
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_IOPAEN);
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_IOPBEN);
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_AFIOEN);

  // //Enable apb1 domain
  set_RCC_APB1ENR_field(RCC, RCC_APB1ENR_USART2EN);
  set_RCC_APB1ENR_field(RCC, RCC_APB1ENR_I2C1EN);
  set_RCC_APB1ENR_field(RCC, RCC_APB1ENR_I2C2EN);


  // //Setting up usart2
  // PA2 tx
  // PA3 rx
  //PA2
  GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
  GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_MODE2_0 | GPIO_CRL_CNF2_1);
  //PA3
  GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
  GPIOA->CRL |= GPIO_CRL_CNF3_0;

  USART2->BRR = 1875; // 9600 бод при APB1 = 18 МГц
  USART2->CR1 &= ~(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS); // 8 бит, без чётности
  USART2->CR2 &= ~USART_CR2_STOP; // 1 стоп-бит

  set_USART_CR1_field(USART2, USART_CR1_UE); // Включаем USART
  set_USART_CR1_field(USART2, USART_CR1_TE); // Включаем передатчик
  set_USART_CR1_field(USART2, USART_CR1_RE); // Включаем приёмник

  ////////////////////////////////////////////////////////////////////////////////
  //I2C example for bmh1750
  //   I2C2_Init();
  //   while (1) {
  //     float lux = BH1750_ReadLux();
  //     if (lux >= 0) {
  //         volatile float l = lux;
  //         (void)l;
  //     }
  
  //     for (volatile unsigned int i = 0; i < 3000000; i++);
  //   }
  ////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////
  //I2C example for bme280
  // I2C1_Init();

  // if (!BME280_Init()) {
  //     // Ошибка: сенсор не найден или не BME280
  //     while (1);
  // }

  // BME280_Data data;

  // while (1) {
  //       if (BME280_Read(&data)) {
  //           // data.temperature, data.pressure, data.humidity
  //           volatile float t = data.temperature;
  //           volatile float p = data.pressure;
  //           volatile float h = data.humidity;
  //           (void)t; (void)p; (void)h;
  //       }
  //       for (volatile unsigned int i = 0; i < 1000000; i++);
  //   }
  ////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////
  //ADC example for MQ-135 - использовать пин PA0
  //   ADC1_Init_PA0();
  
  //   while (1) {
  //       uint16_t adc_raw = ADC1_Read_PA0();
  //       // Пересчёт в напряжение (опционально, если Vref = 3.3V)
  //       float voltage = (adc_raw * 3.3f) / 4095.0f;
        
  //       // adc_raw и voltage можно отправить по USART3 или просто смотреть в отладчике
  //       volatile uint16_t debug_raw = adc_raw;
  //       (void)debug_raw;
        
  //       for (volatile int i = 0; i < 1000000; i++); // Пауза
  //   }
  ////////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////////////////////////////
  //All in one sensors
    I2C2_Init();        // bmh1750
    I2C1_Init();        // bme280
    ADC1_Init_PA0();    // MQ-135

    if (!BME280_Init()) {
        // Ошибка: сенсор не найден или не BME280
        while (1);
    }

    BME280_Data data;

    while (1) {
        //Declaring variables for the sensors
        volatile float l; //lux

        volatile float t; //temperature
        volatile float p; //pressure
        volatile float h; //humidity

        uint16_t adc_raw; //ADC read from MQ-135
        volatile float voltage; //voltage from mq-135
        volatile uint16_t debug_raw;


        float lux = BH1750_ReadLux();
        if (lux >= 0) {
            l = lux;
            (void)l;
        }
    
        for (volatile unsigned int i = 0; i < 3000000; i++);

        if (BME280_Read(&data)) {
                // data.temperature, data.pressure, data.humidity
                t = data.temperature;
                p = data.pressure;
                h = data.humidity;
                (void)t; (void)p; (void)h;
            }
        for (volatile unsigned int j = 0; j < 1000000; j++);

        adc_raw = ADC1_Read_PA0();

        voltage = (adc_raw * 3.3f) / 4095.0f;

        debug_raw = adc_raw;
        (void)debug_raw;
        
        for (volatile int k = 0; k < 1000000; k++); // Пауза

        USART2_SendString("LUX");
        USART2_SendNewline();
        USART2_SendInt((int32_t)lux);
        USART2_SendNewline();

        USART2_SendString("TEMP");
        USART2_SendNewline();
        USART2_SendFloat2(data.temperature);
        USART2_SendNewline();

        USART2_SendString("HUM");
        USART2_SendNewline();
        USART2_SendFloat2(data.humidity);
        USART2_SendNewline();

        USART2_SendString("PRES");           // вы упомянули давление — добавил
        USART2_SendNewline();
        USART2_SendFloat2(data.pressure / 100.0f); // Па -> гПа (мбар)
        USART2_SendNewline();

        USART2_SendString("VOLT");
        USART2_SendNewline();
        USART2_SendFloat2(voltage);
        USART2_SendNewline();

        USART2_SendNewline(); // пустая строка-разделитель между блоками

        for (volatile int ii = 0; ii < 1000000; ii++); // Пауза
    }

  ////////////////////////////////////////////////////////////////////////////////
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

////////////////////////////////////////////////////////////////
// --- BH1750: ФУНКЦИИ ---
// BH1750	  STM32F103RB	  Примечание
// VCC	    3.3V	        Питание
// GND	    GND	          Земля
// SCL	    PB10	        Тактирование I2C2
// SDA	    PB11	        Данные I2C2
void I2C2_Init(void)
{
    // Настройка PB10 (SCL) и PB11 (SDA) как AF Open-Drain, 50 MHz
    // Очищаем биты для PB10 и PB11 в CRH (так как это старшие пины)
    GPIOB->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10 | GPIO_CRH_CNF11 | GPIO_CRH_MODE11);
    // Устанавливаем: Output mode 50MHz (MODE=11), AF Open-Drain (CNF=11)
    GPIOB->CRH |= (GPIO_CRH_MODE10_1 | GPIO_CRH_MODE10_0 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF10_0);
    GPIOB->CRH |= (GPIO_CRH_MODE11_1 | GPIO_CRH_MODE11_0 | GPIO_CRH_CNF11_1 | GPIO_CRH_CNF11_0);

    // Сброс I2C2
    I2C2->CR1 |= I2C_CR1_SWRST;
    I2C2->CR1 &= ~I2C_CR1_SWRST;

    // Настройка (APB1 = 36 МГц, как у тебя в проекте)
    I2C2->CR2 = 36;      // Частота APB1 в МГц
    I2C2->CCR = 180;     // 100 кГц (36MHz / (2*100kHz))
    I2C2->TRISE = 37;    // (36 * 1000ns / 1000) + 1

    // Включение
    I2C2->CR1 |= I2C_CR1_PE;
}

uint8_t BH1750_WriteCmd(uint8_t cmd)
{
    unsigned int timeout = 100000;

    // START
    I2C2->CR1 |= I2C_CR1_START;
    while (!(I2C2->SR1 & I2C_SR1_SB)) { if (--timeout == 0) return 0; }

    // Адрес + W
    I2C2->DR = BH1750_ADDR;
    while (!(I2C2->SR1 & I2C_SR1_ADDR)) { if (--timeout == 0) return 0; }
    (void)I2C2->SR1; (void)I2C2->SR2; // Очистка ADDR

    // Команда
    I2C2->DR = cmd;
    while (!(I2C2->SR1 & I2C_SR1_TXE)) { if (--timeout == 0) return 0; }

    // STOP
    I2C2->CR1 |= I2C_CR1_STOP;
    return 1;
}

uint8_t BH1750_ReadRaw(uint16_t *raw)
{
    unsigned int timeout = 100000;
    uint8_t buf[2];

    // START
    I2C2->CR1 |= I2C_CR1_START;
    while (!(I2C2->SR1 & I2C_SR1_SB)) { if (--timeout == 0) return 0; }

    // Адрес + R
    I2C2->DR = BH1750_ADDR | 1;
    while (!(I2C2->SR1 & I2C_SR1_ADDR)) { if (--timeout == 0) return 0; }

    // Очистка ADDR
    (void)I2C2->SR1; (void)I2C2->SR2;

    // Чтение 2 байт (MSB first)
    // Первый байт - ACK
    I2C2->CR1 |= I2C_CR1_ACK;
    while (!(I2C2->SR1 & I2C_SR1_RXNE)) { if (--timeout == 0) return 0; }
    buf[0] = I2C2->DR;

    // Второй байт - NACK + STOP
    I2C2->CR1 &= ~I2C_CR1_ACK;
    I2C2->CR1 |= I2C_CR1_STOP;
    while (!(I2C2->SR1 & I2C_SR1_RXNE)) { if (--timeout == 0) return 0; }
    buf[1] = I2C2->DR;

    *raw = ((uint16_t)buf[0] << 8) | buf[1];
    return 1;
}

float BH1750_ReadLux(void)
{
    uint16_t raw = 0;

    // 1. Включаем питание (если ещё не включён)
    // BH1750_WriteCmd(BH1750_POWER_ON);

    if (!BH1750_WriteCmd(BH1750_POWER_ON)) {
        I2C2_Recovery(); // <-- Восстановление
        return -1.0f;
    }

    // 2. Запускаем однократное измерение в режиме высокого разрешения (1 lx)
    // BH1750_WriteCmd(BH1750_ONE_HIRES);
    
    if (!BH1750_WriteCmd(BH1750_ONE_HIRES)) {
        I2C2_Recovery(); // <-- Восстановление
        return -1.0f;
    }

    // 3. Ждём время интеграции. Для режима H-Res это ~120 мс, с запасом подождём 180 мс.
    //    Используем простой цикл, если нет SysTick задержки.
    for (volatile unsigned int i = 0; i < 180000; i++); 

    // 4. Читаем результат
    // if (!BH1750_ReadRaw(&raw)) return -1.0f; // Ошибка

    if (!BH1750_ReadRaw(&raw)) {
        I2C2_Recovery(); // <-- Восстановление
        return -1.0f;
    }

    // 5. Пересчёт в люксы: lux = raw / 1.2
    //    (Для режима H-Res2 (0.5 lx) нужно было бы raw / 1.2 / 2)
    return (float)raw / 1.2f;
}

void I2C2_Recovery(void)
{
    // 1. Выключаем периферию
    I2C2->CR1 &= ~I2C_CR1_PE;
    for (volatile int i = 0; i < 100; i++); // Небольшая задержка

    // 2. Программный сброс (SWRST)
    I2C2->CR1 |= I2C_CR1_SWRST;
    for (volatile int i = 0; i < 100; i++);
    I2C2->CR1 &= ~I2C_CR1_SWRST;

    // 3. Заново настраиваем (как в I2C2_Init)
    I2C2->CR2 = 36;
    I2C2->CCR = 180;
    I2C2->TRISE = 37;

    // 4. Включаем обратно
    I2C2->CR1 |= I2C_CR1_PE;
}
////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
// --- BME280: ФУНКЦИИ ---

// VCC (или 3.3V): Подключить к пину 3.3V на плате.

// GND: Подключить к GND на STM32.

// SCL (Serial Clock): Подключить к пину PB6 на STM32.

// SDA (Serial Data): Подключить к пину PB7 на STM32.

void I2C1_Init(void)
{
  //Clearing up bits for pb6(scl) and pb7(sda)
  GPIOB->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6 | GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
  //Setting output mode 50 MHZ(mode=11) af opendrain(cnf11)
  GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF6_0);
  GPIOB->CRL |= (GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0 | GPIO_CRL_CNF7_1 | GPIO_CRL_CNF7_0);

  I2C1->CR1 |= I2C_CR1_SWRST;
  I2C1->CR1 &= ~I2C_CR1_SWRST;

  I2C1->CR2 = 36; // APB1 = 36 MHz
  I2C1->CCR = 180; // 100 kHz
  I2C1->TRISE = 37; // (36 * 1000ns / 1000) + 1
  I2C1->CR1 |= I2C_CR1_PE;
}

static uint8_t I2C_WaitFlag(unsigned int flag, unsigned int timeout)
{
    while (!(I2C1->SR1 & flag)) {
        if (--timeout == 0) return 0;
    }
    return 1;
}

// Запись одного байта в регистр
uint8_t BME280_WriteReg(uint8_t reg, uint8_t value)
{
    unsigned int timeout = 100000;

    // START
    I2C1->CR1 |= I2C_CR1_START;
    if (!I2C_WaitFlag(I2C_SR1_SB, timeout)) return 0;

    // Адрес + W
    I2C1->DR = BME280_ADDR;
    if (!I2C_WaitFlag(I2C_SR1_ADDR, timeout)) return 0;
    (void)I2C1->SR1; (void)I2C1->SR2; // Очистка ADDR

    // Регистр
    I2C1->DR = reg;
    if (!I2C_WaitFlag(I2C_SR1_TXE, timeout)) return 0;

    // Данные
    I2C1->DR = value;
    if (!I2C_WaitFlag(I2C_SR1_TXE, timeout)) return 0;

    // STOP
    I2C1->CR1 |= I2C_CR1_STOP;
    return 1;
}

// Чтение массива байт из регистра
uint8_t BME280_ReadRegs(uint8_t reg, uint8_t *buf, uint8_t len)
{
    unsigned int timeout = 100000;

    // START
    I2C1->CR1 |= I2C_CR1_START;
    if (!I2C_WaitFlag(I2C_SR1_SB, timeout)) return 0;

    // Адрес + W
    I2C1->DR = BME280_ADDR;
    if (!I2C_WaitFlag(I2C_SR1_ADDR, timeout)) return 0;
    (void)I2C1->SR1; (void)I2C1->SR2;

    // Регистр
    I2C1->DR = reg;
    if (!I2C_WaitFlag(I2C_SR1_TXE, timeout)) return 0;

    // Повторный START
    I2C1->CR1 |= I2C_CR1_START;
    if (!I2C_WaitFlag(I2C_SR1_SB, timeout)) return 0;

    // Адрес + R
    I2C1->DR = BME280_ADDR | 1;
    if (!I2C_WaitFlag(I2C_SR1_ADDR, timeout)) return 0;

    // Очистка ADDR
    (void)I2C1->SR1; (void)I2C1->SR2;

    // Чтение
    for (uint8_t i = 0; i < len; i++) {
        if (i == len - 1) {
            // Последний байт - NACK + STOP
            I2C1->CR1 &= ~I2C_CR1_ACK;
            I2C1->CR1 |= I2C_CR1_STOP;
        } else {
            I2C1->CR1 |= I2C_CR1_ACK;
        }
        if (!I2C_WaitFlag(I2C_SR1_RXNE, timeout)) return 0;
        buf[i] = I2C1->DR;
    }

    return 1;
}

uint8_t BME280_Init(void)
{
    uint8_t chip_id = 0;

    // 1. Проверка Chip ID
    if (!BME280_ReadRegs(BME280_REG_CHIPID, &chip_id, 1)) return 0;
    if (chip_id != 0x60) return 0; // 0x60 - BME280, 0x58 - BMP280 (нет влажности)

    // 2. Сброс
    if (!BME280_WriteReg(BME280_REG_RESET, 0xB6)) return 0;
    for (volatile unsigned int i = 0; i < 100000; i++); // Задержка после сброса

    // 3. Чтение калибровочных коэффициентов
    uint8_t calib[26];
    if (!BME280_ReadRegs(BME280_REG_CALIB00, calib, 24)) return 0;
    
    dig_T1 = (uint16_t)(calib[1] << 8 | calib[0]);
    dig_T2 = (int16_t) (calib[3] << 8 | calib[2]);
    dig_T3 = (int16_t) (calib[5] << 8 | calib[4]);
    dig_P1 = (uint16_t)(calib[7] << 8 | calib[6]);
    dig_P2 = (int16_t) (calib[9] << 8 | calib[8]);
    dig_P3 = (int16_t) (calib[11] << 8 | calib[10]);
    dig_P4 = (int16_t) (calib[13] << 8 | calib[12]);
    dig_P5 = (int16_t) (calib[15] << 8 | calib[14]);
    dig_P6 = (int16_t) (calib[17] << 8 | calib[16]);
    dig_P7 = (int16_t) (calib[19] << 8 | calib[18]);
    dig_P8 = (int16_t) (calib[21] << 8 | calib[20]);
    dig_P9 = (int16_t) (calib[23] << 8 | calib[22]);
    dig_H1 = calib[24];

    // Чтение калибровки влажности (0xE1..0xE7)
    uint8_t calib_h[7];
    if (!BME280_ReadRegs(BME280_REG_CALIB26, calib_h, 7)) return 0;
    
    dig_H2 = (int16_t) (calib_h[1] << 8 | calib_h[0]);
    dig_H3 = calib_h[2];
    dig_H4 = (int16_t) ((calib_h[3] << 4) | (calib_h[4] & 0x0F));
    dig_H5 = (int16_t) ((calib_h[5] << 4) | (calib_h[4] >> 4));
    dig_H6 = (int8_t)  calib_h[6];

    // 4. Настройка измерений
    // ctrl_hum: x1 влажность (перед ctrl_meas!)
    if (!BME280_WriteReg(BME280_REG_CTRL_HUM, 0x01)) return 0;
    // config: standby 0.5ms, фильтр off, spi off
    if (!BME280_WriteReg(BME280_REG_CONFIG, 0x00)) return 0;
    // ctrl_meas: x1 temp, x1 press, Normal Mode
    if (!BME280_WriteReg(BME280_REG_CTRL_MEAS, 0x27)) return 0;

    return 1;
}

static int32_t BME280_CompensateT(int32_t adc_T)
{
    int32_t var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    int32_t var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    return (t_fine * 5 + 128) >> 8; // Температура в 0.01 °C
}

static unsigned int BME280_CompensateP(int32_t adc_P)
{
    int64_t var1 = ((int64_t)t_fine) - 128000;
    int64_t var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;

    if (var1 == 0) return 0;
    int64_t p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return (unsigned int)p; // Давление в Q24.8 Па
}

static unsigned int BME280_CompensateH(int32_t adc_H)
{
    int32_t v = t_fine - 76800;
    v = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v)) + 16384) >> 15) *
         (((((((v * ((int32_t)dig_H6)) >> 10) * (((v * ((int32_t)dig_H3)) >> 11) + 32768)) >> 10) + 2097152) *
         ((int32_t)dig_H2) + 8192) >> 14));
    v = v - (((((v >> 15) * (v >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4);
    if (v < 0) v = 0;
    if (v > 419430400) v = 419430400;
    return (unsigned int)(v >> 12); // Влажность в Q22.10 (0..100% * 1024)
}

uint8_t BME280_Read(BME280_Data *out)
{
    uint8_t raw[8];
    if (!BME280_ReadRegs(BME280_REG_DATA, raw, 8)) return 0;

    int32_t adc_P = (int32_t)(((unsigned int)raw[0] << 12) | ((unsigned int)raw[1] << 4) | (raw[2] >> 4));
    int32_t adc_T = (int32_t)(((unsigned int)raw[3] << 12) | ((unsigned int)raw[4] << 4) | (raw[5] >> 4));
    int32_t adc_H = (int32_t)(((unsigned int)raw[6] << 8) | raw[7]);

    int32_t T = BME280_CompensateT(adc_T);
    unsigned int P = BME280_CompensateP(adc_P);
    unsigned int H = BME280_CompensateH(adc_H);

    out->temperature = T / 100.0f;
    out->pressure    = P / 256.0f;       // Па
    out->humidity    = H / 1024.0f;      // %
    return 1;
}
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// --- MQ-135: ФУНКЦИИ ---
// PA0 for analog input
void ADC1_Init_PA0(void)
{
    // 0. Включение тактирования, настройка ноги
    set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_ADC1EN);
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);

    // 1. Делитель частоты ADC: PCLK2/6
    RCC->CFGR &= ~RCC_CFGR_ADCPRE;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    // 2. Включаем ADC1
    ADC1->CR2 |= ADC_CR2_ADON;
    for (volatile int i = 0; i < 100; i++);

    // 3. Калибровка
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);

    // 4. Настройка канала 0
    ADC1->CR2 &= ~ADC_CR2_CONT; // Одиночное преобразование
    ADC1->SQR1 &= ~ADC_SQR1_L;  // Длина последовательности = 1
    ADC1->SQR3 = 0;             // Канал 0 (PA0)

    // 5. Время выборки
    ADC1->SMPR2 |= ADC_SMPR2_SMP0;

    // 6. КЛЮЧЕВОЕ ИСПРАВЛЕНИЕ: разрешить внешний триггер и выбрать SWSTART
    ADC1->CR2 |= ADC_CR2_EXTTRIG;             // Сначала разрешить внешний триггер
    ADC1->CR2 &= ~ADC_CR2_EXTSEL;
    ADC1->CR2 |= (0x7 << ADC_CR2_EXTSEL_Pos); // Затем выбрать SWSTART (0b111)
}

uint16_t ADC1_Read_PA0(void)
{
    // Запуск преобразования
    ADC1->CR2 |= ADC_CR2_SWSTART;
    
    // Ждём окончания (флаг EOC)
    while (!(ADC1->SR & ADC_SR_EOC));
    
    // Возвращаем результат (12 бит, 0..4095)
    return ADC1->DR;
}
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
// --- USART3: ФУНКЦИИ ---
void USART2_SendChar(char c)
{
    while (!(USART2->SR & USART_SR_TXE)); // Ждём, пока освободится передающий регистр
    USART2->DR = (uint8_t)c;
}

void USART2_SendString(const char *s)
{
    while (*s) {
        USART2_SendChar(*s++);
    }
}

// Отправка целого числа (например, lux)
void USART2_SendInt(int32_t value)
{
    char buf[12];
    int i = 0;
    uint8_t negative = 0;

    if (value < 0) {
        negative = 1;
        value = -value;
    }

    if (value == 0) {
        USART2_SendChar('0');
        return;
    }

    while (value > 0) {
        buf[i++] = '0' + (value % 10);
        value /= 10;
    }

    if (negative) USART2_SendChar('-');

    while (i > 0) {
        USART2_SendChar(buf[--i]);
    }
}

// Отправка float с двумя знаками после запятой (например, 28.50)
void USART2_SendFloat2(float value)
{
    // Обработка отрицательных
    if (value < 0) {
        USART2_SendChar('-');
        value = -value;
    }

    // Целая часть
    int32_t int_part = (int32_t)value;
    USART2_SendInt(int_part);

    USART2_SendChar('.');

    // Дробная часть: округляем до 2 знаков
    int32_t frac = (int32_t)((value - int_part) * 100.0f + 0.5f);
    if (frac >= 100) frac = 99; // защита от 0.999 -> 1.00

    if (frac < 10) USART2_SendChar('0'); // ведущий ноль
    USART2_SendInt(frac);
}

void USART2_SendNewline(void)
{
    USART2_SendChar('\r');
    USART2_SendChar('\n');
}
////////////////////////////////////////////////////////////////


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

