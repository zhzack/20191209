//#include "common.h"
//#include "stdlib.h"


//u8 *cmd_buf;


//u8 wifi_sta_tcp_c(void){
//	u8 key;
//	u8 timex=0;
//	u8 res=0;
//	u16 rlen=0;
//	u8 constate=0;	//����״̬
//	u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
//	cmd_buf=mymalloc(SRAMIN,32);							//����32�ֽ��ڴ�					   
//	atk_8266_send_cmd((u8 *)"AT+CWMODE=1",(u8 *)"OK",50);	//����WIFI STAģʽ
//	atk_8266_send_cmd((u8 *)"AT+RST",(u8 *)"OK",20);		//DHCP�������ر�(��APģʽ��Ч) 
//	delay_ms(1000);         
//	delay_ms(1000);
//	delay_ms(1000);                                         //��ʱ3S�ȴ������ɹ�
//	sprintf((char*)cmd_buf,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);
//	//�������߲���:ssid,����
//	
//	while(atk_8266_send_cmd(cmd_buf,(u8 *)"WIFI GOT IP",300));
//	//����Ŀ��·����,���һ��IP
//	
//	atk_8266_send_cmd((u8 *)"AT+CIPMUX=0",(u8 *)"OK",20);   //0�������ӣ�1��������
//	sprintf((char*)cmd_buf,"AT+CIPSTART=\"TCP\",\"%s\",%s",ip_buf,(u8*)portnum);    //����Ŀ��TCP������
//	
//	while(atk_8266_send_cmd(cmd_buf,(u8 *)"OK",200)){
//		printf("fail to connect");
//	};
//	
//	atk_8266_send_cmd((u8 *)"AT+CIPMODE=1",(u8 *)"OK",200);      //����ģʽΪ��͸��
//	
//	
//	LCD_Clear(WHITE);
//	POINT_COLOR=RED;
//	Show_Str_Mid(0,30,(u8*)"ATK-ESP WIFI-STA ����",16,240);
//	Show_Str(30,50,200,16,(u8*)"��������ATK-ESPģ��,���Ե�...",12,0);			
//	LCD_Fill(30,50,239,50+12,WHITE);			//���֮ǰ����ʾ
//	Show_Str(30,50,200,16,(u8*)"WK_UP:�˳�����  KEY0:��������",12,0);
//	LCD_Fill(30,80,239,80+12,WHITE);
//	atk_8266_get_wanip((u8*)ip_buf);//������ģʽ,��ȡWAN IP
//	sprintf((char*)cmd_buf,"IP��ַ:%s �˿�:%s",(u8*)ip_buf,(u8*)portnum);
//	Show_Str(30,65,200,12,cmd_buf,12,0);			//��ʾIP��ַ�Ͷ˿�	
//	Show_Str(30,80,200,12,(u8*)"״̬:",12,0); 		//����״̬
//	Show_Str(120,80,200,12,(u8*)"ģʽ:",12,0); 		//����״̬
//	Show_Str(30,100,200,12,(u8*)"��������:",12,0); 	//��������
//	Show_Str(30,115,200,12,(u8*)"��������:",12,0);	//��������
//	atk_8266_wificonf_show(30,180,(u8*)"������·�������߲���Ϊ:",(u8*)wifista_ssid,(u8*)wifista_encryption,(u8*)wifista_password);
//	POINT_COLOR=BLUE;
//	Show_Str(120+30,80,200,12,(u8*)ATK_ESP8266_WORKMODE_TBL[1],12,0); 		//����״̬
//	USART3_RX_STA=0;
//	
//	
//	atk_8266_quit_trans();
//	atk_8266_send_cmd((u8*)"AT+CIPSEND",(u8*)"OK",20);         //��ʼ͸��           
//	sprintf((char*)cmd_buf,"{\"id\":\"0001\",\"to\":\"0002\",\"msg\":\"4481516\"}\r\n");//��������
//	Show_Str(30+54,100,200,12,cmd_buf,12,0);
//	u3_printf("%s",cmd_buf);
//	printf("%s",USART3_RX_BUF);
////	u3_printf("%s",cmd_buf);while(1)
////			{
////				key=KEY_Scan(0);
////				if(key==WKUP_PRES)			//WK_UP �˳�����		 
////				{ 
////					res=0;					
////					atk_8266_quit_trans();	//�˳�͸�� //�ر�͸��ģʽ
////					atk_8266_send_cmd((u8*)"AT+CIPMODE=0",(u8*)"OK",20);   
////					break;												 
////				}
////				else if(key==KEY0_PRES)	//KEY0 �������� 
////				{
////				
////						atk_8266_quit_trans();
////						atk_8266_send_cmd((u8*)"AT+CIPSEND",(u8*)"OK",20);         //��ʼ͸��           
////						sprintf((char*)cmd_buf,"{\"id\":\"0001\",\"to\":\"0002\",\"msg\":\"4481516\"}\r\n");//��������
////						Show_Str(30+54,100,200,12,cmd_buf,12,0);
////						u3_printf("%s",cmd_buf);
////						timex=100;
////				}
////				
////				if(timex)timex--;
////				if(timex==1)LCD_Fill(30+54,100,239,112,WHITE);
////				t++;
////				delay_ms(10);
////				if(USART3_RX_STA&0X8000)		//���յ�һ��������
////				{ 
////					rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
////					USART3_RX_BUF[rlen]=0;		//��ӽ����� 
////					printf("%s",USART3_RX_BUF);	//���͵�����   
////					sprintf((char*)cmd_buf,"�յ�%d�ֽ�,��������",rlen);//���յ����ֽ��� 
////					LCD_Fill(30+54,115,239,130,WHITE);
////					POINT_COLOR=BRED;
////					Show_Str(30+54,115,156,12,cmd_buf,12,0); 			//��ʾ���յ������ݳ���
////					POINT_COLOR=BLUE;
////					LCD_Fill(30,130,239,319,WHITE);
////					Show_Str(30,130,180,190,USART3_RX_BUF,12,0);//��ʾ���յ������� 

////					USART3_RX_STA=0;
////					if(constate!='+')t=1000;		//״̬Ϊ��δ����,������������״̬
////					else t=0;                   //״̬Ϊ�Ѿ�������,10����ټ��
////				}  
////				if(t==1000)//����10����û���յ��κ�����,��������ǲ��ǻ�����.
////				{   
////					constate=atk_8266_consta_check();//�õ�����״̬
////					printf("%c",constate);
////					if(constate=='+')Show_Str(30+30,80,200,12,(u8*)"���ӳɹ�",12,0);  //����״̬
////					else Show_Str(30+30,80,200,12,(u8*)"����ʧ��",12,0); 	 
////					t=0;
////				}
////				if((t%20)==0)LED0=!LED0;
////				atk_8266_at_response(1);
////			};
//	myfree(SRAMIN,cmd_buf);		//�ͷ��ڴ�
//	return res;
//}

