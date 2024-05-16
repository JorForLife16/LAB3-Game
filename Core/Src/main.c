/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "arm_math.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define EEPROM_ADDR 0b10100000
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_lpuart1_rx;
DMA_HandleTypeDef hdma_lpuart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

TIM_HandleTypeDef htim2;

///* USER CODE BEGIN PV */
//static uint8_t data[4] = { 0xff, 0x00, 0x55, 0xaa };
static uint8_t data[4] = { 0x00, 0x00, 0x00, 0x00 };
int life = 3;
uint8_t I2CReadBuffer[4];
uint8_t I2CReadTrigger =0;
int random_NUM;


uint8_t eepromExampleWriteFlag = 0;
uint8_t eepromExampleReadFlag = 0;
uint8_t eepromDataReadBack[4];
int box[10] = {0,1,2,3,4,5,6,7,8,9};
uint8_t tx[] = "hello \n\r";
int mode;
uint8_t answer[1];
int bullet[1];
int randomBox;
int dangerBullet;


int difficult_level = "CHOOSE DIFFICULT LEVEL \n\r [1] EASY \n\r [2] MEDIUM \n\r [3] DIFFICULT \n\r [4] HARDCORE \n\r [5] SEE LIFE LEFT \n\r";
int level;
int selected_level = "DIFFICULT LEVEL : ";
//uint8_t rx_index;
//uint8_t rxData[6];
//uint8_t rx_buffer[100];
//uint8_t transfer_cplt;

uint8_t RxBuffer[1];
uint8_t TxBuffer[40];

int casee = 1;
int i;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void UARTDMAconfig();

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
  MX_DMA_Init();
  MX_LPUART1_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
//  HAL_UART_Receive_IT(&hlpuart1, rxData, 6);
  	HAL_TIM_Base_Start_IT(&htim2);
  	HAL_Delay(300);
  	UARTDMAconfig();



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


//	  HAL_Delay(100);
	  EEPROMWriteExample();
	  EEPROMReadExample(eepromDataReadBack, 4);
//	  EEPROMWriteExample();

//	  HAL_UART_Transmit(&hlpuart1, RxBuffer, 6,1);



/*
		if(RxBuffer[0] != 0 && RxBuffer[0] != '\r'){
			strcpy(answer, RxBuffer);
			RxBuffer[0] = 0;
		}

		if(RxBuffer[0] == '\r'){
			mode = 1;
			random_NUM = rand()%10;
			data[3] = 0xff;
			RxBuffer[0] = 0;
			eepromExampleWriteFlag = 1;
		}
		if(RxBuffer[0] == 0 && mode == 1){
			HAL_UART_Transmit(&hlpuart1, answer, 1,1);
			HAL_UART_Transmit(&hlpuart1, "\n\r", 4,1);
			mode = 0;
			answer[0] = 0;
			eepromExampleWriteFlag = 0;
		}
*/

	  if(mode == 0 && RxBuffer[0] == 0 && RxBuffer[0] != '\r'){
//		  static uint8_t data[4] = { 0x00, 0x00, 0x00, 0x00 };


			HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);
			HAL_UART_Transmit(&hlpuart1, difficult_level, strlen(difficult_level) ,10);
			HAL_UART_Transmit(&hlpuart1, "ENTER YOUR DIFFICULT\n\r", strlen("ENTER YOUR DIFFICULT\n\r") ,8);
			HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);

			mode = 1;
			RxBuffer[0] = 0;
			eepromExampleReadFlag = 0;

	  }
	  if(mode == 1){

			if(RxBuffer[0] != 0 && RxBuffer[0] != '\r'){
				strcpy(answer, RxBuffer);
				mode = 2;
				RxBuffer[0] = 0;

//				eepromExampleWriteFlag = 0;
			}
	  }
	  if(mode == 2){

			HAL_UART_Transmit(&hlpuart1, selected_level, strlen(selected_level) ,8);

//			HAL_UART_Transmit(&hlpuart1, answer, 1 ,2);
//			HAL_UART_Transmit(&hlpuart1, "\n\r", strlen("\n\r") ,2);

			mode = 3;
			RxBuffer[0] = 0;

	  }

	  if(mode == 3){
		  if(answer[0] == 49){
			  	data[0] = 0xff;
			  	data[1] = 0xff;
			  	data[2] = 0xff;
			  	data[3] = 0x00;
			    eepromExampleWriteFlag = 1;

				HAL_UART_Transmit(&hlpuart1, "EASY\n\r", strlen("EASY\n\r") ,2);
				HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);

				level = 1;
				RxBuffer[0] = 0;

//				mode = 0;
		  }else if(answer[0] == 50){
			  	data[0] = 0xff;
			  	data[1] = 0xff;
			  	data[2] = 0xff;
			  	data[3] = 0x00;
			    eepromExampleWriteFlag = 1;

				HAL_UART_Transmit(&hlpuart1, "MEDIUM\n\r", strlen("MEDIUM\n\r") ,2);
				HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);

				level = 2;
				RxBuffer[0] = 0;

