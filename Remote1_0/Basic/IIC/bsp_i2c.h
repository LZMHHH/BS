#ifndef __BSP_I2C_H
#define	__BSP_I2C_H

#include "includes.h"


/**************************I2C参数定义，I2C1或I2C2********************************/
#define             SENSORS_I2Cx                                I2C1
#define             SENSORS_I2C_APBxClock_FUN                   RCC_APB1PeriphClockCmd
#define             SENSORS_I2C_CLK                             RCC_APB1Periph_I2C1
#define             SENSORS_I2C_GPIO_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define             SENSORS_I2C_GPIO_CLK                        RCC_APB2Periph_GPIOB     
#define             SENSORS_I2C_SCL_PORT                        GPIOB   
#define             SENSORS_I2C_SCL_PIN                         GPIO_Pin_6
#define             SENSORS_I2C_SDA_PORT                        GPIOB 
#define             SENSORS_I2C_SDA_PIN                         GPIO_Pin_7

/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/*信息输出*/
#define MPU_DEBUG_ON         1

#define MPU_INFO(fmt,arg...)           printf("<<-MPU-INFO->> "fmt"\n",##arg)
#define MPU_ERROR(fmt,arg...)          printf("<<-MPU-ERROR->> "fmt"\n",##arg)
#define MPU_DEBUG(fmt,arg...)          do{\
                                          if(MPU_DEBUG_ON)\
                                          printf("<<-MPU-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)


void bsp_I2C_Init(void);
uint8_t I2C_WriteByte(u8 devAddr,u8 regAddr,u8 byte);
uint8_t I2C_WriteBytes(u8 devAddr,u8 regAddr,u8* pData, u16 length);
uint8_t I2C_ReadByte(u8 devAddr, u8 regAddr);
uint8_t I2C_ReadBytes(u8 devAddr, u8 regAddr, u8* pBuffer, u16 length);
void I2C_WaitStandbyState(u8 devAddr);
u8 I2C_writeBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data);
u8 I2C_writeBit(u8 dev, u8 reg, u8 data, u8 bitNum);
																					
#endif /* __BSP_I2C_H */
