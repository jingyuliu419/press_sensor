/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include "gpio.h"
	#include "usart.h"
	#include "stdint.h"

uint16_t all_point_value[256]={0};
uint16_t ADC_scan_finished=FALSE;
uint16_t adcValue[16]={0};
uint16_t count=0;//采样序列计数

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 16;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_4;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_6;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_7;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_8;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_REGULAR_RANK_9;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = ADC_REGULAR_RANK_10;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_11;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = ADC_REGULAR_RANK_12;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = ADC_REGULAR_RANK_13;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_13;
  sConfig.Rank = ADC_REGULAR_RANK_14;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_14;
  sConfig.Rank = ADC_REGULAR_RANK_15;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_15;
  sConfig.Rank = ADC_REGULAR_RANK_16;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    PA4     ------> ADC1_IN4
    PA5     ------> ADC1_IN5
    PA6     ------> ADC1_IN6
    PA7     ------> ADC1_IN7
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
    PB0     ------> ADC1_IN8
    PB1     ------> ADC1_IN9
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_NORMAL;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    PC3     ------> ADC1_IN13
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    PA4     ------> ADC1_IN4
    PA5     ------> ADC1_IN5
    PA6     ------> ADC1_IN6
    PA7     ------> ADC1_IN7
    PC4     ------> ADC1_IN14
    PC5     ------> ADC1_IN15
    PB0     ------> ADC1_IN8
    PB1     ------> ADC1_IN9
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
uint16_t ADC_Read(uint32_t Channel)
{
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = Channel;                                         /* 通道 */
	sConfig.Rank = ADC_REGULAR_RANK_1;                              
	sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;                  /* 采样时间 */
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)             
	{
		Error_Handler();
	}
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	return (uint16_t)HAL_ADC_GetValue(&hadc1);
}



void delay_us(uint32_t us)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
}



/**256个通道采样完成后，数据写入数组all_point_value中，将ADC_scan_finished置为1
*/
uint16_t afterorder[16];
uint16_t t1;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

	static int round=0;
	if(round ==0)
		t1= HAL_GetTick();
		//按照列序列重新排列
		setCD4076Channel(round+1);
		afterorder[15-1]=adcValue[0];
		afterorder[13-1]=adcValue[1];
		afterorder[11-1]=adcValue[2];
		afterorder[9-1]=adcValue[3];
		afterorder[7-1]=adcValue[4];
		afterorder[5-1]=adcValue[5];
		afterorder[3-1]=adcValue[6];
		afterorder[1-1]=adcValue[7];
		afterorder[2-1]=adcValue[8];
		afterorder[4-1]=adcValue[9];
		afterorder[6-1]=adcValue[10];
		afterorder[8-1]=adcValue[11];
		afterorder[10-1]=adcValue[12];
		afterorder[12-1]=adcValue[13];
		afterorder[14-1]=adcValue[14];
		afterorder[16-1]=adcValue[15]; 
//		
//		//逆序，和传感器从上到下顺序一致
		uint16_t temp;
		for(int i=0; i<8;++i)
		{
			temp = afterorder[i];
			afterorder[i]= afterorder[15-i];
			afterorder[15-i]=temp;
		}
		
		//整理添加到256的完整帧数组中
		for(int i=0;i<16;i++)
		{
			all_point_value[round*16+i]=afterorder[i];
		}
		round++;
		if(round == 16)
		{
					//数据采样已完毕，可以发送了。
		uint16_t tic= HAL_GetTick();
		//printf("adopt 16 times,tick:%d\n",tic-t1);
			ADC_scan_finished =1;
			round = 0;
			return;
		}
		else
		{
			
		//HAL_Delay(1);
			delay_us(500);
			HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue,16);//在一个扫描循环中，开启，一个循环结束，就不再调用
		}
}

unsigned char preparedData[512];
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	count++;
	HAL_GPIO_TogglePin(GPIOB,LED2_Pin);

	if(ADC_scan_finished == 1)
	{
		uint16_t t1= HAL_GetTick();
		//printf("enter in time callback,tick:%d\n",t1);
		ADC_scan_finished=0;

			for(int i=0;i<256;++i)//行
			{
				preparedData[2*i]=all_point_value[i]>>8;
				preparedData[2*i+1]=all_point_value[i]&0xff;
			}
//			for(int i=0;i<256;++i)//行
//			{
//				printf("%d ",all_point_value[i]);
//				if((i+1)%16 == 0)
//					printf("\n");
//			}
//			printf("\n");
			HAL_UART_Transmit(&huart3,preparedData,512,0xffff);
			
			
			unsigned char stamp[2];
			stamp[0]=count>>8;
			stamp[1]=count&0xff;
			HAL_UART_Transmit(&huart3,stamp,2,0xffff);
//			printf("%d\n",count);
			
			
			unsigned char end[3];
			end[0]=0xfd;end[1]=0xfe;end[2]=0xff;
			HAL_UART_Transmit(&huart3,end,3,0xffff);
			
			
			
			
			//HAL_UART_Transmit(&huart1,preparedData,512,0xffff);
			//HAL_UART_Transmit(&huart1,end,3,0xffff);
//				tickslastlast=	HAL_GetTick();
//			printf("time during:%d",tickslastlast-tickslast);
////			tickslast = HAL_GetTick();
		/*再次启动，ADC，从第一列开始触发DMA搬运采样数据*/
			setCD4076Channel(0);
			//HAL_Delay(1);
			delay_us(500);
		HAL_ADC_Start_DMA(&hadc1,(uint32_t *)&adcValue,16);
		uint16_t t2= HAL_GetTick();
		//printf("out time callback,tick consume :%d\n",t2-t1);
	}
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
