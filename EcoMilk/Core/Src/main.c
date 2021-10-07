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
#define REALIZE_BRAKES_PORT              GPIOA
#define MOTOR_Z_UP_PORT                  GPIOA
#define MOTOR_Z_DOWN_PORT                GPIOA
#define MOTOR_Z_LIMIT_UP_PORT            GPIOA
#define MOTOR_Z_LIMIT_DOWN_PORT          GPIOA
#define MOTOR_TILT_UP_PORT               GPIOB
#define MOTOR_TILT_DOWN_PORT             GPIOB
#define MOTOR_TILT_LIMIT_UP_PORT         GPIOB
#define MOTOR_TILT_LIMIT_DOWN_PORT       GPIOB
#define BRAKE_X_PORT                     GPIOB
#define BRAKE_ROTATE_PORT                GPIOB
#define BRAKE_SPARE_A_PORT               GPIOB
#define BRAKE_SPARE_B_PORT               GPIOB
#define BRAKE_SPARE_C_PORT               GPIOB
#define BRAKE_SPARE_D_PORT               GPIOB
#define END_AFFECTO_PORT                 GPIOB
#define NFAULT_GLOBAL_PORT               GPIOB
#define MOTOR_N_FORWARD_PORT             GPIOB
#define MOTOR_N_BACKWARD_PORT            GPIOB

#define REALIZE_BRAKES_PIN              GPIO_PIN_9
#define MOTOR_Z_UP_PIN                  GPIO_PIN_10
#define MOTOR_Z_DOWN_PIN                GPIO_PIN_11
#define MOTOR_Z_LIMIT_UP_PIN            GPIO_PIN_12
#define MOTOR_Z_LIMIT_DOWN_PIN          GPIO_PIN_15
#define MOTOR_TILT_UP_PIN               GPIO_PIN_0
#define MOTOR_TILT_DOWN_PIN             GPIO_PIN_1
#define MOTOR_TILT_LIMIT_UP_PIN         GPIO_PIN_2
#define MOTOR_TILT_LIMIT_DOWN_PIN       GPIO_PIN_3
#define BRAKE_X_PIN                     GPIO_PIN_4
#define BRAKE_ROTATE_PIN                GPIO_PIN_5
#define BRAKE_SPARE_A_PIN               GPIO_PIN_6
#define BRAKE_SPARE_B_PIN               GPIO_PIN_7
#define BRAKE_SPARE_C_PIN               GPIO_PIN_8
#define BRAKE_SPARE_D_PIN               GPIO_PIN_9
#define END_AFFECTO_PIN                 GPIO_PIN_10
#define NFAULT_GLOBAL_PIN               GPIO_PIN_11
#define MOTOR_N_FORWARD_PIN             GPIO_PIN_12
#define MOTOR_N_BACKWARD_PIN            GPIO_PIN_13

// Outputs
#define ENABLE_BRAKES_PORT       GPIOB
#define BRAKE_Z_ON_N_PORT        GPIOB	
#define BRAKE_X_ON_N_PORT        GPIOC	
#define BRAKE_TILT_ON_N_PORT     GPIOC
#define BRAKE_ROTATE_ON_PORT     GPIOC
#define BRAKE_SPARE_A_ON_PORT    GPIOC
#define BRAKE_SPARE_B_ON_PORT    GPIOC
#define BRAKE_SPARE_C_ON_PORT    GPIOC
#define BRAKE_SPARE_D_ON_PORT    GPIOC
#define MOTOR_Z_DIR_PORT         GPIOC
#define MOTOR_Z_ENABLE_PORT      GPIOC
#define MOTOR_TILT_DIR_PORT      GPIOC
#define MOTOR_TILT_ENABLE_PORT   GPIOC
#define END_AFFECTO_DIR_PORT     GPIOC
#define MOTOR_N_INA_PORT         GPIOC
#define MOTOR_N_INB_PORT         GPIOC
#define SPARE_ENABLE_A_PORT      GPIOC
#define SPARE_ENABLE_B_PORT      GPIOC

