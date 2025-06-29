/********************************************************************************************* 
 * @file         DIO.h
 * @brief        Khai báo, định nghĩa các biến cho các module I/O Drivers trong AUTOSAR Classic 
 * @details      File này cung cấp việc định nghĩa bao gồm:
 *                   các kiểu dữ liệu
 *                   tên trạng thái trả về 
 *                   số hiệu version dùng
 * @version      1.0
 * @date         2025-06-01
 * @author       Nguyen Duc Cuong
 *********************************************************************************************/

#ifndef DIO_H
#define DIO_H

/* ===========================================================================================
 * Includes
 * =========================================================================================== */
#include "Std_Types.h"
#include "stm32f10x_gpio.h"
#include <stddef.h>   // Cung cấp định nghĩa NULL


/* ===========================================================================================
 * Defines
 * =========================================================================================== */

/********************************************************************************************* 
 * @brief        Macro DIO Port
 * @details      Định nghĩa macro cho các Port A, B, C, D 
 *********************************************************************************************/

#define DIO_PORT_A   0u
#define DIO_PORT_B   1u
#define DIO_PORT_C   2u
#define DIO_PORT_D   3u

/********************************************************************************************* 
 * @brief        Xác định port và pin của chân GPIO dựa trên ChannelID 
 *********************************************************************************************/
// Dựa vào PortId
#define DIO_GET_PORT_FROM_PORT(PortId)                                                                 \
        ((PortId == 0) ? GPIOA : ((PortId == 1) ? GPIOB : ((PortId == 2) ? GPIOC :                   \
        ((PortId == 3) ? GPIOD : NULL))))

// Dựa vào ChannelGroupPtr
#define DIO_GET_PORT_FROM_GROUP(ChannelGroupPtr)                                                     \
        ((ChannelGroupPtr->port == 0) ? GPIOA : ((ChannelGroupPtr->port == 1) ? GPIOB :              \
        ((ChannelGroupPtr->port == 2) ? GPIOC : ((ChannelGroupPtr->port == 3) ? GPIOD : NULL))))

// Dựa vào ChannelId
#define DIO_GET_PORT_FROM_CHANNEL(ChannelId)                                                         \
        ((ChannelId < 16) ? GPIOA : ((ChannelId < 32) ? GPIOB : ((ChannelId < 64) ? GPIOC :          \
        ((ChannelId < 96) ? GPIOD : NULL))))

/*Xác định Pin dựa vào ChannelId*/
#define DIO_GET_PIN(ChannelId)       (1 << ((ChannelId) % 16))                                                                    


/**
 * @brief       Macro xác định channel ID cho từng chân GPIO
 * @param       GPIOx: GPIO port x (GPIOA, GPIOB, GPIOC, GPIOD)
 * @param       Pin: GPIO pin (0 đến 15)
 */
#define DIO_CHANNEL(GPIO_x, Pin)     (((GPIO_x) << 4u) + (Pin))

/* GPIO A Pins 0 to 15 */
#define DIO_CHANNEL_A0      DIO_CHANNEL(GPIOA, 0)
#define DIO_CHANNEL_A1      DIO_CHANNEL(GPIOA, 1)
#define DIO_CHANNEL_A2      DIO_CHANNEL(GPIOA, 2)
#define DIO_CHANNEL_A3      DIO_CHANNEL(GPIOA, 3)
#define DIO_CHANNEL_A4      DIO_CHANNEL(GPIOA, 4)
#define DIO_CHANNEL_A5      DIO_CHANNEL(GPIOA, 5)
#define DIO_CHANNEL_A6      DIO_CHANNEL(GPIOA, 6)
#define DIO_CHANNEL_A7      DIO_CHANNEL(GPIOA, 7)
#define DIO_CHANNEL_A8      DIO_CHANNEL(GPIOA, 8)
#define DIO_CHANNEL_A9      DIO_CHANNEL(GPIOA, 9)
#define DIO_CHANNEL_A10     DIO_CHANNEL(GPIOA, 10)
#define DIO_CHANNEL_A11     DIO_CHANNEL(GPIOA, 11)
#define DIO_CHANNEL_A12     DIO_CHANNEL(GPIOA, 12)
#define DIO_CHANNEL_A13     DIO_CHANNEL(GPIOA, 13)
#define DIO_CHANNEL_A14     DIO_CHANNEL(GPIOA, 14)
#define DIO_CHANNEL_A15     DIO_CHANNEL(GPIOA, 15)

