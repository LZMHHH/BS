/**
  ******************************************************************************
  * @file    bsp_sht3x.c
  * @author  fire
  * @version V1.1
  * @date    2020-xx-xx
  * @brief   I/O���ж�Ӧ��bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:˫��ʵ����-LZM
  * 
  * Wechat��qabc132321
	*
	*
  ******************************************************************************
  */


#include "bsp_sht3x.h" 



//�ӿ�
#define Sht3xdelay_us DwtDelay_uS
#define Sht3xdelay_ms DwtDelay_mS





 

#define Sht3x_write 0
#define Sht3x_read  1

/*��������ACK*/
void SHT3X_IIC_ACK(void)
{ 
		SHT3X_SDA_OUT();
		SHT3X_IIC_SCL=0;
		Sht3xdelay_us(2);  
		SHT3X_IIC_SDA=0;
		Sht3xdelay_us(2);
		SHT3X_IIC_SCL=1;
		Sht3xdelay_us(2);
		SHT3X_IIC_SCL=0;
		Sht3xdelay_us(1); 
}

 /*����������ACK*/
void SHT3X_IIC_NACK(void)
{  
	SHT3X_SDA_OUT();  
	SHT3X_IIC_SCL=0;  
	Sht3xdelay_us(2);   
	SHT3X_IIC_SDA=1;  
	Sht3xdelay_us(2);        
	SHT3X_IIC_SCL=1;  
	Sht3xdelay_us(2);                     
	SHT3X_IIC_SCL=0;                       
	Sht3xdelay_us(1);    
}

 
 
/*�����ȴ��ӻ���ACK
 *���أ�1 ����0������
 */
u8 SHT3X_IIC_wait_ACK(void)
{    
	u8 t = 200;    
	SHT3X_SDA_OUT();    
	SHT3X_IIC_SDA=1;//8λ��������ͷ������ߣ�׼������Ӧ��λ     
	Sht3xdelay_us(1);    
	SHT3X_IIC_SCL=0;    
	Sht3xdelay_us(1);     
	SHT3X_SDA_IN();    
	Sht3xdelay_us(1);     
	while(SHT3X_READ_SDA)//�ȴ�SHT30Ӧ��    
	{	
			t--;
			Sht3xdelay_us(1); 	
			if(t==0)	
			{	  
				SHT3X_IIC_SCL=0;	  
				return 1;	
			}	
			Sht3xdelay_us(1);     
	}    
	Sht3xdelay_us(1);          
	SHT3X_IIC_SCL=1;    
	Sht3xdelay_us(1);    
	SHT3X_IIC_SCL=0;                 
	Sht3xdelay_us(1);        
	return 0;	
}



/******************************************************************
 *����:����I2C����,������I2C��ʼ����.  
********************************************************************/
void SHT3X_IIC_Start(void)
{  
	SHT3X_SDA_OUT();  
	SHT3X_IIC_SDA=1;  
	SHT3X_IIC_SCL=1;  
	Sht3xdelay_us(4);	  
	SHT3X_IIC_SDA=0;  
	Sht3xdelay_us(4);   
	SHT3X_IIC_SCL=0;
}


/******************************************************************
*����:����I2C����,������I2C��������.  
********************************************************************/
void SHT3X_IIC_Stop(void)
{	
	SHT3X_SDA_OUT();	
	SHT3X_IIC_SCL=0;	
	SHT3X_IIC_SDA=0;  	
	Sht3xdelay_us(4);		
	SHT3X_IIC_SCL=1;	
	Sht3xdelay_us(4);	
	SHT3X_IIC_SDA=1;	
	Sht3xdelay_us(4);
}


/******************************************************************
*�ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������
********************************************************************/
void  SHT3X_IIC_SendByte(u8 byte)
{	
	u8  BitCnt;	
	SHT3X_SDA_OUT();	
	SHT3X_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ	
	{		
		if(byte&0x80) 
			SHT3X_IIC_SDA=1;//�жϷ���λ		
		else SHT3X_IIC_SDA=0; 		
		byte<<=1;		
		Sht3xdelay_us(2); 		
		SHT3X_IIC_SCL=1;		
		Sht3xdelay_us(2);		
		SHT3X_IIC_SCL=0;		
		Sht3xdelay_us(2);	
	}
}


