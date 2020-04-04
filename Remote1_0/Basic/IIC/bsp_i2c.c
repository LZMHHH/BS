/**
  ******************************************************************************
  * @file    bsp_i2c_ee.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   i2c mpu6050Ӧ�ú���bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� ָ���� ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "bsp_i2c.h"



/* STM32 I2C ����ģʽ */
#define I2C_Speed              100000  //*

/* �����ַֻҪ��STM32��ҵ�I2C������ַ��һ������ */
#define I2Cx_OWN_ADDRESS7      0X0B   


static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;    


static uint8_t I2C_TIMEOUT_UserCallback(void);

/**
  * @brief  I2C1 I/O����
  * @param  ��
  * @retval ��
  */
static void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* ʹ���� I2C1 �йص�ʱ�� */
	SENSORS_I2C_APBxClock_FUN ( SENSORS_I2C_CLK, ENABLE );
	SENSORS_I2C_GPIO_APBxClock_FUN ( SENSORS_I2C_GPIO_CLK, ENABLE );
	
    
  /* PB6-I2C1_SCL��PB7-I2C1_SDA*/
  GPIO_InitStructure.GPIO_Pin = SENSORS_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(SENSORS_I2C_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = SENSORS_I2C_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
  GPIO_Init(SENSORS_I2C_SDA_PORT, &GPIO_InitStructure);	
	
	
}


/**
  * @brief  I2C ����ģʽ����
  * @param  ��
  * @retval ��
  */
static void I2C_Mode_Configu(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 

  /* I2C ���� */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	
	/* �ߵ�ƽ�����ȶ����͵�ƽ���ݱ仯 SCL ʱ���ߵ�ռ�ձ� */
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	
  I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7; 
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;
	
	/* I2C��Ѱַģʽ */
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	/* ͨ������ */
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
	/* I2C1 ��ʼ�� */
  I2C_Init(SENSORS_I2Cx, &I2C_InitStructure);
  
	/* ʹ�� I2C1 */
  I2C_Cmd(SENSORS_I2Cx, ENABLE);   
}


/**
  * @brief  I2C �����ʼ��
  * @param  ��
  * @retval ��
  */
void bsp_I2C_Init(void)
{

  I2C_GPIO_Config(); 
 
  I2C_Mode_Configu();

}




/**
  * @brief   дһ���ֽڵ�I2C�豸��
  * @param   
  *		@arg devAddr:�����豸iic��ַ
  *		@arg regAddr:Ҫд�������豸�е�ĳ���Ĵ�����ַ
  *		@arg byte:�ֽ� 
  * @retval  ��������1���쳣����0
  */
uint8_t I2C_WriteByte(u8 devAddr,u8 regAddr,u8 byte)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;


  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 

  /* Send slave address for write */
  I2C_Send7bitAddress(SENSORS_I2Cx, devAddr, I2C_Direction_Transmitter);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  }  
      
  /* Send the slave's internal address to write to */
  I2C_SendData(SENSORS_I2Cx, regAddr);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 

  /* Send the byte to be written */
  I2C_SendData(SENSORS_I2Cx, byte); 
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;
   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))	
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 
	
  /* Send STOP condition */
  I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
	
	return 1; //��������1
}

/**
  * @brief   дlength���ֽڵ�I2C�豸��
  * @param   
  *		@arg devAddr:�����豸iic��ַ
  *		@arg regAddr:Ҫд�������豸�е�ĳ���Ĵ�����ַ
  *		@arg pData:����ָ��
  * @retval  ��������1���쳣����0
  */
uint8_t I2C_WriteBytes(u8 devAddr,u8 regAddr,u8* pData, u16 length)
{
	u16 cnt;
	
  /* 1 Send STRAT condition */
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;


  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 

  /* 2 Send slave address for write */
  I2C_Send7bitAddress(SENSORS_I2Cx, devAddr, I2C_Direction_Transmitter);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  }  
      
  /* 3 Send the slave's internal address to write to */
  I2C_SendData(SENSORS_I2Cx, regAddr);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
  } 

  /* 4 Send the bytes to be written */
	for(cnt=0; cnt<(length-1); cnt++)
	{
		I2C_SendData(SENSORS_I2Cx, *pData);
		I2CTimeout = I2CT_FLAG_TIMEOUT; 
		/* Test on EV8 and clear it */
		while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))	
		{
			if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
		} 
		pData++;
	}
	

  /* 5 Send STOP condition */
  I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
	
	return 1; //��������1
}

/**
  * @brief   ��I2C�豸�����ȡ1���ֽ� 
  * @param   
  *		@arg devAddr:�����豸iic��ַ
  *		@arg regAddr:Ҫд�������豸�е�ĳ���Ĵ�����ַ
  *		@arg length:��Ҫ��ȡ�����ݳ���
  * @retval  �����ֽ���
  */
