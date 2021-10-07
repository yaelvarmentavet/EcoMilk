/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Inputs
#define REALIZE_BRAKES_PORT              GPIOD
#define MOTOR_Z_UP_PORT                  GPIOD
#define MOTOR_Z_DOWN_PORT                GPIOD
#define MOTOR_Z_LIMIT_UP_PORT            GPIOD
#define MOTOR_Z_LIMIT_DOWN_PORT          GPIOD
#define MOTOR_TILT_UP_PORT               GPIOD
#define MOTOR_TILT_DOWN_PORT             GPIOD
#define MOTOR_TILT_LIMIT_UP_PORT         GPIOD
#define MOTOR_TILT_LIMIT_DOWN_PORT       GPIOG
#define BRAKE_X_PORT                     GPIOG
#define BRAKE_ROTATE_PORT                GPIOG
#define BRAKE_SPARE_A_PORT               GPIOG
#define BRAKE_SPARE_B_PORT               GPIOG
#define BRAKE_SPARE_C_PORT               GPIOG
#define BRAKE_SPARE_D_PORT               GPIOG
#define END_AFFECTO_PORT                 GPIOC
#define NFAULT_GLOBAL_PORT               GPIOC
#define MOTOR_N_FORWARD_PORT             GPIOC
#define MOTOR_N_BACKWARD_PORT            GPIOC

#define REALIZE_BRAKES_PIN              GPIO_PIN_8
#define MOTOR_Z_UP_PIN                  GPIO_PIN_9
#define MOTOR_Z_DOWN_PIN                GPIO_PIN_10
#define MOTOR_Z_LIMIT_UP_PIN            GPIO_PIN_11
#define MOTOR_Z_LIMIT_DOWN_PIN          GPIO_PIN_12
#define MOTOR_TILT_UP_PIN               GPIO_PIN_13
#define MOTOR_TILT_DOWN_PIN             GPIO_PIN_14
#define MOTOR_TILT_LIMIT_UP_PIN         GPIO_PIN_15
#define MOTOR_TILT_LIMIT_DOWN_PIN       GPIO_PIN_2
#define BRAKE_X_PIN                     GPIO_PIN_3
#define BRAKE_ROTATE_PIN                GPIO_PIN_4
#define BRAKE_SPARE_A_PIN               GPIO_PIN_5
#define BRAKE_SPARE_B_PIN               GPIO_PIN_6
#define BRAKE_SPARE_C_PIN               GPIO_PIN_7
#define BRAKE_SPARE_D_PIN               GPIO_PIN_8
#define END_AFFECTO_PIN                 GPIO_PIN_6
#define NFAULT_GLOBAL_PIN               GPIO_PIN_7
#define MOTOR_N_FORWARD_PIN             GPIO_PIN_8
#define MOTOR_N_BACKWARD_PIN            GPIO_PIN_9

// Outputs
#define ENABLE_BRAKES_PORT       GPIOE
#define BRAKE_Z_ON_N_PORT        GPIOE	
#define BRAKE_X_ON_N_PORT        GPIOE	
#define BRAKE_TILT_ON_N_PORT     GPIOE
#define BRAKE_ROTATE_ON_PORT     GPIOE
#define BRAKE_SPARE_A_ON_PORT    GPIOC
#define BRAKE_SPARE_B_ON_PORT    GPIOF
#define BRAKE_SPARE_C_ON_PORT    GPIOF
#define BRAKE_SPARE_D_ON_PORT    GPIOF
#define MOTOR_Z_DIR_PORT         GPIOF
#define MOTOR_Z_ENABLE_PORT      GPIOF
#define MOTOR_TILT_DIR_PORT      GPIOF
#define MOTOR_TILT_ENABLE_PORT   GPIOF
#define END_AFFECTO_DIR_PORT     GPIOF
#define MOTOR_N_INA_PORT         GPIOF
#define MOTOR_N_INB_PORT         GPIOF
#define SPARE_ENABLE_A_PORT      GPIOF
#define SPARE_ENABLE_B_PORT      GPIOC