/* GPIO B Pins 16 to 31 */
#define DIO_CHANNEL_B0      DIO_CHANNEL(GPIOB, 0)
#define DIO_CHANNEL_B1      DIO_CHANNEL(GPIOB, 1)
#define DIO_CHANNEL_B2      DIO_CHANNEL(GPIOB, 2)
#define DIO_CHANNEL_B3      DIO_CHANNEL(GPIOB, 3)
#define DIO_CHANNEL_B4      DIO_CHANNEL(GPIOB, 4)
#define DIO_CHANNEL_B5      DIO_CHANNEL(GPIOB, 5)
#define DIO_CHANNEL_B6      DIO_CHANNEL(GPIOB, 6)
#define DIO_CHANNEL_B7      DIO_CHANNEL(GPIOB, 7)
#define DIO_CHANNEL_B8      DIO_CHANNEL(GPIOB, 8)
#define DIO_CHANNEL_B9      DIO_CHANNEL(GPIOB, 9)
#define DIO_CHANNEL_B10     DIO_CHANNEL(GPIOB, 10)
#define DIO_CHANNEL_B11     DIO_CHANNEL(GPIOB, 11)
#define DIO_CHANNEL_B12     DIO_CHANNEL(GPIOB, 12)
#define DIO_CHANNEL_B13     DIO_CHANNEL(GPIOB, 13)
#define DIO_CHANNEL_B14     DIO_CHANNEL(GPIOB, 14)
#define DIO_CHANNEL_B15     DIO_CHANNEL(GPIOB, 15)

/* GPIO C Pins 32 to 47 */
#define DIO_CHANNEL_C0      DIO_CHANNEL(GPIOC, 0)
#define DIO_CHANNEL_C1      DIO_CHANNEL(GPIOC, 1)
#define DIO_CHANNEL_C2      DIO_CHANNEL(GPIOC, 2)
#define DIO_CHANNEL_C3      DIO_CHANNEL(GPIOC, 3)
#define DIO_CHANNEL_C4      DIO_CHANNEL(GPIOC, 4)
#define DIO_CHANNEL_C5      DIO_CHANNEL(GPIOC, 5)
#define DIO_CHANNEL_C6      DIO_CHANNEL(GPIOC, 6)
#define DIO_CHANNEL_C7      DIO_CHANNEL(GPIOC, 7)
#define DIO_CHANNEL_C8      DIO_CHANNEL(GPIOC, 8)
#define DIO_CHANNEL_C9      DIO_CHANNEL(GPIOC, 9)
#define DIO_CHANNEL_C10     DIO_CHANNEL(GPIOC, 10)
#define DIO_CHANNEL_C11     DIO_CHANNEL(GPIOC, 11)
#define DIO_CHANNEL_C12     DIO_CHANNEL(GPIOC, 12)
#define DIO_CHANNEL_C13     DIO_CHANNEL(GPIOC, 13)
#define DIO_CHANNEL_C14     DIO_CHANNEL(GPIOC, 14)
#define DIO_CHANNEL_C15     DIO_CHANNEL(GPIOC, 15)



/* ===========================================================================================
 * Type definitions DIO 
 * =========================================================================================== */

/********************************************************************************************* 
 * @typedef      Dio_ChannelType
 * @brief        Số hiệu ID của các chân DIO
 * @details      Định nghĩa kiểu dữ liệu mới có tên là Dio_ChannelType, định danh cho số ID của 
 *               các Pin, khi truyền vào hàm thì tham số nhìn trực quan và có quy tắc
 *               sử dụng kiểu uint8 (tương ứng với 256 chân)
 *********************************************************************************************/

