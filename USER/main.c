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

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		256  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define GET_INFO_PRIO		3
//�����ջ��С	
#define GET_INFO_SIZE 		256  
//������
TaskHandle_t GET_INFO_Handler;
//������
void get_info_task(void *pvParameters);

//�������ȼ�
#define NETWORK_TASK_PRIO		2
//�����ջ��С	
#define NETWORK_STK_SIZE 		256  
//������
TaskHandle_t NetworkTask_Handler;
//������
void network_task(void *pvParameters);

//�������ȼ�
#define KEYPROCESS_TASK_PRIO 3
//�����ջ��С	
#define KEYPROCESS_STK_SIZE  256 
//������
TaskHandle_t Keyprocess_Handler;
//������
void Keyprocess_task(void *pvParameters);


//������Ϣ���е�����
#define KEYMSG_Q_NUM    1  		//������Ϣ���е�����  
#define MESSAGE_Q_NUM   10    	//�������ݵ���Ϣ���е����� 
#define MESSAGE3_Q_NUM   4   	//�������ݵ���Ϣ���е����� 
QueueHandle_t Key_Queue;   		//����ֵ��Ϣ���о��
QueueHandle_t Message_Queue;	//��Ϣ���о��
QueueHandle_t Message3_Queue;	//��Ϣ���о��

//LCDˢ��ʱʹ�õ���ɫ
int lcd_discolor[14]={	WHITE, BLACK, BLUE,  BRED,      
						GRED,  GBLUE, RED,   MAGENTA,       	 
						GREEN, CYAN,  YELLOW,BROWN, 			
						BRRED, GRAY };

//������LCD����ʾ���յ��Ķ��е���Ϣ
//str: Ҫ��ʾ���ַ���(���յ�����Ϣ)
void disp_str(u8* str)
{ 
	LCD_Fill(5,230,110,245,WHITE);					//�������ʾ����
	LCD_ShowString(5,230,100,16,16,str);
	
}

//����������
void freertos_load_main_ui(void)
{
	
	POINT_COLOR = RED;
	LCD_ShowString(10,10,200,16,16,(u8 *)"Apollo STM32F4/F7");	
	LCD_ShowString(10,30,200,16,16,(u8 *)"FreeRTOS Examp 13-1");
	LCD_ShowString(10,50,200,16,16,(u8 *)"Message Queue");
	LCD_ShowString(10,70,220,16,16,(u8 *)"KEY_UP:LED1 KEY0:Refresh LCD");
	LCD_ShowString(10,90,200,16,16,(u8 *)"KEY1:SendMsg KEY2:BEEP");
	
	POINT_COLOR = BLACK;
	LCD_DrawLine(0,107,239,107);		//����
	LCD_DrawLine(119,107,119,319);		//����
	LCD_DrawRectangle(125,110,234,314);	//������
	POINT_COLOR = RED;
	LCD_ShowString(0,130,120,16,16,(u8 *)"DATA_Msg Size:");
	LCD_ShowString(0,170,120,16,16,(u8 *)"DATA_Msg rema:");
	LCD_ShowString(0,210,100,16,16,(u8 *)"DATA_Msg:");
	POINT_COLOR = BLUE;
}