uint8_t I2C_ReadByte(u8 devAddr, u8 regAddr)
{  
	u8 byte;
	
  I2CTimeout = I2CT_LONG_TIMEOUT;
	
  while(I2C_GetFlagStatus(SENSORS_I2Cx, I2C_FLAG_BUSY)) // Added by Najoua 27/08/2008    
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
	 /* 1 Send STRAT condition */
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;	 
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* 2 Send slave address for write */
  I2C_Send7bitAddress(SENSORS_I2Cx, devAddr, I2C_Direction_Transmitter);

	I2CTimeout = I2CT_FLAG_TIMEOUT;	 
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* 3 Clear EV6 by setting again the PE bit */
  I2C_Cmd(SENSORS_I2Cx, ENABLE);

  /* 4 Send the slave's internal address to write to */
  I2C_SendData(SENSORS_I2Cx, regAddr);  

	I2CTimeout = I2CT_FLAG_TIMEOUT;	 
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* 5 Resend STRAT condition a second time */  
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
		
  /* 6 Send slave address for read */
  I2C_Send7bitAddress(SENSORS_I2Cx, devAddr, I2C_Direction_Receiver);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;	 
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
        
	/* 7 Read a byte from the slave */
	byte = I2C_ReceiveData(SENSORS_I2Cx);

	/* 8 Send STOP Condition */
  I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
	 
  /* 9 Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(SENSORS_I2Cx, ENABLE);
	
	return byte; //����������1
}

/**
  * @brief   ��I2C�豸�����ȡlength���ֽ� 
  * @param   
  *		@arg devAddr:�����豸iic��ַ
  *		@arg regAddr:Ҫд�������豸�е�ĳ���Ĵ�����ַ
  *		@arg pBuffer:�����ݶ�ȡ���õ�ַ
  *		@arg length:��Ҫ��ȡ�����ݳ���
  * @retval  ��������1���쳣����0
  */
uint8_t I2C_ReadBytes(u8 devAddr, u8 regAddr, u8* pBuffer, u16 length)
{  
  I2CTimeout = I2CT_LONG_TIMEOUT;
	
  while(I2C_GetFlagStatus(SENSORS_I2Cx, I2C_FLAG_BUSY)) // Added by Najoua 27/08/2008    
  {
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* Send slave address for write */
  I2C_Send7bitAddress(SENSORS_I2Cx, devAddr, I2C_Direction_Transmitter);

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) 
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(SENSORS_I2Cx, ENABLE);

  /* Send the slave's internal address to write to */
  I2C_SendData(SENSORS_I2Cx, regAddr);  

	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
	
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
		
  /* Send slave address for read */
  I2C_Send7bitAddress(SENSORS_I2Cx, devAddr, I2C_Direction_Receiver);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	 
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
    if((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback();
   }
  
  /* While there is data to be read */
  while(length)  
  {
    if(length == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(SENSORS_I2Cx, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(SENSORS_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      /* Read a byte from the slave */
      *pBuffer = I2C_ReceiveData(SENSORS_I2Cx);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      length--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(SENSORS_I2Cx, ENABLE);
	
	return 1; //����������1
}




/**
  * @brief  Wait for slave Standby state 
  * @param  ��
  * @retval ��
  */
void I2C_WaitStandbyState(u8 devAddr)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    /* Send START condition */
    I2C_GenerateSTART(SENSORS_I2Cx, ENABLE);
    /* Read I2C1 SR1 register */
    SR1_Tmp = I2C_ReadRegister(SENSORS_I2Cx, I2C_Register_SR1);
    /* Send slave address for write */
    I2C_Send7bitAddress(SENSORS_I2Cx, devAddr, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(SENSORS_I2Cx, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(SENSORS_I2Cx, I2C_FLAG_AF);
    /* STOP condition */    
    I2C_GenerateSTOP(SENSORS_I2Cx, ENABLE); 
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �еĶ��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitStart  Ŀ���ֽڵ���ʼλ
		length   λ����
		data    ��Ÿı�Ŀ���ֽ�λ��ֵ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
*******************************************************************************/ 
u8 I2C_writeBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
{

    u8 b;
    if (I2C_ReadBytes(dev, reg, &b,1) != 0) {
        u8 mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
//        return I2C_WriteByte(dev, reg, b);
    } else {
        return 0;
    }
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �е�1��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitNum  Ҫ�޸�Ŀ���ֽڵ�bitNumλ
		data  Ϊ0 ʱ��Ŀ��λ������0 ���򽫱���λ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
*******************************************************************************/ 
u8 I2C_writeBit(u8 dev, u8 reg, u8 data, u8 bitNum){
    u8 b;
    I2C_WriteBytes(dev, reg, &b,1);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return I2C_WriteByte(dev, reg, b);
}

/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */
static  uint8_t I2C_TIMEOUT_UserCallback(void)
{
  /* Block communication and all processes */
  MPU_ERROR("I2C Timeout error!"); 
  
  return 0;
}

/*********************************************END OF FILE**********************/

