//#ifndef _TASKS_H
//#define _TASKS_H
//#include "sys.h"
//#include "FreeRTOS.h"
//#include "time.h"
//#include "delay.h"
//#include "task.h"
//#include "queue.h"
//#include "usart.h"
//#include "usart3.h"
//#include "key.h"

//#endif

////按键消息队列的数量
//#define KEYMSG_Q_NUM    1  		//按键消息队列的数量  
//#define MESSAGE_Q_NUM   4   	//发送数据的消息队列的数量 
//#define MESSAGE3_Q_NUM   4   	//发送数据的消息队列的数量 
//QueueHandle_t Key_Queue;   		//按键值消息队列句柄
//QueueHandle_t Message_Queue;	//信息队列句柄
//QueueHandle_t Message3_Queue;	//信息队列句柄


////任务优先级
//#define START_TASK_PRIO		1
////任务堆栈大小	
//#define START_STK_SIZE 		256  
////任务句柄
//TaskHandle_t StartTask_Handler;
////任务函数
//void start_task(void *pvParameters);

////任务优先级
//#define TASK1_TASK_PRIO		2
////任务堆栈大小	
//#define TASK1_STK_SIZE 		256  
////任务句柄
//TaskHandle_t Task1Task_Handler;
////任务函数
//void task1_task(void *pvParameters);

////任务优先级
//#define NETWORK_TASK_PRIO		2
////任务堆栈大小	
//#define NETWORK_STK_SIZE 		256  
////任务句柄
//TaskHandle_t NetworkTask_Handler;
////任务函数
//void network_task(void *pvParameters);

////任务优先级
//#define KEYPROCESS_TASK_PRIO 3
////任务堆栈大小	
//#define KEYPROCESS_STK_SIZE  256 
////任务句柄
//TaskHandle_t Keyprocess_Handler;
////任务函数
//void Keyprocess_task(void *pvParameters);