/******************************************************************
* �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����: �������մ���������������  
********************************************************************/    
u8 SHT3X_IIC_RcvByte(void)
{  
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	SHT3X_SDA_IN();//��������Ϊ���뷽ʽ  
	Sht3xdelay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		SHT3X_IIC_SCL=0;//��ʱ����Ϊ�ͣ�׼����������λ	
		Sht3xdelay_us(2);               	
		SHT3X_IIC_SCL=1;//��ʱ����Ϊ��ʹ��������������Ч                	
		retc=retc<<1;	
		if(SHT3X_READ_SDA) 
			retc |=1;//������λ,���յ�����λ����retc�� 	
		Sht3xdelay_us(1);  
	}  
	SHT3X_IIC_SCL=0;      
	return(retc);
}


/************************* API ********************************************/

/******************************************************************* 
��ʪ�Ȼ�ȡ����               
����ԭ��: SHT30_read_result(u8 addr);
					addr:������ַ������Ϊ��0x44
����: �������մ������ɼ����ϳ���ʪ��
˵���������ڵ���ģʽ��Single Shot Mode��������ѡ���ģʽ���� ���������ڻ�ȡģʽ��Periodic Data Acquisition Mode��
********************************************************************/ 
void SHT3x_Getdata(u8 addr,CLASS_Huimiture* huimiture)
{	
	u16 tem,hum;	
	u16 buff[6];	
	float Temperature=0;	
	float Humidity=0;		
	SHT3X_IIC_Start();	
	SHT3X_IIC_SendByte(addr<<1 | Sht3x_write);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ	
	SHT3X_IIC_wait_ACK();	
	SHT3X_IIC_SendByte(0x2C);	  /* д��0x2c06 ��ʾ���ٲ���������ʱ������ */
	SHT3X_IIC_wait_ACK();	
	SHT3X_IIC_SendByte(0x06);	
	SHT3X_IIC_wait_ACK();	
	SHT3X_IIC_Stop();	
	Sht3xdelay_us(50);	
	SHT3X_IIC_Start();	
	SHT3X_IIC_SendByte(addr<<1 | Sht3x_read);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ	
	if(SHT3X_IIC_wait_ACK()==0)	
	{		
		buff[0]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[1]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[2]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[3]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[4]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_ACK();		
		buff[5]=SHT3X_IIC_RcvByte();		
		SHT3X_IIC_NACK();		
		SHT3X_IIC_Stop();	
	}		
	tem = ((buff[0]<<8) | buff[1]);//�¶�ƴ��	
	hum = ((buff[3]<<8) | buff[4]);//ʪ��ƴ��
	
	/*ת��ʵ���¶�*/	
	Temperature= (175.0*(float)tem/65535.0-45.0) ;// T = -45 + 175 * tem / (2^16-1)	
	Humidity= (100.0*(float)hum/65535.0);// RH = hum*100 / (2^16-1)		
	
	if((Temperature>=-20)&&(Temperature<=125))//���˴�������	
	{		
		huimiture->temperature=Temperature;		
	}
	if((Humidity>=0)&&(Humidity<=100))//���˴�������	
	{				
		huimiture->huimidity=Humidity;		
	}
}



//��ʼ��	    
void bsp_SHT3x_Init(void)
{ 	
 
 	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	SHT3X_I2C_GPIO_APBxClock_FUN(SHT3X_I2C_CLK_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SCL_InitStructure.GPIO_Pin = SHT3X_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(SHT3X_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //��ʼ��GPIOX
	
	SHT3X_I2C_GPIO_APBxClock_FUN(SHT3X_I2C_SDA_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SDA_InitStructure.GPIO_Pin = SHT3X_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(SHT3X_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //��ʼ��GPIOX
	
	SHT3X_IIC_SCL = 1;		
	SHT3X_IIC_SDA = 1;
	
}