//				mode = 0;
		  }else if(answer[0] == 51){
			  	data[0] = 0xff;
			  	data[1] = 0xff;
			  	data[2] = 0xff;
			  	data[3] = 0x00;
			    eepromExampleWriteFlag = 1;

				HAL_UART_Transmit(&hlpuart1, "DIFFICULT\n\r", strlen("DIFFICULT\n\r") ,8);
				HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);

				level = 3;
				RxBuffer[0] = 0;

//				mode = 0;
		  }else if(answer[0] == 52){
			  	data[0] = 0xff;
			  	data[1] = 0xff;
			  	data[2] = 0xff;
			  	data[3] = 0x00;
			    eepromExampleWriteFlag = 1;

				HAL_UART_Transmit(&hlpuart1, "HARDCORE\n\r", strlen("HARDCORE\n\r") ,2);
				HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);

				level = 4;
				RxBuffer[0] = 0;

//				mode = 0;
		  }else if(answer[0] == 53){
			  eepromExampleReadFlag = 1;
			  answer[0] = 0;
			  mode = 0;

		  }else{

				HAL_UART_Transmit(&hlpuart1, "NOT IN A CHOICE\n\r", strlen("NOT IN A CHOICE\n\r") ,2);
				HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);

//				HAL_UART_Transmit(&hlpuart1, system("cls"), 4 ,2);

				level = 5;
				RxBuffer[0] = 0;

