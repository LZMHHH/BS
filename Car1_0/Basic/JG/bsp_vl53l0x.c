/**
  ******************************************************************************
  * @file    bsp_vl53l0x.h
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   .
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
  *
  ******************************************************************************
  */
#include "bsp_vl53l0x.h"

//�ӿ�
#define Vl53l0xdelay_us DwtDelay_uS
#define Vl53l0xdelay_ms DwtDelay_mS



#define Vl53l0x_write 0
#define Vl53l0x_read  1

/*
*********************************************************************************************************
*	�� �� ��: VL53L0X_IIC_Start
*	����˵��: CPU����I2C���������ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void VL53L0X_IIC_Start(void)
{
	VL53L0X_SDA_OUT();  
	VL53L0X_IIC_SDA=1;  
	VL53L0X_IIC_SCL=1;  
	Vl53l0xdelay_us(3);	  
	VL53L0X_IIC_SDA=0;  
	Vl53l0xdelay_us(3);   
	VL53L0X_IIC_SCL=0;
}

/*
*********************************************************************************************************
*	�� �� ��: VL53L0X_IIC_Start
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void VL53L0X_IIC_Stop(void)
{
	VL53L0X_SDA_OUT();	
	VL53L0X_IIC_SCL=0;	
	VL53L0X_IIC_SDA=0;  	
	Vl53l0xdelay_us(3);		
	VL53L0X_IIC_SCL=1;	
	Vl53l0xdelay_us(3);	
	VL53L0X_IIC_SDA=1;	
	Vl53l0xdelay_us(3);
}

/*
*********************************************************************************************************
*	�� �� ��: VL53L0X_IIC_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    �Σ�_ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void VL53L0X_IIC_SendByte(uint8_t byte)
{
	uint8_t i;

	u8  BitCnt;	
	VL53L0X_SDA_OUT();	
	VL53L0X_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ	
	{		
		if(byte&0x80) 
			VL53L0X_IIC_SDA=1;//�жϷ���λ		
		else VL53L0X_IIC_SDA=0; 		
		byte<<=1;		
		Vl53l0xdelay_us(2); 		
		VL53L0X_IIC_SCL=1;		
		Vl53l0xdelay_us(2);		
		VL53L0X_IIC_SCL=0;		
		Vl53l0xdelay_us(2);	
	}
}

/*
*********************************************************************************************************
*	�� �� ��: VL53L0X_IIC_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    �Σ���
*	�� �� ֵ: ����������
*********************************************************************************************************
*/
uint8_t VL53L0X_IIC_ReadByte(void)
{
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	VL53L0X_SDA_IN();//��������Ϊ���뷽ʽ  
	Vl53l0xdelay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		VL53L0X_IIC_SCL=0;//��ʱ����Ϊ�ͣ�׼����������λ	
		Vl53l0xdelay_us(2);               	
		VL53L0X_IIC_SCL=1;//��ʱ����Ϊ��ʹ��������������Ч                	
		retc=retc<<1;	
		if(VL53L0X_READ_SDA) 
			retc |=1;//������λ,���յ�����λ����retc�� 	
		Vl53l0xdelay_us(1);  
	}  
	VL53L0X_IIC_SCL=0;      
	return(retc);
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    �Σ���
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
uint8_t VL53L0X_IIC_WaitAck(void)
{
	u8 t = 200;    
	VL53L0X_SDA_OUT();    
	VL53L0X_IIC_SDA=1;//8λ��������ͷ������ߣ�׼������Ӧ��λ     
	Vl53l0xdelay_us(1);    
	VL53L0X_IIC_SCL=0;    
	Vl53l0xdelay_us(1);     
	VL53L0X_SDA_IN();    
	Vl53l0xdelay_us(1);     
	while(VL53L0X_READ_SDA)//�ȴ�SHT30Ӧ��    
	{	
			t--;
			Vl53l0xdelay_us(1); 	
			if(t==0)	
			{	  
				VL53L0X_IIC_SCL=0;	  
				return 1;	
			}	
			Vl53l0xdelay_us(1);     
	}    
	Vl53l0xdelay_us(1);          
	VL53L0X_IIC_SCL=1;    
	Vl53l0xdelay_us(1);    
	VL53L0X_IIC_SCL=0;                 
	Vl53l0xdelay_us(1);        
	return 0;	
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void VL53L0X_IIC_Ack(void)
{
	VL53L0X_SDA_OUT();
	VL53L0X_IIC_SCL=0;
	Vl53l0xdelay_us(2);  
	VL53L0X_IIC_SDA=0;
	Vl53l0xdelay_us(2);
	VL53L0X_IIC_SCL=1;
	Vl53l0xdelay_us(2);
	VL53L0X_IIC_SCL=0;
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void VL53L0X_IIC_NAck(void)
{
	VL53L0X_SDA_OUT();  
	VL53L0X_IIC_SCL=0;  
	Vl53l0xdelay_us(2);   
	VL53L0X_IIC_SDA=1;  
	Vl53l0xdelay_us(2);        
	VL53L0X_IIC_SCL=1;  
	Vl53l0xdelay_us(2);                     
	VL53L0X_IIC_SCL=0;                       
	Vl53l0xdelay_us(1);  
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_SHT3x_Init
*	����˵��: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/

//��ʼ��	    
void bsp_VL53L0X_Init(void)
{ 	
 
 	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	VL53L0X_I2C_GPIO_APBxClock_FUN(VL53L0X_I2C_CLK_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SCL_InitStructure.GPIO_Pin = VL53L0X_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(VL53L0X_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //��ʼ��GPIOX
	
	VL53L0X_I2C_GPIO_APBxClock_FUN(VL53L0X_I2C_SDA_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SDA_InitStructure.GPIO_Pin = VL53L0X_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(VL53L0X_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //��ʼ��GPIOX
	
	VL53L0X_IIC_SCL = 1;		
	VL53L0X_IIC_SDA = 1;
	VL53L0X_IIC_Stop();			/* ����ֹͣ�ź� */
	
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_CheckDevice
*	����˵��: ���I2C�����豸��CPU�����豸��ַ��Ȼ���ȡ�豸Ӧ�����жϸ��豸�Ƿ����
*	��    �Σ�_Address���豸��I2C���ߵ�ַ
*	�� �� ֵ: ����ֵ 0 ��ʾ��ȷ�� ����1��ʾδ̽�⵽
*********************************************************************************************************
*/
uint8_t VL53L0X_IIC_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	bsp_VL53L0X_Init();		/* ����GPIO */

	
	VL53L0X_IIC_Start();		/* ���������ź� */

	/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
	VL53L0X_IIC_SendByte(_Address | Vl53l0x_write);
	ucAck = VL53L0X_IIC_WaitAck();	/* ����豸��ACKӦ�� */

	VL53L0X_IIC_Stop();			/* ����ֹͣ�ź� */

	return ucAck;
}


/*
*********************************************************************************************************
*	��Ϊiic
* ��Ϊ�豸
*********************************************************************************************************
*/




/*
*********************************************************************************************************
*	�� �� ��: ee_CheckOk
*	����˵��: �жϴ���EERPOM�Ƿ�����
*	��    �Σ���
*	�� �� ֵ: 1 ��ʾ������ 0 ��ʾ������
*********************************************************************************************************
*/
uint8_t vl53l0x_CheckOk(void)
{
	if (VL53L0X_IIC_CheckDevice(VL53L0X_DEV_ADDR) == 0)
	{
		return 1;
	}
	else
	{
		/* ʧ�ܺ��мǷ���I2C����ֹͣ�ź� */
		VL53L0X_IIC_Stop();		
		return 0;
	}
}

/*
*********************************************************************************************************
*	�� �� ��: ee_ReadBytes
*	����˵��: �Ӵ���EEPROMָ����ַ����ʼ��ȡ��������
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pReadBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t vl53l0x_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i;
	
	/* ���ô���EEPROM�漴��ȡָ�����У�������ȡ�����ֽ� */
	
	/* ��1��������I2C���������ź� */
	VL53L0X_IIC_Start();
	
	/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	VL53L0X_IIC_SendByte(VL53L0X_DEV_ADDR | Vl53l0x_write);	/* �˴���дָ�� */
	 
	/* ��3�����ȴ�ACK */
	if (VL53L0X_IIC_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}

	/* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
	VL53L0X_IIC_SendByte((uint8_t)_usAddress);
	
	/* ��5�����ȴ�ACK */
	if (VL53L0X_IIC_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}
	
	/* ��6������������I2C���ߡ�ǰ��Ĵ����Ŀ����EEPROM���͵�ַ�����濪ʼ��ȡ���� */
	VL53L0X_IIC_Start();
	
	/* ��7������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
	VL53L0X_IIC_SendByte(VL53L0X_DEV_ADDR | Vl53l0x_read);	/* �˴��Ƕ�ָ�� */
	
	/* ��8��������ACK */
	if (VL53L0X_IIC_WaitAck() != 0)
	{
		goto cmd_fail;	/* EEPROM������Ӧ�� */
	}	
	
	/* ��9����ѭ����ȡ���� */
	for (i = 0; i < _usSize; i++)
	{
		_pReadBuf[i] = VL53L0X_IIC_ReadByte();	/* ��1���ֽ� */
		
		/* ÿ����1���ֽں���Ҫ����Ack�� ���һ���ֽڲ���ҪAck����Nack */
		if (i != _usSize - 1)
		{
			VL53L0X_IIC_Ack();	/* �м��ֽڶ����CPU����ACK�ź�(����SDA = 0) */
		}
		else
		{
			VL53L0X_IIC_NAck();	/* ���1���ֽڶ����CPU����NACK�ź�(����SDA = 1) */
		}
	}
	/* ����I2C����ֹͣ�ź� */
	VL53L0X_IIC_Stop();
	return 1;	/* ִ�гɹ� */

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	VL53L0X_IIC_Stop();
	return 0;
}

/*
*********************************************************************************************************
*	�� �� ��: ee_WriteBytes
*	����˵��: ����EEPROMָ����ַд���������ݣ�����ҳд�������д��Ч��
*	��    �Σ�_usAddress : ��ʼ��ַ
*			 _usSize : ���ݳ��ȣ���λΪ�ֽ�
*			 _pWriteBuf : ��Ŷ��������ݵĻ�����ָ��
*	�� �� ֵ: 0 ��ʾʧ�ܣ�1��ʾ�ɹ�
*********************************************************************************************************
*/
uint8_t vl53l0x_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize)
{
	uint16_t i,m;
	uint16_t usAddr;
	
	/* 
		д����EEPROM�������������������ȡ�ܶ��ֽڣ�ÿ��д����ֻ����ͬһ��page��
		����24xx02��page size = 8
		�򵥵Ĵ�����Ϊ�����ֽ�д����ģʽ��ûд1���ֽڣ������͵�ַ
		Ϊ���������д��Ч��: ����������page wirte������
	*/

	usAddr = _usAddress;	
	for (i = 0; i < _usSize; i++)
	{
		/* �����͵�1���ֽڻ���ҳ���׵�ַʱ����Ҫ���·��������źź͵�ַ */
		if (i == 0)
		{
			/*���ڣ�������ֹͣ�źţ������ڲ�д������*/
			VL53L0X_IIC_Stop();
			
			/* ͨ���������Ӧ��ķ�ʽ���ж��ڲ�д�����Ƿ����, һ��С�� 10ms 			
				CLKƵ��Ϊ200KHzʱ����ѯ����Ϊ30������
			*/
			for (m = 0; m < 1000; m++)
			{				
				/* ��1��������I2C���������ź� */
				VL53L0X_IIC_Start();
				
				/* ��2������������ֽڣ���7bit�ǵ�ַ��bit0�Ƕ�д����λ��0��ʾд��1��ʾ�� */
				VL53L0X_IIC_SendByte(VL53L0X_DEV_ADDR | Vl53l0x_write);	/* �˴���дָ�� */
				
				/* ��3��������һ��ʱ�ӣ��ж������Ƿ���ȷӦ�� */
				if (VL53L0X_IIC_WaitAck() == 0)
				{
					break;
				}
			}
			if (m  == 1000)
			{
				goto cmd_fail;	/* EEPROM����д��ʱ */
			}
		
			/* ��4���������ֽڵ�ַ��24C02ֻ��256�ֽڣ����1���ֽھ͹��ˣ������24C04���ϣ���ô�˴���Ҫ���������ַ */
			VL53L0X_IIC_SendByte((uint8_t)usAddr);
			
			/* ��5�����ȴ�ACK */
			if (VL53L0X_IIC_WaitAck() != 0)
			{
				goto cmd_fail;	/* EEPROM������Ӧ�� */
			}
		}
	
		/* ��6������ʼд������ */
		VL53L0X_IIC_SendByte(_pWriteBuf[i]);
	
		/* ��7��������ACK */
		if (VL53L0X_IIC_WaitAck() != 0)
		{
			goto cmd_fail;	/* EEPROM������Ӧ�� */
		}

		//usAddr++;	/* ��ַ��1 */		
	}
	
	/* ����ִ�гɹ�������I2C����ֹͣ�ź� */
	VL53L0X_IIC_Stop();
	return 1;

cmd_fail: /* ����ִ��ʧ�ܺ��мǷ���ֹͣ�źţ�����Ӱ��I2C�����������豸 */
	/* ����I2C����ֹͣ�ź� */
	VL53L0X_IIC_Stop();
	return 0;
}

uint8_t vl53l0x_WriteByte(uint8_t _pWriteBuf, uint16_t _usAddress)
{
   return vl53l0x_WriteBytes(&_pWriteBuf, _usAddress, 1);
}

void VL53L0X_Init(void)							  //VL53L0X��ʼ��
{
  vl53l0x_CheckOk();
  vl53l0x_WriteByte(0x01, 0x00);
}

void DistanceRead(CLASS_Distance* diatance)
{
  uint8_t buff[12];
  vl53l0x_WriteByte(0x01, 0x00);                   //MCUͨ��I2C��VL53L0X����������ַ���Ĵ�����ַ�����ݡ���VL53L0X����
	vl53l0x_ReadBytes(buff, 0x14, 12);	               //ͬ��MCUͨ��I2C��ȡVL53L0X�Ĵ���������
  diatance->xmm = ((buff[10] & 0xFF) << 8) | (buff[11] & 0xFF);	 //�Ե�10��,11֡���ݴ���
 	diatance->xmm += diatance->offset;									
}

