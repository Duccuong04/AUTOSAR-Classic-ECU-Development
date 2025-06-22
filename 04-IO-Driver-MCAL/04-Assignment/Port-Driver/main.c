#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

#include "DIO.h"

void delay(uint16_t time)
{
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < time);        
}

void RCC_Config()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config()
{
    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio);
}

void TIM_Config()
{
    TIM_TimeBaseInitTypeDef tim;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 0xFFFF;
    tim.TIM_Prescaler = 8000 - 1;
    TIM_TimeBaseInit(TIM2, &tim);
    TIM_Cmd(TIM2, ENABLE);
}

int main()
{
    RCC_Config();
    GPIO_Config();
    TIM_Config();

    /* Call type following AUTOSAR Classic*/
	Dio_LevelType ledState;
	Dio_PortLevelType readPort;
	Dio_PortLevelType readChannelGrp;
	Std_VersionInfoType SWVersion;
	Dio_LevelType flipChannel;
	
	/*Dio Channel Group*/
	Dio_ChannelGroupType PinGroup;
	PinGroup.mask = 0x00F0;
	PinGroup.offset = 4;
	PinGroup.port = DIO_PORT_C;

    while (1)
    {
        /*Blink LED ID 45 (STM32 is PC13)*/
		for(int i = 0; i< 2; i++)
		{
		Dio_WriteChannel(45, STD_HIGH);
		delay(500);
		Dio_WriteChannel(45, STD_LOW);
		delay(500);
		}
		
		/*Blink Channel Group */
		for(int j = 0; j <3; j++)
		{
		Dio_WriteChannelGroup(&PinGroup, 0xF);
		delay(1000);
		Dio_WriteChannelGroup(&PinGroup, 0x0);
		delay(1000);
		}
    }
}