/**********************************************************
 * @file    ADC.h
 * @brief   ADC Driver Source File (AUTOSAR Standard)
 * @details File này định nghĩa các API chuẩn AUTOSAR cho ADC Driver,
 *          dành cho STM32F103 sử dụng SPL. Driver cho phép cấu hình,
 *          thiết lập mode, kênh đọc ADC, đọc giá trị từ ngoại vi
 *
 * @version 1.0
 * @date    2025-06-27
 * @author  Nguyen Duc Cuong
 **********************************************************/

#include "../inc/ADC.h"

static const Adc_ConfigType* Adc_ConfigPtr = NULL_PTR;

/**
 * @brief       Initializes the ADC hardware units and driver.
 * @param       ConfigPtr: Pointer to configuration set in Variant PB (Variant PC requires a NULL_PTR).
 * @return      void
 */

void Adc_Init (const Adc_ConfigType* ConfigPtr)
{
    /* Check input ConfigPtr*/
    if(ConfigPtr == NULL_PTR)
    {
        return;
    }

    /* Configure GPIO for ADC pins based on channel */
    Adc_Hw_SetupGPIO(ConfigPtr);

    if(ConfigPtr->AdcInstance == ADC_INSTANCE_1)
    {
        ADC_Hw_Init_ADC1(ConfigPtr);
    }

    else if (ConfigPtr->AdcInstance == ADC_INSTANCE_2)
    {
        ADC_Hw_Init_ADC2(ConfigPtr);
    }

    Adc_Hw_SetupChannels(ConfigPtr);

    Adc_Hw_EnableAdc(ConfigPtr);
}