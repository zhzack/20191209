#include "sys.h"

#define ROWPINS GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6|GPIO_Pin_8  //����G
#define COLPINS GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_14 //����D

void KEYS_Init(void);//IO��ʼ��

u8 KEYS_Scan(void);   //����ɨ�躯��
u8 ReScan(u16 colPin,u8 colIndex);//����ɨ��
