#include "keys.h"
#include "delay.h"

u8 lastKey, currentKey;

u16 rowPin[4] = { GPIO_Pin_2,GPIO_Pin_4,GPIO_Pin_6,GPIO_Pin_8 };
u16 colPin[4] = { GPIO_Pin_8,GPIO_Pin_10,GPIO_Pin_12,GPIO_Pin_14 };
u8 otherPin[4] = { 14,13,11,7 };//GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2};     
//按键初始化函数
void KEYS_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);//使能PORTC时钟

	GPIO_InitStructure.GPIO_Pin = ROWPINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推挽输出
	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIOC 0-3
	GPIO_ResetBits(GPIOG, ROWPINS);

	GPIO_InitStructure.GPIO_Pin = COLPINS;//PD5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOC 10-13
}
u8 ReScan(u16 colPin, u8 colIndex)
{
	u8 i;
	for (i = 0; i < 4; i++) {
		GPIO_ResetBits(GPIOG, rowPin[i]);
		GPIO_SetBits(GPIOG, otherPin[i]);
		delay_ms(10);//据说是消除抖动,但是去掉工作也正常
		if ((GPIO_ReadInputDataBit(GPIOD, colPin) == 0)) {
			GPIO_ResetBits(GPIOG, ROWPINS);
			return colIndex * 4 + i + 1;//返回的数据为1-16 对应4x4键盘的16个键
		}
	}
	GPIO_ResetBits(GPIOG, ROWPINS);
	return 0;
}

u8 KEYS_Scan(void)
{
	u8 i;
	for (i = 0; i < 4; i++)
	{
		if (GPIO_ReadInputDataBit(GPIOG, colPin[i]) == 0) {
			currentKey = ReScan(colPin[i], i);
			if (currentKey == 0)
			{
				lastKey = 0;
				return 0;
			}
			else
			{
				if (currentKey != lastKey)
				{
					lastKey = currentKey;
					return lastKey;
				}
				else
				{
					lastKey = currentKey;
					return 0;
				}
			}
		}
	}
	lastKey = 0;
	return 0;
}
