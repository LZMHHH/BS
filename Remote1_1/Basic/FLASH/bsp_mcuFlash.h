/**
  ******************************************************************************
  * @file    bsp_mcuFlash.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#ifndef _BSP_MCUFLASH_H_
#define _BSP_MCUFLASH_H_

 
#include "includes.h"
typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned short int  uint16; /* 16 bits */
typedef unsigned char       byte;  /*  8 bits */
typedef unsigned short int  word; /* 16 bits */
typedef unsigned long int   uint32; /* 32 bits */
typedef unsigned long long  uint64; /* 64 bits */ 

typedef char                int8;   /*  8 bits */
typedef short int           int16;  /* 16 bits */
typedef long  int           int32;  /* 32 bits */
typedef long  long          int64;  /* 64 bits */ 

typedef volatile int8       vint8;  /*  8 bits */
typedef volatile int16      vint16; /* 16 bits */
typedef volatile int32      vint32; /* 32 bits */
typedef volatile int64      vint64; /* 64 bits */ 

typedef volatile uint8      vuint8;  /*  8 bits */
typedef volatile uint16     vuint16; /* 16 bits */
typedef volatile uint32     vuint32; /* 32 bits */
typedef volatile uint64     vuint64; /* 64 bits */ 

// STM32C8T6 64KB FLASH，20KB RAM，1个扇区1KB,程序起始0x8000000
// 虽然c8t6 手册是64k，但是实际一般 c8t6 和 cbt6 都是 128k的 ,
#define FLASH_START_ADDR    ((uint32_t)0x8000000)
#define FLASH_END_ADDR      ((uint32_t)(0x8000000 + FLASH_SECTOR_NUM * FLASH_SECTOR_SIZE))
#define FLASH_SECTOR_NUM    128  // 扇区数量
#define FLASH_SECTOR_SIZE   1024 // 扇区大小1KB

//-------------------------------------------------------------------------------------------------------------------
//  @brief      使用宏定义对flash进行数据读取
//  @param      SectorNum 		需要写入的扇区编号
//  @param      offset	 		地址偏移
//  @param      type		 	读取的数据类型
//  @return     				返回给定地址的数据
//  @since      v1.0
//  Sample usage:               flash_read(20,0,uint32);//读取20号扇区偏移0数据类型为uint32
//-------------------------------------------------------------------------------------------------------------------
#define   Flash_Read(SectorNum,offset,type)     (*(type *)((uint32)(FLASH_START_ADDR + ((SectorNum)*FLASH_SECTOR_SIZE) + (offset))))        

typedef enum
{ 
  FLASH_FAILURE = 0,
  FLASH_SUCCESS,
} flash_status_t;

 
extern u8 INSector;   //最后一个扇区

//===========================================================================

flash_status_t FlashErase(uint32 SectorNum, uint8_t count);

uint32_t FlashWrite(uint32_t addr, uint8_t *buffer, uint32_t length);

uint32_t FlashRead(uint32_t addr, uint8_t *buffer, uint32_t length);

u8       Flash_Write(uint32 SectorNum, const uint8 *buf, uint32 len, uint32 offset);

#endif /* _MCU_FLASH_H_ */
