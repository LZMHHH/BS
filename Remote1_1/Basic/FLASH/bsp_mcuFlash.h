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
  * ʵ��ƽ̨:STʵ����-LZM
  * 
  * Wechat��qabc132321
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

// STM32C8T6 64KB FLASH��20KB RAM��1������1KB,������ʼ0x8000000
// ��Ȼc8t6 �ֲ���64k������ʵ��һ�� c8t6 �� cbt6 ���� 128k�� ,
#define FLASH_START_ADDR    ((uint32_t)0x8000000)
#define FLASH_END_ADDR      ((uint32_t)(0x8000000 + FLASH_SECTOR_NUM * FLASH_SECTOR_SIZE))
#define FLASH_SECTOR_NUM    128  // ��������
#define FLASH_SECTOR_SIZE   1024 // ������С1KB

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ʹ�ú궨���flash�������ݶ�ȡ
//  @param      SectorNum 		��Ҫд����������
//  @param      offset	 		��ַƫ��
//  @param      type		 	��ȡ����������
//  @return     				���ظ�����ַ������
//  @since      v1.0
//  Sample usage:               flash_read(20,0,uint32);//��ȡ20������ƫ��0��������Ϊuint32
//-------------------------------------------------------------------------------------------------------------------
#define   Flash_Read(SectorNum,offset,type)     (*(type *)((uint32)(FLASH_START_ADDR + ((SectorNum)*FLASH_SECTOR_SIZE) + (offset))))        

typedef enum
{ 
  FLASH_FAILURE = 0,
  FLASH_SUCCESS,
} flash_status_t;

 
extern u8 INSector;   //���һ������

//===========================================================================

flash_status_t FlashErase(uint32 SectorNum, uint8_t count);

uint32_t FlashWrite(uint32_t addr, uint8_t *buffer, uint32_t length);

uint32_t FlashRead(uint32_t addr, uint8_t *buffer, uint32_t length);

u8       Flash_Write(uint32 SectorNum, const uint8 *buf, uint32 len, uint32 offset);

#endif /* _MCU_FLASH_H_ */
