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

////������Ϣ���е�����
//#define KEYMSG_Q_NUM    1  		//������Ϣ���е�����  
//#define MESSAGE_Q_NUM   4   	//�������ݵ���Ϣ���е����� 
//#define MESSAGE3_Q_NUM   4   	//�������ݵ���Ϣ���е����� 
//QueueHandle_t Key_Queue;   		//����ֵ��Ϣ���о��
//QueueHandle_t Message_Queue;	//��Ϣ���о��
//QueueHandle_t Message3_Queue;	//��Ϣ���о��


////�������ȼ�
//#define START_TASK_PRIO		1
////�����ջ��С	
//#define START_STK_SIZE 		256  
////������
//TaskHandle_t StartTask_Handler;
////������
//void start_task(void *pvParameters);

////�������ȼ�
//#define TASK1_TASK_PRIO		2
////�����ջ��С	
//#define TASK1_STK_SIZE 		256  
////������
//TaskHandle_t Task1Task_Handler;
////������
//void task1_task(void *pvParameters);

////�������ȼ�
//#define NETWORK_TASK_PRIO		2
////�����ջ��С	
//#define NETWORK_STK_SIZE 		256  
////������
//TaskHandle_t NetworkTask_Handler;
////������
//void network_task(void *pvParameters);

////�������ȼ�
//#define KEYPROCESS_TASK_PRIO 3
////�����ջ��С	
//#define KEYPROCESS_STK_SIZE  256 
////������
//TaskHandle_t Keyprocess_Handler;
////������
//void Keyprocess_task(void *pvParameters);

