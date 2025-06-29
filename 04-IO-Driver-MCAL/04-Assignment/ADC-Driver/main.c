#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

#include "DIO.h"

#include "Port.h"
#include "Port_cfg.h"

void delay(uint16_t time)
{
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < time);        
}

void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

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

	/* Configuration Pin at Port_cfg.c*/
	Port_ConfigType portconfig = {
		.PinConfigs = PortCfg_Pins,
		.PinCount = 4
	};

	/*Init all Pins and Ports following configuration*/
	Port_Init(&portconfig);

	TIM_Config();
	
	/*Dio Channel Group*/
	Dio_ChannelGroupType PinGroup;
	PinGroup.mask = 0x00F0;
	PinGroup.offset = 4;
	PinGroup.port = DIO_PORT_C;

    while (1)
    {
        /*Blink LED ID 45 (STM32 is PC13)*/
		Dio_WriteChannel(GetChannelIdFromConfig(&PortCfg_Pins[3]), STD_HIGH);
		delay(1000);
		Dio_WriteChannel(GetChannelIdFromConfig(&PortCfg_Pins[3]), STD_LOW);
		delay(1000);
    }
}