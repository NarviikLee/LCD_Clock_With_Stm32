/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "g_var.h"
#include "timer_mode.h"
#include "Potentiometer.h"
#include "timer_funs.h"
#include "dht11.h"
#include "alert_fs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// 버튼 인터럽트 입력 딜레이 타임 500ms
#define BUTTON_GAP 500
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
// 인터럽트 발생 시간 저장 함수
static uint32_t btn_time = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
// 1초 타이머 인터럽트 핸들러
extern TIM_HandleTypeDef htim3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */
  // 디바이스 모드 취득 함수 호출
  int now_mode = getMode();
  // if now mode is Modify, Don't Increase Second..
  // 디바이스 시간 및 날짜 변경 모드가 아닐 경우 시간 진행
  if(now_mode != 3){
	  clock_value[0] = ++device_second;
  }
  // 1분이 지날경우 디바이스 시간 업데이트
  if(device_second >=60){
	  // 디바이스 초 단위 초기화
	  device_second=0;
	  // 디바이스 time_t 업데이트
	  set_time_t();
	  // 디바이스 시간 배열 초 단위 업데이트(0)
	  clock_value[0]=device_second;
	  // 알람 설정 상태 확인
	  if(getAlarmState()){
		  // 알람이 설정했을 경우 알람시간 체크 함수 호출
		  check_Alarm();
	  }
  }
  // 타이머 설정을 했을 경우
  if(getTimerState() == 1){
	  // 초단위로 변경한 타이머 시간 감소(ex:01:30 -> 90초이므로 Timer_Second = 90)
	  Timer_Second--;
	  // 타이머 디스플레이 시간 업데이트
	  update_timer();
	  // 타이머 시간이 0이고, 타이머를 설정했을경우 (즉 타이머 종료)
	  if(Timer_Second == 0 && getTimerState()==1){
		  //타이머 종료 변수 업데이트
		  // LCD 변경 및 부저를 울리기 위해
		  setTimerCompleted(1);
		  // 부저 ON
		  start_Boozer(1);
	  }
  }

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  //디바이스 버튼 인터럽트 활성화
  HAL_GPIO_EXTI_IRQHandler(UP_B_Pin);
  HAL_GPIO_EXTI_IRQHandler(USER_Btn_Pin);
  HAL_GPIO_EXTI_IRQHandler(DOWN_B_Pin);
  HAL_GPIO_EXTI_IRQHandler(SEL_B_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
  //
  if((HAL_GetTick() - btn_time) > BUTTON_GAP){
	  // 디스플레이, 메뉴 이동 버튼(CANCEL) 인터럽트는 언제든 활성화(이전 프로세스 이동, 메뉴 선택 회귀등)
	  cancel_btn = HAL_GPIO_ReadPin(USER_Btn_GPIO_Port,USER_Btn_Pin);
	  // 메뉴 선택 모드 일때에 선택 커서 이동 인터럽트 활성화
	  if(getMode() >= 0){
		  up_btn = !HAL_GPIO_ReadPin(UP_B_GPIO_Port,UP_B_Pin);
		  down_btn = !HAL_GPIO_ReadPin(DOWN_B_GPIO_Port,DOWN_B_Pin);
		  select_btn = !HAL_GPIO_ReadPin(SEL_B_GPIO_Port,SEL_B_Pin);
	  }
  }
  btn_time = HAL_GetTick();
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */


/* USER CODE END 1 */
