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

// Custom functions and defines
#include "custom_rcc_functions.h"
#include "custom_gpio_functions.h"
#include "custom_usart_functions.h"
#include "custom_afio_functions.h"


void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  //Setting common RCC registers
  init_RCC(RCC);
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
  set_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_AFIORST);

  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_IOPCRST_Msk);
  clear_RCC_APB2RSTR_field(RCC, RCC_APB2RSTR_AFIORST_Msk);

  // //Resetting apb1 domain
  set_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_USART3RST);
  clear_RCC_APB1RSTR_field(RCC, RCC_APB1RSTR_USART3RST_Msk);

  // //Enable apb2 domain
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_IOPCEN);
  set_RCC_APB2ENR_field(RCC, RCC_APB2ENR_AFIOEN);

  // //Enable apb1 domain
  set_RCC_APB1ENR_field(RCC, RCC_APB1ENR_USART3EN);

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

  while (1)
  {
    while(get_USART_SR_field(USART3, USART_SR_TXE_Pos, USART_SR_TXE_Msk) == 0){}
    set_USART_DR_field(USART3, 0xAA);
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

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
