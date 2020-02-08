#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "sdram.h"
#include "key.h"
#include "timer.h"
#include "pcf8574.h"
#include "string.h"
#include "malloc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "remote.h"
#include "wm8978.h"	 
#include "audioplay.h"
#include "w25qxx.h"
#include "text.h"	
#include "exfuns.h"
#include "common.h"
//#include "usmart.h"
#include "time.h"
#include "recorder.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		256  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define GET_INFO_PRIO		3
//任务堆栈大小	
#define GET_INFO_SIZE 		256  
//任务句柄
TaskHandle_t GET_INFO_Handler;
//任务函数
void get_info_task(void *pvParameters);

//任务优先级
#define NETWORK_TASK_PRIO		2
//任务堆栈大小	
#define NETWORK_STK_SIZE 		256  
//任务句柄
TaskHandle_t NetworkTask_Handler;
//任务函数
void network_task(void *pvParameters);

//任务优先级
#define KEYPROCESS_TASK_PRIO 3
//任务堆栈大小	
#define KEYPROCESS_STK_SIZE  256 
//任务句柄
TaskHandle_t Keyprocess_Handler;
//任务函数
void Keyprocess_task(void *pvParameters);


//按键消息队列的数量
#define KEYMSG_Q_NUM    1  		//按键消息队列的数量  
#define MESSAGE_Q_NUM   10    	//发送数据的消息队列的数量 
#define MESSAGE3_Q_NUM   4   	//发送数据的消息队列的数量 
QueueHandle_t Key_Queue;   		//按键值消息队列句柄
QueueHandle_t Message_Queue;	//信息队列句柄
QueueHandle_t Message3_Queue;	//信息队列句柄

//LCD刷屏时使用的颜色
int lcd_discolor[14]={	WHITE, BLACK, BLUE,  BRED,      
						GRED,  GBLUE, RED,   MAGENTA,       	 
						GREEN, CYAN,  YELLOW,BROWN, 			
						BRRED, GRAY };

//用于在LCD上显示接收到的队列的消息
//str: 要显示的字符串(接收到的消息)
void disp_str(u8* str)
{ 
	LCD_Fill(5,230,110,245,WHITE);					//先清除显示区域
	LCD_ShowString(5,230,100,16,16,str);
	
}

//加载主界面
void freertos_load_main_ui(void)
{
	
	POINT_COLOR = RED;
	LCD_ShowString(10,10,200,16,16,(u8 *)"Apollo STM32F4/F7");	
	LCD_ShowString(10,30,200,16,16,(u8 *)"FreeRTOS Examp 13-1");
	LCD_ShowString(10,50,200,16,16,(u8 *)"Message Queue");
	LCD_ShowString(10,70,220,16,16,(u8 *)"KEY_UP:LED1 KEY0:Refresh LCD");
	LCD_ShowString(10,90,200,16,16,(u8 *)"KEY1:SendMsg KEY2:BEEP");
	
	POINT_COLOR = BLACK;
	LCD_DrawLine(0,107,239,107);		//画线
	LCD_DrawLine(119,107,119,319);		//画线
	LCD_DrawRectangle(125,110,234,314);	//画矩形
	POINT_COLOR = RED;
	LCD_ShowString(0,130,120,16,16,(u8 *)"DATA_Msg Size:");
	LCD_ShowString(0,170,120,16,16,(u8 *)"DATA_Msg rema:");
	LCD_ShowString(0,210,100,16,16,(u8 *)"DATA_Msg:");
	POINT_COLOR = BLUE;
}

