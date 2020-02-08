//#include "time.h"
//#include "led.h"
//#include "malloc.h"
//#include "usart.h"
//#include "string.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"
//#include "remote.h"


//TIM_HandleTypeDef TIM3_Handler;	//TIM3句柄 
//TIM_HandleTypeDef TIM9_Handler;	//TIM9句柄	
//TIM_HandleTypeDef TIM7_Handler;	//TIM7句柄

////FreeRTOS时间统计所用的节拍计数器
//volatile unsigned long long FreeRTOSRunTimeTicks;

////初始化TIM3使其为FreeRTOS的时间统计提供时基
//void ConfigureTimeForRunTimeStats(void)
//{
//	//定时器3初始化，定时器时钟为90M，分频系数为90-1，所以定时器3的频率
//	//为90M/90=1M，自动重装载为50-1，那么定时器周期就是50us
//	FreeRTOSRunTimeTicks=0;
//	TIM3_Init(50-1,90-1);	//初始化TIM3
//}

////通用定时器3中断初始化
////arr：自动重装值。
////psc：时钟预分频数
////定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
////Ft=定时器工作频率,单位:Mhz
////这里使用的是定时器3!(定时器3挂在APB1上，时钟为HCLK/2)
//void TIM3_Init(u16 arr,u16 psc)
//{  
//    TIM3_Handler.Instance=TIM3;                          //通用定时器3
//    TIM3_Handler.Init.Prescaler=psc;                     //分频系数
//    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
//    TIM3_Handler.Init.Period=arr;                        //自动装载值
//    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
//    HAL_TIM_Base_Init(&TIM3_Handler);
//    
//    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
//}
//void TIM7_Int_Init(u16 arr,u16 psc)
//{
//	TIM7_Handler.Instance=TIM7;                          //通用定时器3
//    TIM7_Handler.Init.Prescaler=psc;                     //分频系数
//    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
//    TIM7_Handler.Init.Period=arr;                        //自动装载值
//    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
//    HAL_TIM_Base_Init(&TIM7_Handler);
//    
//    HAL_TIM_Base_Start_IT(&TIM7_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE									 
//}
////通用定时器9中断初始化
////arr：自动重装值。
////psc：时钟预分频数
////定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
////Ft=定时器工作频率,单位:Mhz
////这里使用的是定时器9!(定时器9挂在APB2上，时钟为HCLK)
//void TIM9_Init(u16 arr,u16 psc)
//{  
//    TIM9_Handler.Instance=TIM9;                          //通用定时器3
//    TIM9_Handler.Init.Prescaler=psc;                     //分频系数
//    TIM9_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
//    TIM9_Handler.Init.Period=arr;                        //自动装载值
//    TIM9_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
//    HAL_TIM_Base_Init(&TIM9_Handler);
//    
//    HAL_TIM_Base_Start_IT(&TIM9_Handler); //使能定时器9和定时器9更新中断：TIM_IT_UPDATE   
//}


////定时器底册驱动，开启时钟，设置中断优先级
////此函数会被HAL_TIM_Base_Init()函数调用
//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
//{
//    if(htim->Instance==TIM3)
//	{
//		__HAL_RCC_TIM3_CLK_ENABLE();            //使能TIM3时钟
//		HAL_NVIC_SetPriority(TIM3_IRQn,6,0);    //设置中断优先级，抢占优先级1，子优先级0
//		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启ITM3中断   
//	}
//	else if(htim->Instance==TIM9)
//	{
//		__HAL_RCC_TIM9_CLK_ENABLE();            		//使能TIM9时钟
//		HAL_NVIC_SetPriority(TIM1_BRK_TIM9_IRQn,6,0);  	//设置中断优先级，抢占优先级8
//		HAL_NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);         //开启ITM9中断   
//	} 
//	else if(htim->Instance==TIM7)
//	{
//		__HAL_RCC_TIM7_CLK_ENABLE();            //使能TIM7时钟
//		HAL_NVIC_SetPriority(TIM7_IRQn,6,0);    //设置中断优先级，抢占优先级1，子优先级0
//		HAL_NVIC_EnableIRQ(TIM7_IRQn);          //开启ITM7中断   
//	}
//}


////定时器3中断服务函数
//void TIM3_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&TIM3_Handler);
//}
////定时器7中断服务函数
//void TIM7_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&TIM7_Handler);
//}
////定时器9中断服务函数
//void TIM1_BRK_TIM9_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&TIM9_Handler);
//}

//extern QueueHandle_t Message_Queue;	//信息队列句柄
//extern void disp_str(u8* str);

////回调函数，定时器中断服务函数调用
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
//			memset(buffer,0,USART_REC_LEN);	//清除缓冲区
//			err=xQueueReceiveFromISR(Message_Queue,buffer,&xTaskWokenByReceive);//请求消息Message_Queue
//            if(err==pdTRUE)			//接收到消息
//            {
//				disp_str(buffer);	//在LCD上显示接收到的消息
//            }
//        }
//		myfree(SRAMIN,buffer);		//释放内存
//		
//		portYIELD_FROM_ISR(xTaskWokenByReceive);//如果需要的话进行一次任务切换
//	}   
//	else if(htim==(&TIM7_Handler)){
//		USART3_RX_STA|=1<<15;	//标记接收完成
//		__HAL_TIM_CLEAR_FLAG(&TIM7_Handler,TIM_EventSource_Update );       //清除TIM7更新中断标志  
//		TIM7->CR1&=~(1<<0);  
//	}   			//关闭定时器7 
////	else if(htim->Instance==TIM1){
//// 		if(RmtSta&0x80)//上次有数据被接收到了
////		{	
////			RmtSta&=~0X10;						//取消上升沿已经被捕获标记
////			if((RmtSta&0X0F)==0X00)RmtSta|=1<<6;//标记已经完成一次按键的键值信息采集
////			if((RmtSta&0X0F)<14)RmtSta++;
////			else
////			{
////				RmtSta&=~(1<<7);//清空引导标识
////				RmtSta&=0XF0;	//清空计数器	
////			}						 	   	
////		}	
//// 
//// }
//}
