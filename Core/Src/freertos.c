/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "network_interface.h" //kullanıcı kütüphanesi
#include "user_spi_w5500.h"    //Kullanıcı kütüphanesi
#include "motor_driver.h"      //kullanıcı kütüphanesi
#include "task_manager.h"      //kullanıcı kütüphanesi
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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Task_DispatchHandle;
osThreadId Task_NetCommHandle;
osThreadId Task_DriveRightHandle;
osThreadId Task_DriveLeftHandle;
osThreadId Task_DriveRampHandle;
osMessageQId Queue_NetCmdHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartMotorTask(void const *argument);
void StartNetworkTask(void const *argument);
void StartTask03(void const *argument);
void StartTask04(void const *argument);
void StartTask05(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of Queue_NetCmd */
  osMessageQDef(Queue_NetCmd, 3, uint8_t);
  Queue_NetCmdHandle = osMessageCreate(osMessageQ(Queue_NetCmd), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task_Dispatch */
  osThreadDef(Task_Dispatch, StartMotorTask, osPriorityRealtime, 0, 128);
  Task_DispatchHandle = osThreadCreate(osThread(Task_Dispatch), NULL);

  /* definition and creation of Task_NetComm */
  osThreadDef(Task_NetComm, StartNetworkTask, osPriorityNormal, 0, 128);
  Task_NetCommHandle = osThreadCreate(osThread(Task_NetComm), NULL);

  /* definition and creation of Task_DriveRight */
  osThreadDef(Task_DriveRight, StartTask03, osPriorityHigh, 0, 128);
  Task_DriveRightHandle = osThreadCreate(osThread(Task_DriveRight), NULL);

  /* definition and creation of Task_DriveLeft */
  osThreadDef(Task_DriveLeft, StartTask04, osPriorityLow, 0, 128);
  Task_DriveLeftHandle = osThreadCreate(osThread(Task_DriveLeft), NULL);

  /* definition and creation of Task_DriveRamp */
  osThreadDef(Task_DriveRamp, StartTask05, osPriorityHigh, 0, 128);
  Task_DriveRampHandle = osThreadCreate(osThread(Task_DriveRamp), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_StartMotorTask */
/**
 * @brief  Function implementing the Task_MotorCtrl thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartMotorTask */
void StartMotorTask(void const *argument)
{
  /* USER CODE BEGIN StartMotorTask */

  // Motorun initialize fonksiyonudur
  Motor_Init();

  /* Infinite loop */
  for (;;)
  {
    // Motor görevini işle
    TaskManager_Dispatch_Process();
    osDelay(10);
  }
  /* USER CODE END StartMotorTask */
}

/* USER CODE BEGIN Header_StartNetworkTask */
/**
 * @brief Function implementing the Task_NetComm thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartNetworkTask */
void StartNetworkTask(void const *argument)
{
  /* USER CODE BEGIN StartNetworkTask */

  // W5500 modulunun wiznet kutuphanesine göre initialize fonksiyonudur
  W5500_Hardware_Init();

  // Ağ donanımının statik IP ve MAC ayarlarını yükle
  Network_Init();

  // --- SAĞLAMA TESTİ EKLENTİSİ ---
  wiz_NetInfo read_info;
  wizchip_getnetinfo(&read_info);

  /* Infinite loop */
  for (;;)
  {

    // Client modu
    Network_AppClient();

    osDelay(1);
  }
  /* USER CODE END StartNetworkTask */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
 * @brief Function implementing the Task_DriveRight thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask03 */
void StartTask03(void const *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for (;;)
  {
    TaskManager_DriveRight_Process(); // sağ yön
    osDelay(10);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
 * @brief Function implementing the Task_DriveLeft thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask04 */
void StartTask04(void const *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for (;;)
  {
    TaskManager_DriveLeft_Process(); // sol yön
    osDelay(50);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
 * @brief Function implementing the Task_DriveRamp thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask05 */
void StartTask05(void const *argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for (;;)
  {
    TaskManager_DriveRamp_Process(); // rampalı sürüs ve blink
    osDelay(10);
  }
  /* USER CODE END StartTask05 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
