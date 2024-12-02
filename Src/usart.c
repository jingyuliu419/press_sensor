/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"
#include "atk_mw8266d.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include "tim.h"
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (unsigned char) ch;      
	return ch;
}
#endif 



uint8_t uart3recvBuf;
extern uint16_t count;

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART3 init function */

// void MX_USART3_UART_Init(void)
// {

//   /* USER CODE BEGIN USART3_Init 0 */

//   /* USER CODE END USART3_Init 0 */

//   /* USER CODE BEGIN USART3_Init 1 */

//   /* USER CODE END USART3_Init 1 */
//   huart3.Instance = USART3;
//   huart3.Init.BaudRate = 460800;
//   huart3.Init.WordLength = UART_WORDLENGTH_8B;
//   huart3.Init.StopBits = UART_STOPBITS_1;
//   huart3.Init.Parity = UART_PARITY_NONE;
//   huart3.Init.Mode = UART_MODE_TX_RX;
//   huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//   huart3.Init.OverSampling = UART_OVERSAMPLING_16;
//   if (HAL_UART_Init(&huart3) != HAL_OK)
//   {
//     Error_Handler();
//   }
//   /* USER CODE BEGIN USART3_Init 2 */

//   /* USER CODE END USART3_Init 2 */

// }

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(uartHandle->Instance==USART1)
    {
    /* USER CODE BEGIN USART1_MspInit 0 */

    /* USER CODE END USART1_MspInit 0 */
      /* USART1 clock enable */
      __HAL_RCC_USART1_CLK_ENABLE();

      __HAL_RCC_GPIOA_CLK_ENABLE();
      /**USART1 GPIO Configuration
      PA9     ------> USART1_TX
      PA10     ------> USART1_RX
      */
      GPIO_InitStruct.Pin = GPIO_PIN_9;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_10;
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      /* USART1 interrupt Init */
      HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
      HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspInit 1 */

    /* USER CODE END USART1_MspInit 1 */
    }
    else if (uartHandle->Instance == ATK_MW8266D_UART_INTERFACE)                 /* �����ATK-MW8266D UART */
    {
        ATK_MW8266D_UART_TX_GPIO_CLK_ENABLE();                              /* ʹ��UART TX����ʱ�� */
        ATK_MW8266D_UART_RX_GPIO_CLK_ENABLE();                              /* ʹ��UART RX����ʱ�� */
        ATK_MW8266D_UART_CLK_ENABLE();                                      /* ʹ��UARTʱ�� */
        
        GPIO_InitStruct.Pin    = ATK_MW8266D_UART_TX_GPIO_PIN;             /* UART TX���� */
        GPIO_InitStruct.Mode   = GPIO_MODE_AF_PP;                          /* ����������� */
        GPIO_InitStruct.Pull   = GPIO_NOPULL;                              /* �������� */
        GPIO_InitStruct.Speed  = GPIO_SPEED_FREQ_HIGH;                     /* ���� */
        HAL_GPIO_Init(ATK_MW8266D_UART_TX_GPIO_PORT, &GPIO_InitStruct);    /* ��ʼ��UART TX���� */
        
        GPIO_InitStruct.Pin    = ATK_MW8266D_UART_RX_GPIO_PIN;             /* UART RX���� */
        GPIO_InitStruct.Mode   = GPIO_MODE_INPUT;                          /* ���� */
        GPIO_InitStruct.Pull   = GPIO_NOPULL;                              /* �������� */
        GPIO_InitStruct.Speed  = GPIO_SPEED_FREQ_HIGH;                     /* ���� */
        HAL_GPIO_Init(ATK_MW8266D_UART_RX_GPIO_PORT, &GPIO_InitStruct);    /* ��ʼ��UART RX���� */
        
        HAL_NVIC_SetPriority(ATK_MW8266D_UART_IRQn, 0, 0);                  /* ��ռ���ȼ�0�������ȼ�0 */
        HAL_NVIC_EnableIRQ(ATK_MW8266D_UART_IRQn);                          /* ʹ��UART�ж�ͨ�� */
        
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE);                          /* ʹ��UART�����ж� */
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);                          /* ʹ��UART���߿����ж� */
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  // else if(uartHandle->Instance==USART3)
  // {
  // /* USER CODE BEGIN USART3_MspDeInit 0 */

  // /* USER CODE END USART3_MspDeInit 0 */
  //   /* Peripheral clock disable */
  //   __HAL_RCC_USART3_CLK_DISABLE();

  //   /**USART3 GPIO Configuration
  //   PB10     ------> USART3_TX
  //   PB11     ------> USART3_RX
  //   */
  //   HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

  //   /* USART3 interrupt Deinit */
  //   HAL_NVIC_DisableIRQ(USART3_IRQn);
  // /* USER CODE BEGIN USART3_MspDeInit 1 */

  // /* USER CODE END USART3_MspDeInit 1 */
  // }
}

/* USER CODE BEGIN 1 */

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	printf("enter HAL_UART_RxCpltCallback\n");
// 	if(huart->Instance == USART3)
// 	{
// 		printf("huart == huart3\n");
// 		printf("uart3recvBuf %d\n",uart3recvBuf);
// 		HAL_UART_Receive_IT(&huart3,&uart3recvBuf,1);
// 		if(uart3recvBuf == '2')
// 		 HAL_TIM_Base_Stop_IT(&htim2);
// 		else if(uart3recvBuf == '1')
// 		{
// 			count=0;//count��������
// 			HAL_TIM_Base_Start_IT(&htim2);
// 		}
// 	}
	
	
	
// }

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
