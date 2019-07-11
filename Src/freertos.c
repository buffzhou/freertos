/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
osThreadId_t keyHandle;
osThreadId_t led1Handle;
osThreadId_t led2Handle;
osMessageQueueId_t messageHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void keyfunction(void *argument); // for v2
void led1function(void *argument); // for v2
void led2function(void *argument); // for v2

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
osKernelInitialize(); // Initialize CMSIS-RTOS

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
  /* definition and creation of message */
  const osMessageQueueAttr_t message_attributes = {
    .name = "message"
  };
  messageHandle = osMessageQueueNew (16, sizeof(uint16_t), &message_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of key */
  const osThreadAttr_t key_attributes = {
    .name = "key",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 512
  };
  keyHandle = osThreadNew(keyfunction, NULL, &key_attributes);

  /* definition and creation of led1 */
  const osThreadAttr_t led1_attributes = {
    .name = "led1",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 512
  };
  led1Handle = osThreadNew(led1function, NULL, &led1_attributes);

  /* definition and creation of led2 */
  const osThreadAttr_t led2_attributes = {
    .name = "led2",
    .priority = (osPriority_t) osPriorityLow,
    .stack_size = 512
  };
  led2Handle = osThreadNew(led2function, NULL, &led2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_keyfunction */
/**
  * @brief  Function implementing the key thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_keyfunction */
void keyfunction(void *argument)
{

  /* USER CODE BEGIN keyfunction */
	uint16_t p;
  /* Infinite loop */
for(;;)
{p = 1;
osMessageQueuePut(messageHandle,(void *)&p,0,0);
osDelay(500);
p= 2;
osMessageQueuePut(messageHandle,(void *)&p,0,0);
osDelay(500);
}

  /* USER CODE END keyfunction */
}

/* USER CODE BEGIN Header_led1function */
/**
* @brief Function implementing the led1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_led1function */
void led1function(void *argument)
{
  /* USER CODE BEGIN led1function */
  /* Infinite loop */
	uint16_t p;
	osStatus_t sta;
	for(;;)
	{
  	sta = osMessageQueueGet (messageHandle, (void *)&p, 0, 100);
	if(sta == osOK)
	{

	if(p == 1){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_RESET);
		}
	else
	{
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET);
	  }
	}
	osDelay(1);
	}
  /* USER CODE END led1function */
}

/* USER CODE BEGIN Header_led2function */
/**
* @brief Function implementing the led2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_led2function */
void led2function(void *argument)
{
  /* USER CODE BEGIN led2function */
  /* Infinite loop */
	for(;;)
	{
	osDelay(1);
	}
  /* USER CODE END led2function */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
