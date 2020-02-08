//#include "time.h"
//#include "led.h"
//#include "malloc.h"
//#include "usart.h"
//#include "string.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"
//#include "remote.h"


//TIM_HandleTypeDef TIM3_Handler;	//TIM3��� 
//TIM_HandleTypeDef TIM9_Handler;	//TIM9���	
//TIM_HandleTypeDef TIM7_Handler;	//TIM7���

////FreeRTOSʱ��ͳ�����õĽ��ļ�����
//volatile unsigned long long FreeRTOSRunTimeTicks;

////��ʼ��TIM3ʹ��ΪFreeRTOS��ʱ��ͳ���ṩʱ��
//void ConfigureTimeForRunTimeStats(void)
//{
//	//��ʱ��3��ʼ������ʱ��ʱ��Ϊ90M����Ƶϵ��Ϊ90-1�����Զ�ʱ��3��Ƶ��
//	//Ϊ90M/90=1M���Զ���װ��Ϊ50-1����ô��ʱ�����ھ���50us
//	FreeRTOSRunTimeTicks=0;
//	TIM3_Init(50-1,90-1);	//��ʼ��TIM3
//}

////ͨ�ö�ʱ��3�жϳ�ʼ��
////arr���Զ���װֵ��
////psc��ʱ��Ԥ��Ƶ��
////��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
////Ft=��ʱ������Ƶ��,��λ:Mhz
////����ʹ�õ��Ƕ�ʱ��3!(��ʱ��3����APB1�ϣ�ʱ��ΪHCLK/2)
//void TIM3_Init(u16 arr,u16 psc)
//{  
//    TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��3
//    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
//    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
//    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
//    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
//    HAL_TIM_Base_Init(&TIM3_Handler);
//    
//    HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
//}
//void TIM7_Int_Init(u16 arr,u16 psc)
//{
//	TIM7_Handler.Instance=TIM7;                          //ͨ�ö�ʱ��3
//    TIM7_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
//    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
//    TIM7_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
//    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
//    HAL_TIM_Base_Init(&TIM7_Handler);
//    
//    HAL_TIM_Base_Start_IT(&TIM7_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE									 
//}
////ͨ�ö�ʱ��9�жϳ�ʼ��
////arr���Զ���װֵ��
////psc��ʱ��Ԥ��Ƶ��
////��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
////Ft=��ʱ������Ƶ��,��λ:Mhz
////����ʹ�õ��Ƕ�ʱ��9!(��ʱ��9����APB2�ϣ�ʱ��ΪHCLK)
//void TIM9_Init(u16 arr,u16 psc)
//{  
//    TIM9_Handler.Instance=TIM9;                          //ͨ�ö�ʱ��3
//    TIM9_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
//    TIM9_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
//    TIM9_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
//    TIM9_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
//    HAL_TIM_Base_Init(&TIM9_Handler);
//    
//    HAL_TIM_Base_Start_IT(&TIM9_Handler); //ʹ�ܶ�ʱ��9�Ͷ�ʱ��9�����жϣ�TIM_IT_UPDATE   
//}


////��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
////�˺����ᱻHAL_TIM_Base_Init()��������
//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
//{
//    if(htim->Instance==TIM3)
//	{
//		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
//		HAL_NVIC_SetPriority(TIM3_IRQn,6,0);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�0
//		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
//	}
//	else if(htim->Instance==TIM9)
//	{
//		__HAL_RCC_TIM9_CLK_ENABLE();            		//ʹ��TIM9ʱ��
//		HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn,6,0);  	//�����ж����ȼ�����ռ���ȼ�8
//		HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);         //����ITM9�ж�   
//	} 
//	else if(htim->Instance==TIM7)
//	{
//		__HAL_RCC_TIM7_CLK_ENABLE();            //ʹ��TIM7ʱ��
//		HAL_NVIC_SetPriority(TIM7_IRQn,6,0);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�0
//		HAL_NVIC_EnableIRQ(TIM7_IRQn);          //����ITM7�ж�   
//	}
//}


////��ʱ��3�жϷ�����
//void TIM3_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&TIM3_Handler);
//}
////��ʱ��7�жϷ�����
//void TIM7_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&TIM7_Handler);
//}
////��ʱ��9�жϷ�����
//void TIM1_BRK_TIM9_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&TIM9_Handler);
//}

//extern QueueHandle_t Message_Queue;	//��Ϣ���о��
//extern void disp_str(u8* str);

////�ص���������ʱ���жϷ���������
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{	u8 *buffer;
//	BaseType_t xTaskWokenByReceive=pdFALSE;
//	BaseType_t err;
//	extern  u8 RmtSta;
//	
//    if(htim==(&TIM3_Handler))
//    {
//        FreeRTOSRunTimeTicks++;
//    }
//	else if(htim==(&TIM9_Handler))
//	{
//		buffer=mymalloc(SRAMIN,USART_REC_LEN);
//        if(Message_Queue!=NULL)
//        {
//			memset(buffer,0,USART_REC_LEN);	//���������
//			err=xQueueReceiveFromISR(Message_Queue,buffer,&xTaskWokenByReceive);//������ϢMessage_Queue
//            if(err==pdTRUE)			//���յ���Ϣ
//            {
//				disp_str(buffer);	//��LCD����ʾ���յ�����Ϣ
//            }
//        }
//		myfree(SRAMIN,buffer);		//�ͷ��ڴ�
//		
//		portYIELD_FROM_ISR(xTaskWokenByReceive);//�����Ҫ�Ļ�����һ�������л�
//	}   
//	else if(htim==(&TIM7_Handler)){
//		USART3_RX_STA|=1<<15;	//��ǽ������
//		__HAL_TIM_CLEAR_FLAG(&TIM7_Handler,TIM_EventSource_Update );       //���TIM7�����жϱ�־  
//		TIM7->CR1&=~(1<<0);  
//	}   			//�رն�ʱ��7 
////	else if(htim->Instance==TIM1){
//// 		if(RmtSta&0x80)//�ϴ������ݱ����յ���
////		{	
////			RmtSta&=~0X10;						//ȡ���������Ѿ���������
////			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
////			if((RmtSta&0X0F)<14)RmtSta++;
////			else
////			{
////				RmtSta&=~(1<<7);//���������ʶ
////				RmtSta&=0XF0;	//��ռ�����	
////			}						 	   	
////		}	
//// 
//// }
//}