u8 i=0;
int main(void)
{
    HAL_Init();                     //初始化HAL库   
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);                //初始化延时函数
    uart_init(115200);              //初始化串口
	usart3_init(1500000);
	//usmart_dev.init(90);						//初始化usmart
    LED_Init();                     //初始化LED 
    KEY_Init();                     //初始化按键
    PCF8574_Init();                 //初始化PCF8574
    SDRAM_Init();                   //初始化SDRAM
    LCD_Init();                     //初始化LCD
	TIM9_Init(5000,18000-1);		//初始化定时器9，周期500ms
	
    my_mem_init(SRAMIN);            //初始化内部内存池
    //freertos_load_main_ui();        //加载主UI
	W25QXX_Init();				    //初始化W25Q256
	tp_dev.init();
    WM8978_Init();				    //初始化WM8978
	WM8978_HPvol_Set(40,40);	    //耳机音量设置
	WM8978_SPKvol_Set(40);		    //喇叭音量设置
    my_mem_init(SRAMIN);            //初始化内部内存池
    my_mem_init(SRAMEX);            //初始化外部SDRAM内存池
    my_mem_init(SRAMCCM);           //初始化内部CCM内存池
    exfuns_init();		            //为fatfs相关变量申请内存  
    f_mount(fs[0],"0:",1);          //挂载SD卡 
 	f_mount(fs[1],"1:",1);          //挂载SPI FLASH. 
	
	POINT_COLOR=RED;      
	
	while(font_init()) 			    //检查字库
	{	    
		LCD_ShowString(30,50,200,16,16,(u8 *)"Font Error!");
		delay_ms(20);				  
		LCD_Fill(30,50,240,66,WHITE);//清除显示	     
		delay_ms(200);				  
	}  	 
	POINT_COLOR=RED;      
 	Show_Str(30,80,200,16,(u8 *)"野狼团",16,0);
	Show_Str(30,40,200,16,(u8 *)"智能家居",16,0); 
	//atk_8266_wifista_test();
    //创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄                
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
	
	//创建消息队列
    Key_Queue=xQueueCreate(KEYMSG_Q_NUM,sizeof(u8));        //创建消息Key_Queue
    Message_Queue=xQueueCreate(MESSAGE_Q_NUM,USART_REC_LEN); //创建消息Message_Queue,队列项长度是串口接收缓冲区长度
	Message3_Queue=xQueueCreate(MESSAGE3_Q_NUM,USART3_MAX_RECV_LEN);
    //创建TASK1任务
    xTaskCreate((TaskFunction_t )get_info_task,             
                (const char*    )"get_info_task",           
                (uint16_t       )GET_INFO_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )GET_INFO_PRIO,        
                (TaskHandle_t*  )&GET_INFO_Handler); 
				
	xTaskCreate((TaskFunction_t )network_task,             
                (const char*    )"network_task",           
                (uint16_t       )NETWORK_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )NETWORK_TASK_PRIO,        
                (TaskHandle_t*  )&NetworkTask_Handler);				
    //创建TASK2任务
    xTaskCreate((TaskFunction_t )Keyprocess_task,     
                (const char*    )"keyprocess_task",   
                (uint16_t       )KEYPROCESS_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )KEYPROCESS_TASK_PRIO,
                (TaskHandle_t*  )&Keyprocess_Handler); 
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}
static const char __get_token[] = 
{
"GET /oauth/2.0/token?\
grant_type=client_credentials\
&client_id=oOB2hX8gzU1jtP5m9GI4WDQK\
&client_secret=NW3AUu7MTnwb9RGjVh2OT0rhNeZnxbt0 \
HTTP/1.1\r\nHost: openapi.baidu.com\r\n\r\n"
};
//task1任务函数
void get_info_task(void *pvParameters)
{   u8 *p;
	p=mymalloc(SRAMIN,32);
		atk_8266_quit_trans();
		atk_8266_send_cmd((u8 *)"ATE0",(u8 *)"OK",20);//关闭回显
		atk_8266_send_cmd((u8 *)"AT+CIPMODE=1",(u8 *)"OK",200);      //传输模式为：透传
		//atk_8266_send_cmd((u8*)"AT+CIPSTART=\"TCP\",\"47.97.25.40\",6789",(u8*)"OK",100);
		atk_8266_send_cmd((u8*)"AT+CIPSTART=\"TCP\",\"openapi.baidu.com\",80",(u8*)"OK",100);
		//sprintf((char*)p,"{\"id\":\"0001\",\"to\":\"0002\",\"msg\":\"4455\"}");//测试数据
		sprintf((char*)p,__get_token);//测试数据
		
	while(1)
	{ 	atk_8266_send_cmd((u8 *)"AT+CIPSEND",(u8 *)"OK",20);
		Show_Str(30+54,100,200,12,p,12,0);
		u3_printf("%s",p);
		//atk_8266_send_data(p,"token",100);
        vTaskDelay(100); 
		atk_8266_quit_trans();                          		//延时10ms，也就是10个时钟节拍	
		vTaskDelay(100); 
	}
	
	
}

void network_task(void *pvParameters){

	u8* buffer;
	BaseType_t err;
	 while(1)
	{   
//		if(Message_Queue!=NULL){
//			buffer=mymalloc(SRAMIN,USART_REC_LEN);
//			memset(buffer,0,USART_REC_LEN);	//清除缓冲区
//			err=xQueueReceive(Message_Queue,buffer,portMAX_DELAY);
//			if(err==pdPASS){}
//				  //disp_str(buffer);	//在LCD上显示接收到的消息
//				disp_str(buffer);	//在LCD上显示接收到的消息
//				printf("uart1%s",buffer);	
//			
//			
//			myfree(SRAMIN,buffer);		//释放内存
//		}
		
		if(Message3_Queue!=NULL){
			buffer=mymalloc(SRAMIN,USART3_MAX_RECV_LEN);
			memset(buffer,0,USART3_MAX_RECV_LEN);	//清除缓冲区
			err=xQueueReceive(Message3_Queue,buffer,portMAX_DELAY);
			if(err==pdPASS){ }
				  //disp_str(buffer);	//在LCD上显示接收到的消息
				disp_str(buffer);	//在LCD上显示接收到的消息
				printf("uart3：%s",buffer);
			
			//printf("err:%s",(u8*)err);
			myfree(SRAMIN,buffer);		//释放内存
		}
		vTaskDelay(10);      //延时10ms，也就是10个时钟节拍	
	}
	
}

//Keyprocess_task函数
void Keyprocess_task(void *pvParameters)
{   
	
	while(1)
	{
		LED1=~LED1;
		//printf("%d",i);
		vTaskDelay(1000);      //延时10ms，也就是10个时钟节拍	
	}
}


