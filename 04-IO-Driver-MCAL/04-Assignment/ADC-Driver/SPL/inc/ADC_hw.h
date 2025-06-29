/**********************************************************
 * @file    ADC_hw.h
 * @brief   ADC Hardware Driver Header File 
 * @details File này định nghĩa API liên quan đến phần cứng STM32
 * @version 1.0
 * @date    2025-06-27
 * @author  Nguyen Duc Cuong
 **********************************************************/

#ifndef ADC_HW_H
#define ADC_HW_H

#include "ADC.h"
#include "stm32f10x_adc.h"

/**
 * @brief       Function to initialize the ADC hardware 
 * @param       ConfigPtr: Pointer to configuration set in Variant PB (Variant PC requires a NULL_PTR).
 * @return      void
 */

static inline void Adc_Hw_Init_ADC1(const Adc_ConfigType *ConfigPtr)
{
    ADC_InitTypeDef ADC_InitStruct;
    
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;

    ADC_InitStruct.ADC_ContinuousConvMode = (ConfigPtr->ConversionMode == ADC_CONV_MODE_CONTINUOUS) ? ENABLE : DISABLE;

    ADC_InitStruct.ADC_ScanConvMode = DISABLE;

    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;;

    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;

    ADC_InitStruct.ADC_NbrOfChannel = 1;

    ADC_Init(ADC1, &ADC_InitStruct);
}

/**
 * @brief       Setup channels
 * @param       ConfigPtr: Pointer to configuration set in Variant PB (Variant PC requires a NULL_PTR).
 * @return      void
 */

static inline void Adc_Hw_SetupChannels(const Adc_ConfigType* ConfigPtr)
{
    for(uint8 i = 0; i < ConfigPtr->NumChannels; i++)
    {
        Adc_ChannelType  channel = ConfigPtr->Channel[i].Channel;
        uint32 samplingtime = ConfigPtr->Channel[i].SamplingTime;
        uint8 rank = ConfigPtr->Channel[i].Rank;

        if(ConfigPtr->AdcInstance == ADC_INSTANCE_1)
        {
            ADC_RegularChannelConfig(ADC1, channel, rank, samplingtime);
        }

        else if(ConfigPtr->AdcInstance == ADC_INSTANCE_2)
        {
            ADC_RegularChannelConfig(ADC2, channel, rank, samplingtime);
        }
    }
}


#endif /*ADC_HW_H*/