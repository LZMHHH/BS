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
#include "bsp_mcuFlash.h"
#include "stm32f10x_flash.h"

u8 INSector  =  FLASH_SECTOR_NUM-1;   //最后一个扇区

// addr:地址  count:扇区数量
flash_status_t FlashErase(uint32 SectorNum, uint8_t count)

{
  uint8_t i;
	
	uint32   addr;
	
	addr =   FLASH_START_ADDR + SectorNum*FLASH_SECTOR_SIZE;

  // 解锁
  FLASH_Unlock();
  
  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  
  for(i = 0; i < count; ++i)
  {
    if(FLASH_ErasePage(addr + i * FLASH_SECTOR_SIZE) != FLASH_COMPLETE)
    {
      return FLASH_FAILURE;
    }
  }

  FLASH_Lock();

  return FLASH_SUCCESS;
}

 

uint32_t FlashWrite(uint32_t addr, uint8_t *buffer, uint32_t length)
{
  uint16_t i, data = 0;

  FLASH_Unlock();

  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

  for(i = 0; i < length; i += 2)
  {
    data = (*(buffer + i + 1) << 8) + (*(buffer + i));
    if(FLASH_ProgramHalfWord((uint32_t)(addr + i), data) != FLASH_COMPLETE)
    {
      return i;
    }
  }

  FLASH_Lock();

  return length;
}

 

uint32_t FlashRead(uint32_t addr, uint8_t *buffer, uint32_t length)

{
  memcpy(buffer, (void *)addr, length);
  
  return length;

}

//  len : 要为2的倍数
u8 Flash_Write(uint32 SectorNum, const uint8 *buf, uint32 len, uint32 offset)
{
	uint32   addr;
	uint16_t i, data = 0;

	addr = (uint32)(FLASH_START_ADDR + SectorNum*FLASH_SECTOR_SIZE + offset);
	
	FLASH_Unlock();

  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	
	for(i = 0; i < len; i += 2)
  {
    data = (*(buf + i + 1) << 8) + (*(buf + i));
    if(FLASH_ProgramHalfWord((uint32_t)(addr + i), data) != FLASH_COMPLETE)
    {
      return 0;
    }
  }
	
	FLASH_Lock();
	
	return 1;

}