#define ENABLE_BRAKES_PIN       GPIO_PIN_14
#define BRAKE_Z_ON_N_PIN        GPIO_PIN_15	
#define BRAKE_X_ON_N_PIN        GPIO_PIN_0	
#define BRAKE_TILT_ON_N_PIN     GPIO_PIN_1
#define BRAKE_ROTATE_ON_PIN     GPIO_PIN_2
#define BRAKE_SPARE_A_ON_PIN    GPIO_PIN_3
#define BRAKE_SPARE_B_ON_PIN    GPIO_PIN_4
#define BRAKE_SPARE_C_ON_PIN    GPIO_PIN_5
#define BRAKE_SPARE_D_ON_PIN    GPIO_PIN_6
#define MOTOR_Z_DIR_PIN         GPIO_PIN_7
#define MOTOR_Z_ENABLE_PIN      GPIO_PIN_8
#define MOTOR_TILT_DIR_PIN      GPIO_PIN_9
#define MOTOR_TILT_ENABLE_PIN   GPIO_PIN_10
#define END_AFFECTO_DIR_PIN     GPIO_PIN_11
#define MOTOR_N_INA_PIN         GPIO_PIN_12
#define MOTOR_N_INB_PIN         GPIO_PIN_13
#define SPARE_ENABLE_A_PIN      GPIO_PIN_14
#define SPARE_ENABLE_B_PIN      GPIO_PIN_15

