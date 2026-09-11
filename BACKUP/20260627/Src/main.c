/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
U16toU8 water;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    HAL_Delay(1000);
    water.var16 = GetWaterLevel();
    // printf("O:%d\r\n",water.var16);
    // printf("hex:%02x %02x\r\n",water.var8[0],water.var8[1]);
    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 3199;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 299;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  // HAL_TIM_Base_Start_IT(&htim2);
  __HAL_TIM_SetCounter(&htim2,0);
  __HAL_TIM_ENABLE_IT(&htim2,TIM_IT_UPDATE);
  // __HAL_TIM_ENABLE(&htim2);
  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  // HAL_UART_Receive_IT(&huart2,&data,1);
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA4 PA5
                           PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
int fputc(int ch,FILE* fp){
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

uint16_t GetWaterLevel(){
  uint8_t chipselect[7][3]={{0,0,1},{0,1,1},{1,0,1},{1,1,0},{0,1,0},{1,0,0},{0,0,0}};
  uint8_t channelselect[8][3]={{1,1,1},{1,0,1},{1,1,0},{0,0,0},{1,0,0},{0,1,0},{0,0,1},{0,1,1}};

  uint8_t counter=57;

  for(int8_t i=6;i>=0;i--){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,chipselect[i][0]);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,chipselect[i][1]);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,chipselect[i][2]);
    HAL_Delay(1);
    for(int8_t j=7;j>=0;j--){
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,channelselect[j][0]);
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,channelselect[j][1]);
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,channelselect[j][2]);
      HAL_Delay(1);
      //read water level
      counter--;
      if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==0){
        if(counter<7){
          counter=counter-3;
        }else{
          counter=counter-6;
        }
        // printf("i:%d j:%d\r\n",i,j);
        // printf("counter:%d\r\n",counter);
        return counter;
      }
    }
  }
  return 0;
}

uint16_t CRC_Check(uint8_t *CRC_Ptr, uint8_t LEN) {
uint16_t CRC_Value = 0xFFFF;
uint8_t i, j;

for (i = 0; i < LEN; i++) {
CRC_Value ^= *(CRC_Ptr + i);
for (j = 0; j < 8; j++) {
if (CRC_Value & 0x0001)
CRC_Value = (CRC_Value >> 1) ^ 0xA001;
else
CRC_Value = (CRC_Value >> 1);
}
}
CRC_Value = (CRC_Value >> 8) | (CRC_Value << 8); //swap high low byte

return CRC_Value;
}

void ParseModbus(uint8_t *src,uint8_t len){
  uint16_t crc=CRC_Check(src,len-2);
  uint8_t crclow,crchigh;
  uint8_t databuff[16]={0};
  SplitU16toU8(crc,&crchigh,&crclow);
  U16toU8 temp={.var16=0};
  if((src[len-2]==crchigh)&&(src[len-1]==crclow)){
    // printf("crc correct\r\n");
    if(src[0]==SLAVE_ADD){
      switch (src[1])
      {
      case 0x03:
        /* code */
        if((len%2)==0)//judge master(0) or slave(1)
        {
          databuff[0]=SLAVE_ADD;
          databuff[1]=src[1];
          databuff[2]=0x02;
          databuff[3]=water.var8[1];
          databuff[4]=water.var8[0];
          crc=CRC_Check(databuff,5);
          SplitU16toU8(crc,&databuff[5],&databuff[6]);
          HAL_UART_Transmit(&huart2,databuff,7,HAL_MAX_DELAY);

        }else{
          databuff[0]=SLAVE_ADD;
          databuff[1]=src[1];
          databuff[2]=0x02;
          temp.var8[1]=src[3];
          temp.var8[0]=src[4];
          temp.var16=temp.var16+water.var16;
          databuff[3]=temp.var8[1];
          databuff[4]=temp.var8[0];
          crc=CRC_Check(databuff,5);
          SplitU16toU8(crc,&databuff[5],&databuff[6]);
          HAL_UART_Transmit(&huart2,databuff,7,HAL_MAX_DELAY);

        }

        break;
      
      default:
        break;
      }
    }else{return;}

  }else{return;}
  return;

}
void SplitU16toU8(uint16_t src,uint8_t *high,uint8_t *low){
  *low=src&0x00FF;
  *high=(src>>8)&0x00FF;
}
void CommandRespond(uint8_t code,uint16_t reg,uint16_t value){

}