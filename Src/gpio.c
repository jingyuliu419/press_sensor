/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|A_Pin|B_Pin|C_Pin
                          |D_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED3_Pin|LED2_Pin|LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PB2 PBPin PBPin PBPin
                           PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = GPIO_PIN_2|A_Pin|B_Pin|C_Pin
                          |D_Pin|LED3_Pin|LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

void setIOs(uint8_t A,uint8_t B,uint8_t C,uint8_t D)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,A);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,B);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,C);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,D);
	
	
}
void setCD4076Channel(uint8_t channel)
{
	switch (channel)
	{
		case 0:
			setIOs(0,0,0,0);
			break;
		case 1:
			setIOs(1,0,0,0);
			break;
		case 2:
			setIOs(0,1,0,0);
			break;
		case 3:
			setIOs(1,1,0,0);
			break;
		case 4:
			setIOs(0,0,1,0);
			break;
		case 5:
			setIOs(1,0,1,0);
			break;
		case 6:
			setIOs(0,1,1,0);
			break;
		case 7:
			setIOs(1,1,1,0);
			break;
		case 8:
			setIOs(0,0,0,1);
			break;
		case 9:
			setIOs(1,0,0,1);
			break;
		case 10:
			setIOs(0,1,0,1);
			break;
		case 11:
			setIOs(1,1,0,1);
			break;		
		case 12:
			setIOs(0,0,1,1);
			break;
		case 13:
			setIOs(1,0,1,1);
			break;
		case 14:
			setIOs(0,1,1,1);
			break;
		case 15:
			setIOs(1,1,1,1);
			break;
		default:
			break;
	}	
}

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
