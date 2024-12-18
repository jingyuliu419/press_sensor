/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "wifi.h"
#include "atk_mw8266d.h"
#include "packet_transmission.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEMO_WIFI_SSID          "wsn"
#define DEMO_WIFI_PWD           "wsn123456"
#define DEMO_TCP_SERVER_IP      "192.168.31.101"
#define DEMO_TCP_SERVER_PORT    "8000"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint16_t scanValue[16][16]={0};
uint16_t test=1000;

void atk_mw8266d_test(void)
{
    uint8_t ret;
    char ip_buf[16];

    ret = atk_mw8266d_init(115200);
    if (ret != 0)
    {
        printf("ATK-MW8266D init failed!\r\n");
        return;
    }

    printf("Joining to AP...\r\n");
    ret  = atk_mw8266d_restore();                               /* �ָ��������� */
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    ret += atk_mw8266d_at_test();                               /* AT���� */
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    ret += atk_mw8266d_set_mode(1);                             /* Stationģʽ */
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    ret += atk_mw8266d_sw_reset();                              /* ������λ */
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    // ret += atk_mw8266d_ate_config(0);                           /* �رջ��Թ��� */
    // printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    ret += atk_mw8266d_join_ap(DEMO_WIFI_SSID, DEMO_WIFI_PWD);  /* ����WIFI */
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    // ret += atk_mw8266d_get_ip(ip_buf);                          /* ��ȡIP��ַ */
    // if (ret != 0)
    // {
    //     printf("Error to join ap!\r\n");
    // }
    atk_mw8266d_send_at_cmd("AT+CIPMUX=0", "OK", 10000);
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    /* ����TCP������ */
    ret = atk_mw8266d_connect_tcp_server(DEMO_TCP_SERVER_IP, DEMO_TCP_SERVER_PORT);
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);
    if (ret != 0)
    {
        printf("Error to connect tcp server!\r\n");
    }
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);

    atk_mw8266d_send_at_cmd("AT+CIPMODE=1", "OK", 10000);
    atk_mw8266d_send_at_cmd("AT+CIPSEND", "OK", 10000);
    atk_mw8266d_uart_rx_restart();
    printf("func:%s line%d\r\n", __FUNCTION__, __LINE__);

    atk_mw8266d_uart_printf("This ATK-MW8266D TCP Connect Test.\r\n");

    printf("IP: %s\r\n", ip_buf);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	HAL_NVIC_SetPriority(SysTick_IRQn,0,0);

	MX_GPIO_Init();
	MX_DMA_Init();

	MX_ADC1_Init();
	MX_USART1_UART_Init();
	MX_TIM2_Init();

	printf("built -- %s %s:%\r\n", __DATE__, __TIME__);

	HAL_ADCEx_Calibration_Start(&hadc1);
	setCD4076Channel(0);
	HAL_Delay(5);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue,16);
	HAL_GPIO_WritePin(GPIOB,LED1_Pin,0);
	// packet_test();
	atk_mw8266d_test();
	atk_mw8266d_uart_printf("This ATK-MW8266D TCP Connect Test.\r\n");

  HAL_TIM_Base_Start_IT(&htim2);

	while(1){};
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
