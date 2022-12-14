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
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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
#define ECOMILK_DEBUG           0
#if ECOMILK_DEBUG == 1
  #define DEBUG_PRINT           printf
#else
  #define DEBUG_PRINT
#endif
#define ECOMILK_DEBUG_TIMEOUT   10
#define ECOMILK_TIMEOUT         ECOMILK_DEBUG_TIMEOUT
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

//Inputs
#define	ACTUATOR_BACKWARD_COM_PORT      GPIOE
#define	ACTUATOR_BACKWARD_COM_PIN       GPIO_PIN_12
#define	ACTUATOR_FORWARD_COM_PORT       GPIOE
#define	ACTUATOR_FORWARD_COM_PIN        GPIO_PIN_11
#define	ROTATE_Z_CW_COM_PORT            GPIOE
#define	ROTATE_Z_CW_COM_PIN             GPIO_PIN_10
#define	ROTATE_Z_CCW_COM_PORT           GPIOE
#define	ROTATE_Z_CCW_COM_PIN            GPIO_PIN_9
#define	TILT_CCW_COM_PORT               GPIOE
#define	TILT_CCW_COM_PIN                GPIO_PIN_8
#define	TILT_CW_COM_PORT                GPIOE
#define	TILT_CW_COM_PIN                 GPIO_PIN_7
#define	MOTOR_Z_DOWN_COM_PORT           GPIOE
#define	MOTOR_Z_DOWN_COM_PIN            GPIO_PIN_6
#define	MOTOR_Z_UP_COM_PORT             GPIOE
#define	MOTOR_Z_UP_COM_PIN              GPIO_PIN_5
#define	ACTUATOR_Y_BACKWARD_COM_PORT    GPIOE
#define	ACTUATOR_Y_BACKWARD_COM_PIN     GPIO_PIN_4
#define	ACTUATOR_Y_FORWARD_COM_PORT     GPIOE
#define	ACTUATOR_Y_FORWARD_COM_PIN      GPIO_PIN_3
#define	X_BACKWARD_COM_PORT             GPIOE
#define	X_BACKWARD_COM_PIN              GPIO_PIN_2
#define	X_FORWARD_COM_PORT              GPIOE
#define	X_FORWARD_COM_PIN               GPIO_PIN_1

//Outputs
#define	CS_N_PORT                       GPIOB
#define	CS_N_PIN                        GPIO_PIN_8
#define	MOT_M1_PORT                     GPIOD
#define	MOT_M1_PIN                      GPIO_PIN_6

#define DIR_MOTOR_Z                             1
#define DIR_MOTOR_TILT                          2
#define DIR_MOTOR_ROTATE                        3
#define DIR_MOTOR_X                             4
#define DIR_MOTOR_1                             5
#define DIR_MOTOR_2                             6
#define DIR_MOTOR_Y                             7
#define DIR_MOTOR_SP_1                          0
#define DIR_MOTOR_END_AFFECTO                   1
#define DIR_MOTOR_END_AFFECTO_A_1_2_3_4         2

#define LIN_MOTOR_Y                             1
#define LIN_MOTOR_SP_1                          2
#define LIN_MOTOR_END_AFFECTO                   3
#define LIN_MOTOR_END_AFFECTO_2                 4
#define LIN_MOTOR_END_AFFECTO_3                 5
#define LIN_MOTOR_END_AFFECTO_4                 6

#define DEC0                                    5
#define DEC1                                    6
#define DEC2                                    7

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc2;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim8;
DMA_HandleTypeDef hdma_tim3_ch1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;

/* USER CODE BEGIN PV */

static volatile int tim8_falling = 0;
static volatile int tim8_rising = 0;
static volatile int tim8_delta = 0;

