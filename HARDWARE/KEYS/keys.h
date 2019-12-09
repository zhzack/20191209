#include "sys.h"

#define ROWPINS GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6|GPIO_Pin_8  //行针G
#define COLPINS GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_14 //列针D

void KEYS_Init(void);//IO初始化

u8 KEYS_Scan(void);   //按键扫描函数
u8 ReScan(u16 colPin,u8 colIndex);//二次扫描