//				mode = 0;
		  }
	  }
	  if(level == 1){
		    eepromExampleWriteFlag = 0;

		  random_NUM = rand()%10;
		  mode = 6;
		  level = 5;
		  RxBuffer[0] = 0;

	  }else if(level == 2){
		    eepromExampleWriteFlag = 0;

		  random_NUM = rand()%10;
		  mode = 6;
		  level = 5;
		  RxBuffer[0] = 0;


	  }else if(level == 3){
		    eepromExampleWriteFlag = 0;

		  random_NUM = rand()%10;
		  mode = 6;
		  level = 5;
		  RxBuffer[0] = 0;


	  }else if(level == 4){
		    eepromExampleWriteFlag = 0;

		  random_NUM = rand()%10;
		  mode = 6;
		  level = 5;
		  RxBuffer[0] = 0;

	  }else if(level == 5){

		  mode = 6;
//		  level = 0;
	  }
	  randomBox = box[random_NUM];
	  if(randomBox == 1){dangerBullet = 49;}
	  else if(randomBox == 2){dangerBullet = 50;}
	  else if(randomBox == 3){dangerBullet = 51;}
	  else if(randomBox == 4){dangerBullet = 52;}
	  else if(randomBox == 5){dangerBullet = 53;}
	  else if(randomBox == 6){dangerBullet = 54;}
	  else if(randomBox == 7){dangerBullet = 55;}
	  else if(randomBox == 8){dangerBullet = 56;}
	  else if(randomBox == 9){dangerBullet = 57;}
	  else if(randomBox == 0){dangerBullet = 48;}



	  if(mode == 6){
		if(RxBuffer[0] != 0 && RxBuffer[0] != '\r'){
			strcpy(bullet, RxBuffer);
			RxBuffer[0] = 0;
		}

		if(RxBuffer[0] == '\r'){
			casee = 1;

			RxBuffer[0] = 0;
			eepromExampleWriteFlag = 1;
		}
		if(RxBuffer[0] == 0 && casee == 1){
			HAL_UART_Transmit(&hlpuart1,"BULLET OF YOUR CHOICE :" , strlen("BULLET OF YOUR CHOICE :"),8);
			HAL_UART_Transmit(&hlpuart1, bullet, 1,1);
			HAL_UART_Transmit(&hlpuart1, "\n\r", 4,1);
			casee = 2;



		}
		if(casee == 2){
//			life = 3;
			if(bullet[0] == dangerBullet){


				if(data[3]==0 && life == 3){
					HAL_UART_Transmit(&hlpuart1, "YOUR LIFE HAVE BEEN LEFT JUST 2 !!\n\r", strlen("YOUR LIFE HAVE BEEN LEFT JUST 2 !!\n\r") ,8);
					life--;
					bullet[0] = 0;
					data[life] = 0x00;
					random_NUM = rand()%10;
					eepromExampleWriteFlag = 1;

				}else if(data[2]==0 && life == 2){
					HAL_UART_Transmit(&hlpuart1, "YOUR LIFE LEFT JUST 1 !!\n\r", strlen("YOUR LIFE LEFT JUST 1 !!\n\r") ,8);

					life--;
					bullet[0] = 0;
					data[life] = 0x00;
					random_NUM = rand()%10;
					eepromExampleWriteFlag = 1;

				}else if(data[1]==0 && life == 1){
					life--;
					bullet[0] = 0;
					data[life] = 0x00;
					random_NUM = rand()%10;
					eepromExampleWriteFlag = 1;

				}


			}if(life == 0 && data[0,3] == 0){
				HAL_UART_Transmit(&hlpuart1, "GAME OVERRRRRR\n\r", strlen("GAME OVERRRRRR\n\r") ,8);

				life = 3;
				mode = 0;
				casee = 0;
				RxBuffer[0] = 0;
				level = 0;
				dangerBullet = 0;

//				eepromExampleReadFlag = 0;

			}



//			if(bullet[0] == dangerBullet){
//				HAL_UART_Transmit(&hlpuart1, "--------------------------\n\r", strlen("--------------------------\n\r") ,8);
//				HAL_UART_Transmit(&hlpuart1,"YOU GOT SHOT!! \n\r" , strlen("YOU GOT SHOT!! \n\r"),8);
//
//				bullet[0] = 0;
//				data[2] = 0x00;
//
////				mode = 0;
//				casee = 0;
//				random_NUM = rand()%10;
//				eepromExampleWriteFlag = 1;
//
//			}
		}

	  }








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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x30A0A7FB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_2;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  htim2.Init.Prescaler = 169;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 5479;
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

  /* USER CODE END TIM2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void UARTDMAconfig(){
	HAL_UART_Receive_DMA(&hlpuart1, RxBuffer, 1);
}

void EEPROMWriteExample() {
	if (eepromExampleWriteFlag && hi2c1.State == HAL_I2C_STATE_READY) {

		HAL_I2C_Mem_Write_IT(&hi2c1, EEPROM_ADDR, 0x2C, I2C_MEMADD_SIZE_16BIT,data, 4);

//		eepromExampleWriteFlag = 0;
	}
}

void EEPROMReadExample(uint8_t *Rdata, uint16_t len) {
	if (eepromExampleReadFlag && hi2c1.State == HAL_I2C_STATE_READY) {
		HAL_I2C_Mem_Read_IT(&hi2c1, EEPROM_ADDR, 0x2c, I2C_MEMADD_SIZE_16BIT, Rdata, len);
//		eepromExampleReadFlag = 0;
	}
}

//void ReadEEPROMSeq(uint16_t MemAddr,uint8_t *Rdata,uint16_t len,uint8_t *Trigger)
//{
//	static enum
//	{
//		State_Idle,
//		State_address_frame,
//		State_address_frame_wait,
//		State_dataFrame,
//		State_dataFrame_wait
//	} State = State_Idle;
//	switch(State)
//	{
//	case State_Idle:
//	if(*Trigger)
//	{
//		State = State_address_frame;
//	}
//	break;
//	case State_address_frame:
//	{
//		static uint8_t MemoryAddress[2];
//		MemoryAddress[0] = (MemAddr>>8) & 0xFF;
//		MemoryAddress[1] = (MemAddr) & 0xFF;
//		HAL_I2C_Master_Seq_Transmit_IT(&hi2c1, EEPROMAddr, MemoryAddress, 2, I2C_FIRST_AND_NEXT_FRAME);
//		State = State_address_frame_wait;
//	}
//	break;
//	case State_address_frame_wait:
//	if(hi2c1.State == HAL_I2C_STATE_READY)
//	{
//		State = State_dataFrame;
//	}
//	break;
//	case State_dataFrame:
//	HAL_I2C_Master_Seq_Receive_IT(&hi2c1, EEPROMAddr, Rdata, len, I2C_LAST_FRAME);
//	State = State_dataFrame_wait;
//	break;
//	case State_dataFrame_wait:
//	if(hi2c1.State == HAL_I2C_STATE_READY)
//	{
//		State = State_Idle;
//		*Trigger = 0;
//	}
//	break;
//	}
//}
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
//	if (htim == &htim2) {
////		UARTDMAconfig();
//		HAL_UART_Receive_DMA(&hlpuart1, RxBuffer, 1);
//
//	}
//
//
//}
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hlpuart){
////	UNUSED(huart);
////	GPIO_PinState B1 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
//	if(hlpuart == &hlpuart1){
//
////		RxBuffer[6] = '\0';
//
//
//		if(RxBuffer == '1'){
//			casee = 2;
//			HAL_UART_Transmit_DMA(&hlpuart1, "\n\r", 4);
//
//		}else if(mode == 1){
//			casee = 1;
//
//			HAL_UART_Transmit_DMA(&hlpuart1, RxBuffer, 6);
//		}
//	}
//
//}
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