#define ENABLE_BRAKES_PIN       GPIO_PIN_2
#define BRAKE_Z_ON_N_PIN        GPIO_PIN_3	
#define BRAKE_X_ON_N_PIN        GPIO_PIN_4	
#define BRAKE_TILT_ON_N_PIN     GPIO_PIN_5
#define BRAKE_ROTATE_ON_PIN     GPIO_PIN_6
#define BRAKE_SPARE_A_ON_PIN    GPIO_PIN_13
#define BRAKE_SPARE_B_ON_PIN    GPIO_PIN_0
#define BRAKE_SPARE_C_ON_PIN    GPIO_PIN_1
#define BRAKE_SPARE_D_ON_PIN    GPIO_PIN_2
#define MOTOR_Z_DIR_PIN         GPIO_PIN_3
#define MOTOR_Z_ENABLE_PIN      GPIO_PIN_4
#define MOTOR_TILT_DIR_PIN      GPIO_PIN_5
#define MOTOR_TILT_ENABLE_PIN   GPIO_PIN_6
#define END_AFFECTO_DIR_PIN     GPIO_PIN_7
#define MOTOR_N_INA_PIN         GPIO_PIN_8
#define MOTOR_N_INB_PIN         GPIO_PIN_9
#define SPARE_ENABLE_A_PIN      GPIO_PIN_10
#define SPARE_ENABLE_B_PIN      GPIO_PIN_0

#define MOTOR_Z_STEP_TIM        htim2
#define MOTOR_Z_STEP_CH         1