uint8_t ecomilk[] = {'\r', '\n', 'E', 'c', 'o', 'M', 'i', 'l', 'k', '\r', '\n'};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC2_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM8_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void cmd_send_32(uint8_t dir_0, uint8_t dir_1, uint8_t cmd_0, uint8_t cmd_1)
{
  uint8_t data[4];
  uint8_t rdata[4];
  memset(data, 0, sizeof(data));
  data[0] = dir_1;
  data[1] = dir_0;
  data[2] = cmd_1;
  data[3] = cmd_0;
  HAL_GPIO_WritePin(CS_N_PORT, CS_N_PIN, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, data, rdata, sizeof(data), 500);
  //HAL_SPI_Transmit(&hspi2, data, sizeof(data), 500);
  HAL_GPIO_WritePin(CS_N_PORT, CS_N_PIN, GPIO_PIN_SET);
}

void cmd_send_16(uint8_t cmd_0, uint8_t cmd_1)
{
  uint8_t data[2];
  uint8_t rdata[2];
  memset(data, 0, sizeof(data));
  data[0] = cmd_1;
  data[1] = cmd_0;
  HAL_GPIO_WritePin(CS_N_PORT, CS_N_PIN, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, data, rdata, sizeof(data), 500);
  //HAL_SPI_Transmit(&hspi2, data, sizeof(data), 500);
  HAL_GPIO_WritePin(CS_N_PORT, CS_N_PIN, GPIO_PIN_SET);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM8)
  {
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
      tim8_falling = READ_REG(htim->Instance->CCR1);
    else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
      tim8_rising = READ_REG(htim->Instance->CCR2);
    
    if(tim8_falling > tim8_rising)
      tim8_delta = tim8_falling - tim8_rising;
  }
}

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
  MX_USART1_UART_Init();
  MX_ADC2_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART3_UART_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

  volatile uint16_t pData_3_1[] = {0x1111, 0x2222};
  //volatile uint16_t* pData_3_1_0 = &pData_3_1[0];
  //volatile uint16_t* pData_3_1_1 = &pData_3_1[1];
  int period_measured = 0;
  int period = 0;
  HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t*)pData_3_1, sizeof(pData_3_1));

  HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_2);

  uint8_t pDataTx[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa};
  uint8_t pDataRx[10];
  uint8_t pDataTx_USART3_DMA[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa};
  uint8_t pDataRx_USART3_DMA[10];
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  bool actuator_backward = false;
  bool actuator_forward = false;
  bool rotate_z_cw = false;
  bool rotate_z_ccw = false;
  bool tilt_ccw = false;
  bool tilt_cw = false;
  bool motor_z_down = false;
  bool motor_z_up = false;
  bool actuator_y_backward = false;
  bool actuator_y_forward = false;
  bool x_backward = false;
  bool x_forward = false;
  
  while (1)
  {
    if(__HAL_DMA_GET_FLAG(&hdma_tim3_ch1, DMA_FLAG_TCIF0_4) != 0U)
    {
      //period_measured = *pData_3_1_1 - *pData_3_1_0;
      period_measured = pData_3_1[1] - pData_3_1[0];
      if((period <= 0) || ((period_measured > 0) && (period_measured < (period * 2))))
        period = period_measured;
      printf("period %d\n", period);
    }
    
    // 1, 2
    //if(HAL_GPIO_ReadPin(ACTUATOR_BACKWARD_COM_PORT, ACTUATOR_BACKWARD_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!actuator_backward)
      {
        actuator_backward = true;
        cmd_send_32(0x00, 0x00 | (0x01 << DEC0), 0x00 | (0x01 << LIN_MOTOR_SP_1), 0x00 | (0x01 << DEC0) | (0x01 << DEC1));
      }
    }
    //else
    {
      if(actuator_backward)
      {
        actuator_backward = false;
        cmd_send_16(0x00, 0x00 | (0x01 << DEC0) | (0x01 << DEC1));
      }
    }

    // 3, 4
    //if(HAL_GPIO_ReadPin(ACTUATOR_FORWARD_COM_PORT, ACTUATOR_FORWARD_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!actuator_forward)
      {
        actuator_forward = true;
        cmd_send_32(0x00, 0x00 | (1 << DIR_MOTOR_SP_1) | (1 << DEC0), 0x00 | (1 << LIN_MOTOR_SP_1), 0x00 | (1 << DEC0) | (1 << DEC1));
      }
    }
    //else
    {
      if(actuator_forward)
      {
        actuator_forward = false;
        cmd_send_16(0x00 ,0x00 | (1 << DEC0) | (1 << DEC1));
      }
    }
    
    // 5, 6
    //if(HAL_GPIO_ReadPin(ROTATE_Z_CW_COM_PORT, ROTATE_Z_CW_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!rotate_z_cw)
      {
        rotate_z_cw = true;
        cmd_send_32(0x00 | (1 << DIR_MOTOR_ROTATE), 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_ROTATE), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(rotate_z_cw)
      {
        rotate_z_cw = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }
    
    // 7, 8
    //if(HAL_GPIO_ReadPin(ROTATE_Z_CCW_COM_PORT, ROTATE_Z_CCW_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!rotate_z_ccw)
      {
        rotate_z_ccw = true;
        cmd_send_32(0x00, 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_ROTATE), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(rotate_z_ccw)
      {
        rotate_z_ccw = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }
    
    // 9, 10
    //if(HAL_GPIO_ReadPin(TILT_CCW_COM_PORT, TILT_CCW_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!tilt_ccw)
      {
        tilt_ccw = true;
        cmd_send_32(0x00, 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_TILT), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(tilt_ccw)
      {
        tilt_ccw = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }
    
    // 11, 12
    //if(HAL_GPIO_ReadPin(TILT_CW_COM_PORT, TILT_CW_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!tilt_cw)
      {
        tilt_cw = true;
        cmd_send_32(0x00 | (1 << DIR_MOTOR_TILT), 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_TILT), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(tilt_cw)
      {
        tilt_cw = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }
    // 13, 14
    //if(HAL_GPIO_ReadPin(MOTOR_Z_DOWN_COM_PORT, MOTOR_Z_DOWN_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!motor_z_down)
      {
        motor_z_down = true;
        cmd_send_32(0x00, 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_Z), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(motor_z_down)
      {
        motor_z_down = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }
    
    // 15, 16
    //if(HAL_GPIO_ReadPin(MOTOR_Z_UP_COM_PORT, MOTOR_Z_UP_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!motor_z_up)
      {
        motor_z_up = true;
        cmd_send_32(0x00 | (1 << DIR_MOTOR_Z), 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_Z), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(motor_z_up)
      {
        motor_z_up = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }
    
    // 17, 18
    //if(HAL_GPIO_ReadPin(ACTUATOR_Y_BACKWARD_COM_PORT, ACTUATOR_Y_BACKWARD_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!actuator_y_backward)
      {
        actuator_y_backward = true;
        cmd_send_32(0x00, 0x00 | (1 << DEC0), 0x00 | (1 << LIN_MOTOR_Y), 0x00 | (1 << DEC0) | (1 << DEC1));
      }
    }
    //else
    {
      if(actuator_y_backward)
      {
        actuator_y_backward = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC0) | (1 << DEC1));
      }
    }
    
    // 19, 20
    //if(HAL_GPIO_ReadPin(ACTUATOR_Y_FORWARD_COM_PORT, ACTUATOR_Y_FORWARD_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!actuator_y_forward)
      {
        actuator_y_forward = true;
        cmd_send_32(0x00 | (1 << DIR_MOTOR_Y), 0x00 | (1 << DEC0), 0x00 | (1 << LIN_MOTOR_Y), 0x00 | (1 << DEC0) | (1 << DEC1));
      }
    }
    //else
    {
      if(actuator_y_forward)
      {
        actuator_y_forward = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC0) | (1 << DEC1));
      }
    }

    // 21, 22
    //if(HAL_GPIO_ReadPin(X_BACKWARD_COM_PORT, X_BACKWARD_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!x_backward)
      {
        x_backward = true;
        cmd_send_32(0x00, 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_X), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(x_backward)
      {
        x_backward = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }

    // 23, 24
    //if(HAL_GPIO_ReadPin(X_FORWARD_COM_PORT, X_FORWARD_COM_PIN) == GPIO_PIN_SET)
    {  
      if(!x_forward)
      {
        x_forward = true;
        cmd_send_32(0x00 | (1 << DIR_MOTOR_X), 0x00 | (1 << DEC0), 0x00 | (1 << DIR_MOTOR_X), 0x00 | (1 << DEC1));
      }
    }
    //else
    {
      if(x_forward)
      {
        x_forward = false;
        cmd_send_16(0x00, 0x00 | (1 << DEC1));
      }
    }
    
    //for(int i = 0; i < 1000; i++);
    
    // Working
     
    HAL_UART_Transmit(&huart1, ecomilk, sizeof(ecomilk), ECOMILK_TIMEOUT);
    HAL_UART_Receive(&huart1, ecomilk, sizeof(ecomilk), ECOMILK_TIMEOUT);
    for(int i = 0; i < sizeof(ecomilk); i++)
      printf("%x ", ecomilk[i]);
    printf("\n");

   
    // USART1 Fifo enabled
    memset(pDataRx, 0, sizeof(pDataRx));
    for(int i = 0; i < 10; i++)
    {
      HAL_UART_Transmit(&huart1, &pDataTx[i], 1, 10);
      HAL_UART_Receive(&huart1, &pDataRx[i], 1, 10);
    }
    
    memset(pDataRx, 0, sizeof(pDataRx));
    HAL_UART_Transmit(&huart1, pDataTx, sizeof(pDataTx), 10);
    HAL_UART_Receive(&huart1, pDataRx, sizeof(pDataRx), 10);
  
    memset(pDataRx, 0, sizeof(pDataRx));
    HAL_SPI_TransmitReceive(&hspi2, pDataTx, pDataRx, sizeof(pDataTx), 10);
    
    memset(pDataRx, 0, sizeof(pDataRx));
    HAL_SPI_Transmit(&hspi2, pDataTx, sizeof(pDataTx), 10);
    HAL_SPI_Receive(&hspi2, pDataRx, sizeof(pDataRx), 10);
    
    memset(pDataRx, 0, sizeof(pDataRx));
    for(int i = 0; i < 10; i++)
    {
      HAL_SPI_Transmit(&hspi2, &pDataTx[i], 1, 10);
      HAL_SPI_Receive(&hspi2, &pDataRx[i], 1, 10);
    }
      
    // USART3 Fifo disabled
    memset(pDataRx_USART3_DMA, 0, sizeof(pDataRx_USART3_DMA));
    HAL_UART_Transmit_DMA(&huart3, pDataTx_USART3_DMA, sizeof(pDataTx_USART3_DMA));
    HAL_UART_Receive_DMA(&huart3, pDataRx_USART3_DMA, sizeof(pDataRx_USART3_DMA));
    for(int i = 0; i < sizeof(pDataRx_USART3_DMA); i++)
      printf("%x ", pDataRx_USART3_DMA[i]);
    printf("\n");

    for(int i = 0; i < 1000; i++);

#if 0

    // Working
     
    {
      memset(pDataRx, 0, sizeof(pDataRx));
      for(int i = 0; i < 10; i++)
      {
        HAL_UART_Transmit(&huart3, &pDataTx[i], 1, 10);
        HAL_UART_Receive(&huart3, &pDataRx[i], 1, 10);
      }
    }
    
    //Not working
    {
      memset(pDataRx, 0, sizeof(pDataRx));
      HAL_UART_Transmit(&huart3, pDataTx, sizeof(pDataTx), 10);
      HAL_UART_Receive(&huart3, pDataRx, sizeof(pDataRx), 10);
    }

#endif    

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
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);
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
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */
  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc2.Init.Resolution = ADC_RESOLUTION_16B;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;
  hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc2.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
  hadc2.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  sConfig.OffsetSignedSaturation = DISABLE;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 0x0;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi2.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
  htim1.Init.Period = 64000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 32000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
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
  htim2.Init.Period = 4000;
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
  sConfigOC.Pulse = 2000;
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
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 0;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 65535;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim8, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim8, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */

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
  if (HAL_UARTEx_EnableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE4 PE5
                           PE6 PE7 PE8 PE9
                           PE10 PE11 PE12 PE0
                           PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_0
                          |GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 PA8
                           PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_8
                          |GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PD3 PD4 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PD5 PD6 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PB3 PB4 PB5 PB6
                           PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
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
