#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "sdram.h"
#include "key.h"
#include "time.h"
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
#include "usmart.h"
#include "time.h"
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		256  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define TASK1_TASK_PRIO		2
//�����ջ��С	
#define TASK1_STK_SIZE 		256  
//������
TaskHandle_t Task1Task_Handler;
//������
void task1_task(void *pvParameters);

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
#define MESSAGE_Q_NUM   4   	//�������ݵ���Ϣ���е����� 
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


int main(void)
{
    HAL_Init();                     //��ʼ��HAL��   
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);                //��ʼ����ʱ����
    uart_init(115200);              //��ʼ������
	usart3_init(115200);
	usmart_dev.init(90);						//��ʼ��usmart
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
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}  	 
	POINT_COLOR=RED;      
 	 
	
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
    xTaskCreate((TaskFunction_t )task1_task,             
                (const char*    )"task1_task",           
                (uint16_t       )TASK1_STK_SIZE,        
                (void*          )NULL,                  
                (UBaseType_t    )TASK1_TASK_PRIO,        
                (TaskHandle_t*  )&Task1Task_Handler);   
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

//task1������
void task1_task(void *pvParameters)
{
//	u8 key;
	u8 i=0;
//    BaseType_t err;
	atk_8266_test();
	while(1)
	{
//		key=KEY_Scan(0);            //ɨ�谴��
//        if((Key_Queue!=NULL)&&(key))   //��Ϣ����Key_Queue�����ɹ�,���Ұ���������
//        {
//            err=xQueueSend(Key_Queue,&key,10);
//            if(err==errQUEUE_FULL)   //���Ͱ���ֵ
//            {
//                printf("����Key_Queue���������ݷ���ʧ��!\r\n");
//            }
//        }
        i++;
        if(i%10==0) //��Message_Queue���е�����
        if(i==100)
        {
            i=0;
            LED0=!LED0;
        }
		
        vTaskDelay(10);                           //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
	}
	
	
}


//Keyprocess_task����
void Keyprocess_task(void *pvParameters)
{   u8 *buffer;
	buffer=mymalloc(SRAMIN,USART3_MAX_RECV_LEN);
	while(1)
	{
//		Show_Str(60,130,200,16,"KEY0:NEXT   KEY2:PREV",16,0); 
//		Show_Str(60,150,200,16,"KEY_UP:PAUSE/PLAY",16,0);
//		audio_play();
		if(Message_Queue!=NULL)
        {   
			memset(buffer,0,USART_REC_LEN);	//���������			
		if(xQueueReceive(Message_Queue,&buffer,portMAX_DELAY))//������Ϣ
            {
				printf("receive from ip :%s\r\n",buffer);    
            } 
			//			myfree(SRAMIN,buffer);		//�ͷ��ڴ�
        } 
		vTaskDelay(10);      //��ʱ10ms��Ҳ����10��ʱ�ӽ���	
	}
}
void key(u8 *key){
	 if((u8 *)1==key){
		  LED1=0;
	 
	 }

}