//#define Spare_enable_b_Pin GPIO_PIN_15
//#define Spare_enable_b_GPIO_Port GPIOC

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
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
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    
    //Realize_brakes  = high 	Realize  all  brakes  	Enable_brakes_n	High= realize 
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
      //HAL_TIMEx_PWMN_Start(&htim1, 1);
      HAL_TIMEx_OnePulseN_Start(&htim1, 1);
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_SET);
    }
    
    //Motor_z_down = H  Realize    brakes Z     Brake_z_on      Low  =  realize 
    //                  Motor   Z  dir  = 0     Motor_Z _dir    low= down
    //                  Motor   Z  step pwm     Motor_Z _step   Pwm  1khz
    //                                          Motor _z_enable Enable = high  
    if(HAL_GPIO_ReadPin(MOTOR_Z_DOWN_PORT, MOTOR_Z_DOWN_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(BRAKE_Z_ON_N_PORT, BRAKE_Z_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_Z_DIR_PORT, MOTOR_Z_DIR_PIN, GPIO_PIN_RESET);
      //HAL_TIMEx_PWMN_Start(&htim1, 1);
      HAL_TIMEx_OnePulseN_Start(&htim1, 1);
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_SET);
    }
    
    //Motor_z_up =low    Brake z  on    B Motor_Z _step  High  =  hold
    //Motor_z_down =low  Motor z  stop  brake_z_on       Low = stop
    //                                  Motor _z_enable  Disable = low
    if((HAL_GPIO_ReadPin(MOTOR_Z_UP_PORT, MOTOR_Z_UP_PIN) == GPIO_PIN_RESET) &&
       (HAL_GPIO_ReadPin(MOTOR_Z_DOWN_PORT, MOTOR_Z_DOWN_PIN) == GPIO_PIN_RESET))
    {
      HAL_TIMEx_PWMN_Start(&htim1, 1);
      HAL_GPIO_WritePin(BRAKE_Z_ON_N_PORT, BRAKE_Z_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_RESET);
    }

    //Motor_z_limit_up = high   move up   Motor_z_enable  Disable = low  
    //And  motor_z= up	Limit
    if((HAL_GPIO_ReadPin(MOTOR_Z_LIMIT_UP_PORT, MOTOR_Z_LIMIT_UP_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_Z_UP_PORT, MOTOR_Z_UP_PIN) == GPIO_PIN_SET))
      HAL_GPIO_WritePin(MOTOR_Z_ENABLE_PORT, MOTOR_Z_ENABLE_PIN, GPIO_PIN_RESET);
  
    //Motor_z_limit_Down = high   Limit  move down      Motor_z_enable 	Disable = low  
    //And  motor_z= down	
    if((HAL_GPIO_ReadPin(MOTOR_Z_LIMIT_DOWN_PORT, MOTOR_Z_LIMIT_DOWN_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_Z_UP_PORT, MOTOR_Z_UP_PIN) == GPIO_PIN_RESET))
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
      HAL_TIMEx_OnePulseN_Start(&htim2, 1);
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_SET);
    }
	
    //Motor_tilt_down =H   Realize brakes  tilt        Brake_tiltz_on 	   Low  =  realize 
    //                     Motor   tilt  dir  = 0      Motor_tilt_dir      low= down
    //                     Motor   tilt  step  pwm     Motor_tilt_step     Pwm  1khz
    //                                                 Motor_tilt_enable   Enable = high
    if(HAL_GPIO_ReadPin(MOTOR_TILT_DOWN_PORT, MOTOR_TILT_DOWN_PIN) == GPIO_PIN_SET)
    {
      HAL_GPIO_WritePin(BRAKE_TILT_ON_N_PORT, BRAKE_TILT_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_TILT_DIR_PORT, MOTOR_TILT_DIR_PIN, GPIO_PIN_RESET);
      HAL_TIMEx_OnePulseN_Start(&htim2, 1);
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_SET);
    }

    //Motor_tilt_up =low     Brake tilt  on    Motor_tilt_step     High  =  hold
    //Motor_tilt_down =low   Motor tilt stop   brake_tilt_on       Low = stop
    //                                         Motor_tilt_enable   Disable= low
    if((HAL_GPIO_ReadPin(MOTOR_TILT_UP_PORT, MOTOR_TILT_UP_PIN) == GPIO_PIN_RESET) &&
       (HAL_GPIO_ReadPin(MOTOR_TILT_DOWN_PORT, MOTOR_TILT_DOWN_PIN) == GPIO_PIN_RESET))
    {
      HAL_TIMEx_PWMN_Start(&htim2, 1);
      HAL_GPIO_WritePin(BRAKE_TILT_ON_N_PORT, BRAKE_TILT_ON_N_PIN, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_RESET);
    }

    //Motor_tilt_limit_up = high        Limit  move up 	Motor_tilt_enable	Disable= low
    //And  motor_tilt= up	        
    if((HAL_GPIO_ReadPin(MOTOR_TILT_LIMIT_UP_PORT, MOTOR_TILT_LIMIT_UP_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_TILT_UP_PORT, MOTOR_TILT_UP_PIN) == GPIO_PIN_SET))
      HAL_GPIO_WritePin(MOTOR_TILT_ENABLE_PORT, MOTOR_TILT_ENABLE_PIN, GPIO_PIN_RESET);

    //Motor_tilit_limit_Down = high   Limit  move down	Motor_tilt_enable	Disable= low
    //And  motor_tilt= down	        
    if((HAL_GPIO_ReadPin(MOTOR_TILT_LIMIT_DOWN_PORT, MOTOR_TILT_LIMIT_DOWN_PIN) == GPIO_PIN_SET) &&
       (HAL_GPIO_ReadPin(MOTOR_TILT_DOWN_PORT, MOTOR_TILT_DOWN_PIN) == GPIO_PIN_RESET))
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

    //Brake_ rotate = Low Brakes  X on	Brake_x_on	High  =  hold  
    if(HAL_GPIO_ReadPin(BRAKE_ROTATE_PORT, BRAKE_ROTATE_PIN) == GPIO_PIN_RESET)
      HAL_GPIO_WritePin(BRAKE_X_ON_N_PORT, BRAKE_X_ON_N_PIN, GPIO_PIN_SET);
    
    ////////////////////////////////////////////////////////////////////////////
    
    //End_affecto = high   End_affecto move  in one direction	End_affecto_dir   High  = out 
    //                                                                            Low = in
    if(HAL_GPIO_ReadPin(END_AFFECTO_PORT, END_AFFECTO_PIN) == GPIO_PIN_RESET)
      HAL_GPIO_WritePin(END_AFFECTO_DIR_PORT, END_AFFECTO_DIR_PIN, GPIO_PIN_SET);

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

    //
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
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

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
  sConfigOC.Pulse = 1000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  huart2.Init.BaudRate = 38400;
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 PC0
                           PC1 PC2 PC3 PC4
                           PC5 PC6 PC7 PC8
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB3
                           PB4 PB5 PB6 PB7
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
