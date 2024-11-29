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
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	
	//??????SysTick_IRQn?????
	HAL_NVIC_SetPriority(SysTick_IRQn,0,0);

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  
  /* USER CODE BEGIN 2 */
	
//	init_wifi_STA(); //?????WIFI??�???? STA??
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_ADCEx_Calibration_Start(&hadc1);
	setCD4076Channel(0); //?????????????????
	HAL_Delay(5);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue,16);
	HAL_GPIO_WritePin(GPIOB,LED1_Pin,0);
	//HAL_TIM_Base_Start_IT(&htim2);
	HAL_UART_Receive_IT(&huart3,&uart3recvBuf,1);
	
uint16_t adcValue2[16];
uint16_t adcValue3[16];
uint16_t adcValue4[16];
uint16_t adcValue5[16];
// while(1)
// {}
//setCD4076Channel(15);
while(1)
{
			printf("*************************************************\r\n");
			for(int i=0;i<16;++i)//??
			{
				setCD4076Channel(i);
				adcValue2[15-1]=ADC_Read(ADC_CHANNEL_0);
				adcValue2[13-1]=ADC_Read(ADC_CHANNEL_1);
				adcValue2[11-1]=ADC_Read(ADC_CHANNEL_2);
				adcValue2[9-1]=ADC_Read(ADC_CHANNEL_3);
				adcValue2[7-1]=ADC_Read(ADC_CHANNEL_4);
				adcValue2[5-1]=ADC_Read(ADC_CHANNEL_5);
				adcValue2[3-1]=ADC_Read(ADC_CHANNEL_6);
				adcValue2[1-1]=ADC_Read(ADC_CHANNEL_7);
				adcValue2[2-1]=ADC_Read(ADC_CHANNEL_8);
				adcValue2[4-1]=ADC_Read(ADC_CHANNEL_9);
				adcValue2[6-1]=ADC_Read(ADC_CHANNEL_10);
				adcValue2[8-1]=ADC_Read(ADC_CHANNEL_11);
				adcValue2[10-1]=ADC_Read(ADC_CHANNEL_12);
				adcValue2[12-1]=ADC_Read(ADC_CHANNEL_13);
				adcValue2[14-1]=ADC_Read(ADC_CHANNEL_14);
				adcValue2[16-1]=ADC_Read(ADC_CHANNEL_15);
	
				uint16_t temp;
				for(int j=0;j<8;j++)
				{
					temp=adcValue2[j];
					adcValue2[j]=adcValue2[15-j];
					adcValue2[15-j]=temp;
				}

				printf("[%2d]", i);
				for(int i=0;i<16;++i)//??
				{
					printf("%5d ",adcValue2[i]);
				}
				printf("\r\n");
			}
			//????

			HAL_Delay(1000);
}
	while(0)
	{
		// setCD4076Channel(0);
		HAL_Delay(2);
		//HAL_Delay(10);
		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue,16);
		HAL_Delay(2);
		// setCD4076Channel(1);
		HAL_Delay(2);
		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue2,16);
		HAL_Delay(2);
//		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue3,16);
//		HAL_Delay(5);
//		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue4,16);
//		HAL_Delay(5);
//		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue5,16);
//		HAL_Delay(5);	
		for(int i=0;i<16;++i)//??
			{
				printf("%d ",adcValue[i]);
			}
			printf("\n");
		
		//HAL_Delay(10);
		

			for(int i=0;i<16;++i)//??
			{
				printf("%d ",adcValue2[i]);
			}
			printf("\n");
			for(int i=0;i<16;++i)//??
			{
				printf("%d ",adcValue3[i]);
			}
			printf("\n");
			for(int i=0;i<16;++i)//??
			{
				printf("%d ",adcValue4[i]);
			}
			printf("\n");
			for(int i=0;i<16;++i)//??
			{
				printf("%d ",adcValue5[i]);
			}
			printf("\n");
			printf("\n");
			HAL_Delay(500);
		
	}
  while (0)
  {
		uint32_t tickstart = HAL_GetTick();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		for(int j=0;j<16;++j) //??
		{
			// setCD4076Channel(j);
			for(int i=0;i<16;++i)//??
			{
				scanValue[j][15-1]=ADC_Read(ADC_CHANNEL_0);
				scanValue[j][13-1]=ADC_Read(ADC_CHANNEL_1);
				scanValue[j][11-1]=ADC_Read(ADC_CHANNEL_2);
				scanValue[j][9-1]=ADC_Read(ADC_CHANNEL_3);
				scanValue[j][7-1]=ADC_Read(ADC_CHANNEL_4);
				scanValue[j][5-1]=ADC_Read(ADC_CHANNEL_5);
				scanValue[j][3-1]=ADC_Read(ADC_CHANNEL_6);
				scanValue[j][1-1]=ADC_Read(ADC_CHANNEL_7);
				scanValue[j][2-1]=ADC_Read(ADC_CHANNEL_8);
				scanValue[j][4-1]=ADC_Read(ADC_CHANNEL_9);
				scanValue[j][6-1]=ADC_Read(ADC_CHANNEL_10);
				scanValue[j][8-1]=ADC_Read(ADC_CHANNEL_11);
				scanValue[j][10-1]=ADC_Read(ADC_CHANNEL_12);
				scanValue[j][12-1]=ADC_Read(ADC_CHANNEL_13);
				scanValue[j][14-1]=ADC_Read(ADC_CHANNEL_14);
				scanValue[j][16-1]=ADC_Read(ADC_CHANNEL_15);
			}
			//????
			uint16_t temp;
			for(int i=0;i<8;i++)
			{
				temp=scanValue[j][i];
				scanValue[j][i]=scanValue[j][15-i];
				scanValue[j][15-i]=temp;
			}
		}
		
		//?????��??????????????��???��???????
		unsigned char preparedData[512];
		int order=0;
		for(int j=0;j<16;j++)
		{
			for(int i=0;i<16;++i)//??
			{
				preparedData[2*order]=scanValue[j][i]>>8;
				preparedData[2*order+1]=scanValue[j][i]&0xff;
				order++;
			}
		}
		

		//???????????????????WIFI???????????
		HAL_UART_Transmit(&huart3,preparedData,512,0xffff);
		unsigned char end[3];
		end[0]=0xff;end[1]=0xff;end[2]=0xff;
		HAL_UART_Transmit(&huart3,end,3,0xffff);
		
		uint32_t tickend = HAL_GetTick();
		printf("time consume: %d",tickend-tickstart);
		
		//HAL_GPIO_TogglePin(GPIOB,LED3_Pin|LED2_Pin|LED1_Pin);
		HAL_GPIO_WritePin(GPIOB,LED3_Pin,0);
		
		HAL_Delay(100);
				HAL_GPIO_WritePin(GPIOB,LED3_Pin,1);
		HAL_Delay(100);
		
	}
  /* USER CODE END 3 */
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
