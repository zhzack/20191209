//#include "common.h"
//#include "stdlib.h"


//u8 *cmd_buf;


//u8 wifi_sta_tcp_c(void){
//	u8 key;
//	u8 timex=0;
//	u8 res=0;
//	u16 rlen=0;
//	u8 constate=0;	//连接状态
//	u16 t=999;		//加速第一次获取链接状态
//	cmd_buf=mymalloc(SRAMIN,32);							//申请32字节内存					   
//	atk_8266_send_cmd((u8 *)"AT+CWMODE=1",(u8 *)"OK",50);	//设置WIFI STA模式
//	atk_8266_send_cmd((u8 *)"AT+RST",(u8 *)"OK",20);		//DHCP服务器关闭(仅AP模式有效) 
//	delay_ms(1000);         
//	delay_ms(1000);
//	delay_ms(1000);                                         //延时3S等待重启成功
//	sprintf((char*)cmd_buf,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);
//	//设置无线参数:ssid,密码
//	
//	while(atk_8266_send_cmd(cmd_buf,(u8 *)"WIFI GOT IP",300));
//	//连接目标路由器,并且获得IP
//	
//	atk_8266_send_cmd((u8 *)"AT+CIPMUX=0",(u8 *)"OK",20);   //0：单连接，1：多连接
//	sprintf((char*)cmd_buf,"AT+CIPSTART=\"TCP\",\"%s\",%s",ip_buf,(u8*)portnum);    //配置目标TCP服务器
//	
//	while(atk_8266_send_cmd(cmd_buf,(u8 *)"OK",200)){
//		printf("fail to connect");
//	};
//	
//	atk_8266_send_cmd((u8 *)"AT+CIPMODE=1",(u8 *)"OK",200);      //传输模式为：透传
//	
//	
//	LCD_Clear(WHITE);
//	POINT_COLOR=RED;
//	Show_Str_Mid(0,30,(u8*)"ATK-ESP WIFI-STA 测试",16,240);
//	Show_Str(30,50,200,16,(u8*)"正在配置ATK-ESP模块,请稍等...",12,0);			
//	LCD_Fill(30,50,239,50+12,WHITE);			//清除之前的显示
//	Show_Str(30,50,200,16,(u8*)"WK_UP:退出测试  KEY0:发送数据",12,0);
//	LCD_Fill(30,80,239,80+12,WHITE);
//	atk_8266_get_wanip((u8*)ip_buf);//服务器模式,获取WAN IP
//	sprintf((char*)cmd_buf,"IP地址:%s 端口:%s",(u8*)ip_buf,(u8*)portnum);
//	Show_Str(30,65,200,12,cmd_buf,12,0);			//显示IP地址和端口	
//	Show_Str(30,80,200,12,(u8*)"状态:",12,0); 		//连接状态
//	Show_Str(120,80,200,12,(u8*)"模式:",12,0); 		//连接状态
//	Show_Str(30,100,200,12,(u8*)"发送数据:",12,0); 	//发送数据
//	Show_Str(30,115,200,12,(u8*)"接收数据:",12,0);	//接收数据
//	atk_8266_wificonf_show(30,180,(u8*)"请设置路由器无线参数为:",(u8*)wifista_ssid,(u8*)wifista_encryption,(u8*)wifista_password);
//	POINT_COLOR=BLUE;
//	Show_Str(120+30,80,200,12,(u8*)ATK_ESP8266_WORKMODE_TBL[1],12,0); 		//连接状态
//	USART3_RX_STA=0;
//	
//	
//	atk_8266_quit_trans();
//	atk_8266_send_cmd((u8*)"AT+CIPSEND",(u8*)"OK",20);         //开始透传           
//	sprintf((char*)cmd_buf,"{\"id\":\"0001\",\"to\":\"0002\",\"msg\":\"4481516\"}\r\n");//测试数据
//	Show_Str(30+54,100,200,12,cmd_buf,12,0);
//	u3_printf("%s",cmd_buf);
//	printf("%s",USART3_RX_BUF);
////	u3_printf("%s",cmd_buf);while(1)
////			{
////				key=KEY_Scan(0);
////				if(key==WKUP_PRES)			//WK_UP 退出测试		 
////				{ 
////					res=0;					
////					atk_8266_quit_trans();	//退出透传 //关闭透传模式
////					atk_8266_send_cmd((u8*)"AT+CIPMODE=0",(u8*)"OK",20);   
////					break;												 
////				}
////				else if(key==KEY0_PRES)	//KEY0 发送数据 
////				{
////				
////						atk_8266_quit_trans();
////						atk_8266_send_cmd((u8*)"AT+CIPSEND",(u8*)"OK",20);         //开始透传           
////						sprintf((char*)cmd_buf,"{\"id\":\"0001\",\"to\":\"0002\",\"msg\":\"4481516\"}\r\n");//测试数据
////						Show_Str(30+54,100,200,12,cmd_buf,12,0);
////						u3_printf("%s",cmd_buf);
////						timex=100;
////				}
////				
////				if(timex)timex--;
////				if(timex==1)LCD_Fill(30+54,100,239,112,WHITE);
////				t++;
////				delay_ms(10);
////				if(USART3_RX_STA&0X8000)		//接收到一次数据了
////				{ 
////					rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
////					USART3_RX_BUF[rlen]=0;		//添加结束符 
////					printf("%s",USART3_RX_BUF);	//发送到串口   
////					sprintf((char*)cmd_buf,"收到%d字节,内容如下",rlen);//接收到的字节数 
////					LCD_Fill(30+54,115,239,130,WHITE);
////					POINT_COLOR=BRED;
////					Show_Str(30+54,115,156,12,cmd_buf,12,0); 			//显示接收到的数据长度
////					POINT_COLOR=BLUE;
////					LCD_Fill(30,130,239,319,WHITE);
////					Show_Str(30,130,180,190,USART3_RX_BUF,12,0);//显示接收到的数据 

////					USART3_RX_STA=0;
////					if(constate!='+')t=1000;		//状态为还未连接,立即更新连接状态
////					else t=0;                   //状态为已经连接了,10秒后再检查
////				}  
////				if(t==1000)//连续10秒钟没有收到任何数据,检查连接是不是还存在.
////				{   
////					constate=atk_8266_consta_check();//得到连接状态
////					printf("%c",constate);
////					if(constate=='+')Show_Str(30+30,80,200,12,(u8*)"连接成功",12,0);  //连接状态
////					else Show_Str(30+30,80,200,12,(u8*)"连接失败",12,0); 	 
////					t=0;
////				}
////				if((t%20)==0)LED0=!LED0;
////				atk_8266_at_response(1);
////			};
//	myfree(SRAMIN,cmd_buf);		//释放内存
//	return res;
//}