#define MOTOR_TILT_STEP_TIM     htim3
#define MOTOR_TILT_STEP_CH      1

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM3_Init(void);
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
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    //Realize_brakes  = high 	Realize  all  brakes  	Enable_brakes	High= realize 
    if(HAL_GPIO_ReadPin(REALIZE_BRAKES_PORT, REALIZE_BRAKES_PIN) == GPIO_PIN_SET)
      HAL_GPIO_WritePin(ENABLE_BRAKES_PORT, ENABLE_BRAKES_PIN, GPIO_PIN_SET);

    ////////////////////////////////////////////////////////////////////////////
    
    //Motor_z_up =H     Realize    brakes Z   Brake_z_on      Low  =  realize 
    //                  Motor   Z  dir  = 1   Motor_Z_dir     High= up
    //                  Motor   Z  step pwm   Motor_Z_step    Pwm  1khz
    //                                        Motor_z_enable  Enable = high
    if(HAL_GPIO_ReadPin(MOTOR_Z_UP_PORT, MOTOR_Z_UP_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(BRAKE_Z_ON_N_PORT, BRAKE_Z_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_Z_DIR_PORT, MOTOR_Z_DIR_PIN, GPIO_PIN_SET);
      HAL_TIMEx_PWMN_Start(&MOTOR_Z_STEP_TIM, 1);
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_SET);
    }
    
    //Motor_z_down = H  Realize    brakes Z     Brake_z_on      Low  =  realize 
    //                  Motor   Z  dir  = 0     Motor_Z_dir     low= down
    //                  Motor   Z  step pwm     Motor_Z_step    Pwm  1khz
    //                                          Motor_z_enable Enable = high  
    if(HAL_GPIO_ReadPin(MOTOR_Z_DOWN_PORT, MOTOR_Z_DOWN_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(BRAKE_Z_ON_N_PORT, BRAKE_Z_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_Z_DIR_PORT, MOTOR_Z_DIR_PIN, GPIO_PIN_RESET);
      HAL_TIMEx_PWMN_Start(&MOTOR_Z_STEP_TIM, 1);
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_SET);
    }
    
    //Motor_z_up =low    Brake z  on    Motor_Z_step     High  =  hold
    //Motor_z_down =low  Motor z  stop  brake_z_on       Low = stop
    //                                  Motor_z_enable  Disable = low
    if((HAL_GPIO_ReadPin(MOTOR_Z_UP_PORT, MOTOR_Z_UP_PIN) == GPIO_PIN_RESET) &&
       (HAL_GPIO_ReadPin(MOTOR_Z_DOWN_PORT, MOTOR_Z_DOWN_PIN) == GPIO_PIN_RESET))
    {
      HAL_TIMEx_PWMN_Start(&MOTOR_Z_STEP_TIM, MOTOR_Z_STEP_CH);
      HAL_GPIO_WritePin(BRAKE_Z_ON_N_PORT, BRAKE_Z_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_RESET);
    }

    //Motor_z_limit_up = high   move up   Motor_z_enable  Disable = low  
    //And  motor_z_up = high	Limit
    if((HAL_GPIO_ReadPin(MOTOR_Z_LIMIT_UP_PORT, MOTOR_Z_LIMIT_UP_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_Z_UP_PORT, MOTOR_Z_UP_PIN) == GPIO_PIN_SET))
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_RESET);
  
    //Motor_z_limit_Down = high   Limit  move down      Motor_z_enable 	Disable = low  
    //And  motor_z_down = high	
    if((HAL_GPIO_ReadPin(MOTOR_Z_LIMIT_DOWN_PORT, MOTOR_Z_LIMIT_DOWN_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_Z_DOWN_PORT, MOTOR_Z_DOWN_PIN) == GPIO_PIN_SET))
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_RESET);

    ////////////////////////////////////////////////////////////////////////////

    //Motor_tilt_up =H	Realize    brakes  tilt 	        Brake_tilt_on 	       Low  =  realize 
    //                             Motor   tilt  dir  = 1       Motor_tilt_dir         High= up
    //                             Motor   tilt  step     pwm	Motor_tilt_step        Pwm  1khz
    //                                                          Motor_tilt_enable      Enable=high
    if(HAL_GPIO_ReadPin(MOTOR_TILT_UP_PORT, MOTOR_TILT_UP_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(BRAKE_TILT_ON_N_PORT, BRAKE_TILT_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_TILT_DIR_PORT, MOTOR_TILT_DIR_PIN, GPIO_PIN_SET);
      HAL_TIMEx_OnePulseN_Start(&MOTOR_TILT_STEP_TIM, MOTOR_TILT_STEP_CH);
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_SET);
    }
	
    //Motor_tilt_down =H   Realize brakes  tilt        Brake_tilt_on 	   Low  =  realize 
    //                     Motor   tilt  dir  = 0      Motor_tilt_dir      low= down
    //                     Motor   tilt  step  pwm     Motor_tilt_step     Pwm  1khz
    //                                                 Motor_tilt_enable   Enable = high
    if(HAL_GPIO_ReadPin(MOTOR_TILT_DOWN_PORT, MOTOR_TILT_DOWN_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(BRAKE_TILT_ON_N_PORT, BRAKE_TILT_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_TILT_DIR_PORT, MOTOR_TILT_DIR_PIN, GPIO_PIN_RESET);
      HAL_TIMEx_OnePulseN_Start(&MOTOR_TILT_STEP_TIM, MOTOR_TILT_STEP_CH);
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_SET);
    }

    //Motor_tilt_up =low     Brake tilt  on    Motor_tilt_step     High  =  hold
    //Motor_tilt_down =low   Motor tilt stop   brake_tilt_on       Low = stop
    //                                         Motor_tilt_enable   Disable= low
    if((HAL_GPIO_ReadPin(MOTOR_TILT_UP_PORT, MOTOR_TILT_UP_PIN) == GPIO_PIN_RESET) &&
       (HAL_GPIO_ReadPin(MOTOR_TILT_DOWN_PORT, MOTOR_TILT_DOWN_PIN) == GPIO_PIN_RESET))
    {
      HAL_TIMEx_PWMN_Start(&MOTOR_TILT_STEP_TIM, MOTOR_TILT_STEP_CH);
      HAL_GPIO_WritePin(BRAKE_TILT_ON_N_PORT, BRAKE_TILT_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_RESET);
    }

    //Motor_tilt_limit_up = high        Limit  move up 	Motor_tilt_enable	Disable= low
    //And  motor_tilt_up = high	        
    if((HAL_GPIO_ReadPin(MOTOR_TILT_LIMIT_UP_PORT, MOTOR_TILT_LIMIT_UP_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_TILT_UP_PORT, MOTOR_TILT_UP_PIN) == GPIO_PIN_SET))
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_RESET);

    //Motor_tilt_limit_Down = high   Limit  move down	Motor_tilt_enable	Disable= low
    //And  motor_tilt_down = high	        
    if((HAL_GPIO_ReadPin(MOTOR_TILT_LIMIT_DOWN_PORT, MOTOR_TILT_LIMIT_DOWN_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_TILT_DOWN_PORT, MOTOR_TILT_DOWN_PIN) == GPIO_PIN_SET))
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_RESET);

    ////////////////////////////////////////////////////////////////////////////

    //Brake_X = H   Realize    brakes  X	Brake_x_on 	 Low  =  realize 
    if(HAL_GPIO_ReadPin(BRAKE_X_PORT, BRAKE_X_PIN) == GPIO_PIN_SET)
      HAL_GPIO_WritePin(BRAKE_X_ON_N_PORT, BRAKE_X_ON_N_PIN, GPIO_PIN_RESET);

    //Brake_X = Low   brakes  X	Brake_x_on	High  =  hold  
    if(HAL_GPIO_ReadPin(BRAKE_X_PORT, BRAKE_X_PIN) == GPIO_PIN_RESET)
      HAL_GPIO_WritePin(BRAKE_X_ON_N_PORT, BRAKE_X_ON_N_PIN, GPIO_PIN_SET);
    
    ////////////////////////////////////////////////////////////////////////////

    //Brake_rotate = H    Realize    brakes  X	Brake_x_on 	 Low  =  realize 
    if(HAL_GPIO_ReadPin(BRAKE_ROTATE_PORT, BRAKE_ROTATE_PIN) == GPIO_PIN_SET)
      HAL_GPIO_WritePin(BRAKE_X_ON_N_PORT, BRAKE_X_ON_N_PIN, GPIO_PIN_RESET);

    //Brake_rotate = Low Brakes  X on	Brake_x_on	High  =  hold  
    if(HAL_GPIO_ReadPin(BRAKE_ROTATE_PORT, BRAKE_ROTATE_PIN) == GPIO_PIN_RESET)
      HAL_GPIO_WritePin(BRAKE_X_ON_N_PORT, BRAKE_X_ON_N_PIN, GPIO_PIN_SET);
    
    ////////////////////////////////////////////////////////////////////////////
    
    //End_affecto = high   End_affecto move  in one direction	End_affecto_dir   High  = out 
    //End_affecto = low                                                           Low = in
    if(HAL_GPIO_ReadPin(END_AFFECTO_PORT, END_AFFECTO_PIN) == GPIO_PIN_SET)
      HAL_GPIO_WritePin(END_AFFECTO_DIR_PORT, END_AFFECTO_DIR_PIN, GPIO_PIN_SET);
    
    if(HAL_GPIO_ReadPin(END_AFFECTO_PORT, END_AFFECTO_PIN) == GPIO_PIN_RESET)
      HAL_GPIO_WritePin(END_AFFECTO_DIR_PORT, END_AFFECTO_DIR_PIN, GPIO_PIN_RESET);

    ////////////////////////////////////////////////////////////////////////////

    //Motor_n_forward=HIGH	Move  motor N forward 	Motor_n_ina  Motor_n_ina = 1
    //                                                  Motor_n_inb  Motor_n_inb=0
    if(HAL_GPIO_ReadPin(MOTOR_N_FORWARD_PORT, MOTOR_N_FORWARD_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(MOTOR_N_INA_PORT, MOTOR_N_INA_PIN, GPIO_PIN_SET);
      HAL_GPIO_WritePin(MOTOR_N_INB_PORT, MOTOR_N_INB_PIN, GPIO_PIN_RESET);
    }

    //Motor_n_backward=HIGH	Move  motor N backward 	Motor_n_ina   Motor_n_ina = 0
    //                                                  Motor_n_inb   Motor_n_inb=1
    if(HAL_GPIO_ReadPin(MOTOR_N_BACKWARD_PORT, MOTOR_N_BACKWARD_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(MOTOR_N_INA_PORT, MOTOR_N_INA_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_N_INB_PORT, MOTOR_N_INB_PIN, GPIO_PIN_SET);
    }

    //Motor_n_forward=Low   Motor n  stop   Motor_n_ina   Motor_n_ina = 0
    //Motor_n_backward=Low	            Motor_n_inb   Motor_n_inb=0
    if((HAL_GPIO_ReadPin(MOTOR_N_FORWARD_PORT, MOTOR_N_FORWARD_PIN) == GPIO_PIN_RESET) &&
      (HAL_GPIO_ReadPin(MOTOR_N_BACKWARD_PORT, MOTOR_N_BACKWARD_PIN) == GPIO_PIN_RESET))
    {
      HAL_GPIO_WritePin(MOTOR_N_INA_PORT, MOTOR_N_INA_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_N_INB_PORT, MOTOR_N_INB_PIN, GPIO_PIN_RESET);
    }

    /* USER CODE END WHILE */

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

  /** Supply configuration update enable
  */
  //HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 1;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_4BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x0;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

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
  huart1.Init.StopBits = UART_STOPBITS_1;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE4 PE5
                           PE6 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC13 PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PF0 PF1 PF2 PF3
                           PF4 PF5 PF6 PF7
                           PF8 PF9 PF10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11
                           PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PG2 PG3 PG4 PG5
                           PG6 PG7 PG8 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