typedef uint8       Dio_ChannelType;

/********************************************************************************************* 
 * @typedef      Dio_PortType
 * @brief        Số hiệu ID của các Port DIO 
 * @details      Định nghĩa kiểu dữ liệu mới có tên là Dio_ChannelPort, định danh cho số ID của 
 *               các Port, khi truyền vào hàm thì tham số nhìn trực quan và có quy tắc
 *               sử dụng kiểu uint8 (đủ cho số Port trong 1 vi điều khiển bất kì)
 *********************************************************************************************/

typedef uint8       Dio_PortType;

/********************************************************************************************* 
 * @struct       Dio_ChannelGroupType
 * @brief        Số hiệu của ChannelGroup 
 * @details      Định nghĩa 1 struct có tên là Dio_ChannelGroupType, chứa các tham số sau:
 *               mask
 *               offset
 *               port
 *********************************************************************************************/

 typedef struct 
 {
    uint16 mask;                             /*<< Mặt nạ bit xác định vị trí của group*/
    uint8 offset;                            /*<< Giá trị offset để đến vị trí group tính từ LSB*/
    Dio_PortType port;                       /*<< Port chứa group*/

 } Dio_ChannelGroupType;

/********************************************************************************************* 
 * @struct       Dio_LevelType
 * @brief        Kiểu dữ liệu thể hiện mức logic của 1 PIN 
 * @details      LOW & HIGH
 *********************************************************************************************/

typedef uint8        Dio_LevelType;

/********************************************************************************************* 
 * @struct       Dio_PortLevelType
 * @brief        Kiểu dữ liệu thể hiện mức logic của 1 DIO Port
 * @details      Thể hiện mức logic của các Pin trong Port
 *********************************************************************************************/

typedef uint16       Dio_PortLevelType;

/* ===========================================================================================
 * Fuction Decalarations
 * =========================================================================================== */

/********************************************************************************************* 
 * @brief       Đọc trạng thái của 1 Pin       
 * @param       Channel ID
 * @return      Dio_LevelType: STD_HIGH/ STD_LOW
 *********************************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelID);

 /********************************************************************************************* 
 * @brief       Ghi trạng thái cho 1 Pin       
 * @param       Channel ID, Level
 * @return      void
 *********************************************************************************************/

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/********************************************************************************************* 
 * @brief       Đọc trạng thái của 1 Port     
 * @param       PortID
 * @return      PortLevel
 *********************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortID);

/********************************************************************************************* 
 * @brief       Ghi trạng thái logic cho toàn bộ cổng DIO của 1 Port     
 * @param       PortID (DIO_PORT_A, DIO_PORTB,...), Level cho 16 pin của Port đối với STM32F1
 * @return      void
 *********************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/********************************************************************************************* 
 * @brief       Đọc trạng thái logic của một GroupChannel    
 * @param       Con trỏ trỏ đến 1  ChannelGroup
 * @return      Dio_PortLevelType
 *********************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupPtr);

/********************************************************************************************* 
 * @brief       Ghi trạng thái logic cho một GroupChannel    
 * @param       Con trỏ trỏ đến 1  ChannelGroup, PortLevel
 * @return      void
 *********************************************************************************************/

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

/********************************************************************************************* 
 * @brief       Lấy dữ liệu về version của software đang dùng    
 * @param       Con trỏ VersionInfo
 * @return      void
 *********************************************************************************************/

void Dio_GetVersionInfo (Std_VersionInfoType* VersionInfo);

/********************************************************************************************* 
 * @brief       Đảo ngược trạng thái của 1 channel   
 * @param       ChannelId
 * @return      STD_HIGH/ STD_LOW
 *********************************************************************************************/
Dio_LevelType Dio_FlipChannel (Dio_ChannelType ChannelId);

#endif /*DIO.h*/