//#include "tasks.h"

//void start_task(void *pvParameters)
//{
//    taskENTER_CRITICAL();           //�����ٽ���
//	
//	//������Ϣ����
//    Key_Queue=xQueueCreate(KEYMSG_Q_NUM,sizeof(u8));        //������ϢKey_Queue
//    Message_Queue=xQueueCreate(MESSAGE_Q_NUM,USART_REC_LEN); //������ϢMessage_Queue,��������Ǵ��ڽ��ջ���������
//	Message3_Queue=xQueueCreate(MESSAGE3_Q_NUM,USART3_MAX_RECV_LEN);
//    //����TASK1����
//    xTaskCreate((TaskFunction_t )task1_task,             
//                (const char*    )"task1_task",           
//                (uint16_t       )TASK1_STK_SIZE,        
//                (void*          )NULL,                  
//                (UBaseType_t    )TASK1_TASK_PRIO,        
//                (TaskHandle_t*  )&Task1Task_Handler); 
//				
//	xTaskCreate((TaskFunction_t )network_task,             
//                (const char*    )"network_task",           
//                (uint16_t       )NETWORK_STK_SIZE,        
//                (void*          )NULL,                  
//                (UBaseType_t    )NETWORK_TASK_PRIO,        
//                (TaskHandle_t*  )&NetworkTask_Handler);				
//    //����TASK2����
//    xTaskCreate((TaskFunction_t )Keyprocess_task,     
//                (const char*    )"keyprocess_task",   
//                (uint16_t       )KEYPROCESS_STK_SIZE,
//                (void*          )NULL,
//                (UBaseType_t    )KEYPROCESS_TASK_PRIO,
//                (TaskHandle_t*  )&Keyprocess_Handler); 
//    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
//    taskEXIT_CRITICAL();            //�˳��ٽ���
//}



////task1������
//void task1_task(void *pvParameters)
//{
//	//atk_8266_test();
//	//atk_8266_wifista_test();
//	//atk_8266_wifista_test1();
//	//wifi_sta_tcp_c();
//	while(1)
//	{
//		
//		//atk_8266_quit_trans();
//		if(KEY_Scan(0)==KEY1_PRES){
//// 			wav_recorder();
////			LCD_Fill(30,190,240,480,WHITE);//�����ʾ
//		}            
//       
//        vTaskDelay(10);                           //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
//	}
//	
//	
//}

//void network_task(void *pvParameters){

//	 while(1)
//	{

//		
//		vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
//	}

//}

////Keyprocess_task����
//void Keyprocess_task(void *pvParameters)
//{   
//	
//	while(1)
//	{

//		
//		vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
//	}
//}