u8 i=0;
int main(void)
{
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ������
	usart3_init(1500000);
	//usmart_dev.init(90);						//��ʼ��usmart
    LED_Init();                     //��ʼ��LED 
    KEY_Init();                     //��ʼ������
    PCF8574_Init();                 //��ʼ��PCF8574
    SDRAM_Init();                   //��ʼ��SDRAM
    LCD_Init();                     //��ʼ��LCD
	TIM9_Init(5000,18000-1);		//��ʼ����ʱ��9������500ms
	
    my_mem_init(SRAMIN);            //��ʼ���ڲ��ڴ��
    //freertos_load_main_ui();        //������UI
	W25QXX_Init();				    //��ʼ��W25Q256
	tp_dev.init();
    WM8978_Init();				    //��ʼ��WM8978
	WM8978_HPvol_Set(40,40);	    //������������
	WM8978_SPKvol_Set(40);		    //������������
    my_mem_init(SRAMIN);            //��ʼ���ڲ��ڴ��
    my_mem_init(SRAMEX);            //��ʼ���ⲿSDRAM�ڴ��
    my_mem_init(SRAMCCM);           //��ʼ���ڲ�CCM�ڴ��
    exfuns_init();		            //Ϊfatfs��ر��������ڴ�  
    f_mount(fs[0],"0:",1);          //����SD�� 
 	f_mount(fs[1],"1:",1);          //����SPI FLASH. 
	
	POINT_COLOR=RED;      
	
	while(font_init()) 			    //����ֿ�
	{	    
		LCD_ShowString(30,50,200,16,16,(u8 *)"Font Error!");
		delay_ms(20);				  
		LCD_Fill(30,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}  	 
	POINT_COLOR=RED;      
 	Show_Str(30,80,200,16,(u8 *)"Ұ����",16,0);
	Show_Str(30,40,200,16,(u8 *)"���ܼҾ�",16,0); 
	//atk_8266_wifista_test();
    //������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������                
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
	
	//������Ϣ����
    Key_Queue=xQueueCreate(KEYMSG_Q_NUM,sizeof(u8));        //������ϢKey_Queue
    Message_Queue=xQueueCreate(MESSAGE_Q_NUM,USART_REC_LEN); //������ϢMessage_Queue,��������Ǵ��ڽ��ջ���������
	Message3_Queue=xQueueCreate(MESSAGE3_Q_NUM,USART3_MAX_RECV_LEN);
    //����TASK1����
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
    //����TASK2����
    xTaskCreate((TaskFunction_t )Keyprocess_task,     
                (const char*    )"keyprocess_task",   
                (uint16_t       )KEYPROCESS_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )KEYPROCESS_TASK_PRIO,
                (TaskHandle_t*  )&Keyprocess_Handler); 
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}
static const char __get_token[] = 
{
"GET /oauth/2.0/token?\
grant_type=client_credentials\
&client_id=oOB2hX8gzU1jtP5m9GI4WDQK\
&client_secret=NW3AUu7MTnwb9RGjVh2OT0rhNeZnxbt0 \
HTTP/1.1\r\nHost: openapi.baidu.com\r\n\r\n"
};
//task1������
void get_info_task(void *pvParameters)
{   u8 *p;
	p=mymalloc(SRAMIN,32);
		atk_8266_quit_trans();
		atk_8266_send_cmd((u8 *)"ATE0",(u8 *)"OK",20);//�رջ���
		atk_8266_send_cmd((u8 *)"AT+CIPMODE=1",(u8 *)"OK",200);      //����ģʽΪ��͸��
		//atk_8266_send_cmd((u8*)"AT+CIPSTART=\"TCP\",\"47.97.25.40\",6789",(u8*)"OK",100);
		atk_8266_send_cmd((u8*)"AT+CIPSTART=\"TCP\",\"openapi.baidu.com\",80",(u8*)"OK",100);
		//sprintf((char*)p,"{\"id\":\"0001\",\"to\":\"0002\",\"msg\":\"4455\"}");//��������
		sprintf((char*)p,__get_token);//��������
		
	while(1)
	{ 	atk_8266_send_cmd((u8 *)"AT+CIPSEND",(u8 *)"OK",20);
		Show_Str(30+54,100,200,12,p,12,0);
		u3_printf("%s",p);
		//atk_8266_send_data(p,"token",100);
        vTaskDelay(100); 
		atk_8266_quit_trans();                          		//��ʱ10ms��Ҳ����10��ʱ�ӽ���	
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
//			memset(buffer,0,USART_REC_LEN);	//���������
//			err=xQueueReceive(Message_Queue,buffer,portMAX_DELAY);
//			if(err==pdPASS){}
//				  //disp_str(buffer);	//��LCD����ʾ���յ�����Ϣ
//				disp_str(buffer);	//��LCD����ʾ���յ�����Ϣ
//				printf("uart1%s",buffer);	
//			
//			
//			myfree(SRAMIN,buffer);		//�ͷ��ڴ�
//		}
		
		if(Message3_Queue!=NULL){
			buffer=mymalloc(SRAMIN,USART3_MAX_RECV_LEN);
			memset(buffer,0,USART3_MAX_RECV_LEN);	//���������
			err=xQueueReceive(Message3_Queue,buffer,portMAX_DELAY);
			if(err==pdPASS){ }
				  //disp_str(buffer);	//��LCD����ʾ���յ�����Ϣ
				disp_str(buffer);	//��LCD����ʾ���յ�����Ϣ
				printf("uart3��%s",buffer);
			
			//printf("err:%s",(u8*)err);
			myfree(SRAMIN,buffer);		//�ͷ��ڴ�
		}
		vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
	}
	
}

//Keyprocess_task����
void Keyprocess_task(void *pvParameters)
{   
	
	while(1)
	{
		LED1=~LED1;
		//printf("%d",i);
		vTaskDelay(1000);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
	}
}


