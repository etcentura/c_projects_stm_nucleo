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
#define BME280_ADDR        (0x76 << 1)  // Адрес 0x76, сдвинутый для I2C
// Если не работает, попробуй (0x77 << 1)

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
////////////////////////////////////////////////////////////////

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


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  //Setting common RCC registers
  init_RCC(RCC);

  set_RCC_CFGR_field  (RCC, RCC_CFGR_SW_PLL);
  set_RCC_CFGR_field  (RCC, RCC_CFGR_PLLMULL9);
  set_RCC_CFGR_field  (RCC, RCC_CFGR_MCO_PLLCLK_DIV2);
  
  set_RCC_CR_field    (RCC, RCC_CR_PLLON);

  while(1)
  {
    int captured_sws_value = get_RCC_CFGR_field(RCC, RCC_CFGR_SWS_Pos, RCC_CFGR_SWS_Msk);
    if(captured_sws_value == 2) break;
  }

  // //Resetting apb2 domain
  set_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPCRST);
  set_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPBRST);
  set_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_AFIORST);

  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPCRST_Msk);
  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPBRST_Msk);
  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_AFIORST_Msk);

  // //Resetting apb1 domain
  set_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_USART3RST);
  set_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_I2C1RST);
  clear_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_USART3RST_Msk);
  clear_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_I2C1RST_Msk);

  // //Enable apb2 domain
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_IOPCEN);
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_IOPBEN);
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_AFIOEN);

  // //Enable apb1 domain
  set_RCC_APB1ENR_field(RCC, RCC_APB1ENR_USART3EN);
  set_RCC_APB1ENR_field(RCC, RCC_APB1ENR_I2C1EN);

  // //Setting up pc10 and 11 for usart3
  // // For instance, on NUCLEO-F103RB it is possible to use USART3 available on PC10 (TX) and PC11 (RX).
  // // Two flying wires need to be connected as follows:
  // // PC10 (USART3_TX) available on CN7 pin 1 to CN3 pin RX
  // // PC11 (USART3_RX) available on CN7 pin 2 to CN3 pin TX
  // // Use GPIOC to drive usart, also remap gpio using AFIO registers
  set_AFIO_MAPR_field(AFIO, AFIO_MAPR_USART3_REMAP_0);

  clear_GPIO_CRH_field(GPIOC, GPIO_CRH_CNF10_Msk);
  set_GPIO_CRH_field(GPIOC, GPIO_CRH_CNF10_1);
  set_GPIO_CRH_field(GPIOC, GPIO_CRH_MODE10);
  
  // //Setting up usart3
  set_USART_CR1_field(USART3, USART_CR1_UE);
  set_USART_CR1_field(USART3, USART_CR1_TE);
  USART3->BRR = 3750;

  // while (1)
  // {
  //   while(get_USART_SR_field(USART3, USART_SR_TXE_Pos, USART_SR_TXE_Msk) == 0){}
  //   set_USART_DR_field(USART3, 0xAA);
  // }

  I2C1_Init();

  if (!BME280_Init()) {
      // Ошибка: сенсор не найден или не BME280
      while (1);
  }

  BME280_Data data;

  while (1) {
        if (BME280_Read(&data)) {
            // data.temperature, data.pressure, data.humidity
            volatile float t = data.temperature;
            volatile float p = data.pressure;
            volatile float h = data.humidity;
            (void)t; (void)p; (void)h;
        }
        for (volatile unsigned int i = 0; i < 1000000; i++);
    }
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
