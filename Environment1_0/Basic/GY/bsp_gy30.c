/**
  ******************************************************************************
  * @file    bsp_gy30.c
  * @author  fire
  * @version V1.0
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
	*
  ******************************************************************************
  */


#include "bsp_gy30.h"

/* ��ֲʱע��������ע�⡱ */

u8    BH_Buf[8];                //�������ݻ�����

//�ӿ�
#define GY30delay_us DwtDelay_uS
#define GY30delay_ms DwtDelay_mS


#define GY30_write 0
#define GY30_read  1

/*��������ACK*/
void GY30_IIC_ACK(void)
{ 
		GY30_SDA_OUT();
		GY30_IIC_SCL=0;
		GY30delay_us(1);  
		GY30_IIC_SDA=0;
		GY30delay_us(1);
		GY30_IIC_SCL=1;
		GY30delay_us(1);
		GY30_IIC_SCL=0;
		GY30delay_us(1); 
}

 /*����������ACK*/
void GY30_IIC_NACK(void)
{  
		GY30_SDA_OUT();  
		GY30_IIC_SCL=0;  
		GY30delay_us(1);   
		GY30_IIC_SDA=1;  
		GY30delay_us(1);        
		GY30_IIC_SCL=1;  
		GY30delay_us(1);                     
		GY30_IIC_SCL=0;                       
		GY30delay_us(1);    
}

 
 
/*�����ȴ��ӻ���ACK
 *���أ�1 ����0������
 */
u8 GY30_IIC_wait_ACK(void)
{    
	u8 t = 200;    
	GY30_SDA_OUT();    
	GY30_IIC_SDA=1;//8λ��������ͷ������ߣ�׼������Ӧ��λ     
	GY30delay_us(1);    
	GY30_IIC_SCL=0;    
	GY30delay_us(1);     
	GY30_SDA_IN();    
	GY30delay_us(1);     
	while(GY30_READ_SDA)//�ȴ�GY30Ӧ��    
	{	
			t--;
			GY30delay_us(1); 	
			if(t==0)	
			{	  
				GY30_IIC_SCL=0;	  
				return 1;	
			}	
			GY30delay_us(1);     
	}    
	GY30delay_us(1);          
	GY30_IIC_SCL=1;    
	GY30delay_us(1);    
	GY30_IIC_SCL=0;                 
	GY30delay_us(1);        
	return 0;	
}



/******************************************************************
 *����:����I2C����,������I2C��ʼ����.  
********************************************************************/
int GY30_IIC_Start(void)
{  
	GY30_SDA_OUT();  
	GY30_IIC_SDA=1; 
	if(!GY30_READ_SDA)return 0;	
	GY30_IIC_SCL=1;  
	GY30delay_us(1);	  
	GY30_IIC_SDA=0; 
	if(GY30_READ_SDA)return 0;	
	GY30delay_us(1);   
	GY30_IIC_SCL=0;
	return 1;	
}


/******************************************************************
*����:����I2C����,������I2C��������.  
********************************************************************/
void GY30_IIC_Stop(void)
{	
	GY30_SDA_OUT();	
	GY30_IIC_SCL=0;	
	GY30_IIC_SDA=0;  	
	GY30delay_us(1);		
	GY30_IIC_SCL=1;	
	GY30delay_us(1);	
	GY30_IIC_SDA=1;	
	GY30delay_us(1);
}


/******************************************************************
*�ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������
********************************************************************/
void GY30_IIC_SendByte(u8 byte)
{	
	u8  BitCnt;	
	GY30_SDA_OUT();	
	GY30_IIC_SCL=0;	
	for(BitCnt=0;BitCnt<8;BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ	
	{		
		if(byte&0x80) 
			GY30_IIC_SDA=1;//�жϷ���λ		
		else GY30_IIC_SDA=0; 		
		byte<<=1;		
		GY30delay_us(1); 		
		GY30_IIC_SCL=1;		
		GY30delay_us(1);		
		GY30_IIC_SCL=0;		
		GY30delay_us(1);	
	}
	GY30_SDA_IN(); 	   //ע�⣺����7�䲻���٣���������������ǲ������ģ���00212��
	GY30_IIC_SDA=0;  
	GY30delay_us(1); 
	GY30_IIC_SCL=1;
	GY30delay_us(1); 
	GY30_IIC_SCL=0;  
	GY30delay_us(1); 
}


/******************************************************************
* �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����: �������մ���������������  
********************************************************************/    
u8 GY30_IIC_RcvByte(void)
{  
	u8 retc;  
	u8 BitCnt;  
	retc=0;   
	GY30_SDA_IN();//��������Ϊ���뷽ʽ  
	GY30delay_us(1);                      
	for(BitCnt=0;BitCnt<8;BitCnt++)  
	{  	
		GY30_IIC_SCL=0;//��ʱ����Ϊ�ͣ�׼����������λ	
		GY30delay_us(2);               	
		GY30_IIC_SCL=1;//��ʱ����Ϊ��ʹ��������������Ч                	
		retc=retc<<1;	
		if(GY30_READ_SDA) 
			retc |=1;//������λ,���յ�����λ����retc�� 	
		GY30delay_us(1);  
	}  
	GY30_IIC_SCL=0;      
	return(retc);
}

/********************** ��Ϊ iic����ΪGY30 ****************************/


void Single_Write_BH1750(u8 REG_Address)
{
    GY30_IIC_Start();                  //��ʼ�ź�
    GY30_IIC_SendByte(BH1750_ADDR);    //�����豸��ַ+д�ź�
    GY30_IIC_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
    GY30_IIC_Stop();                   //����ֹͣ�ź�
}
u8 Single_Read_BH1750(u8 REG_Address)
{  u8 REG_data;
    GY30_IIC_Start();                          //��ʼ�ź�
    GY30_IIC_SendByte(BH1750_ADDR);           //�����豸��ַ+д�ź�
    GY30_IIC_SendByte(REG_Address);           //���ʹ洢��Ԫ��ַ����0��ʼ	
    GY30_IIC_Start();                          //��ʼ�ź�
    GY30_IIC_SendByte(BH1750_ADDR+1);         //�����豸��ַ+���ź�
    REG_data=GY30_IIC_RcvByte();             //�����Ĵ�������
	  GY30_IIC_NACK();   
	  GY30_IIC_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
//��������BH1750�ڲ�����
void Multiple_Read_BH1750(void)
{   
	  u8 i;	
    GY30_IIC_Start();                          //��ʼ�ź�
    GY30_IIC_SendByte(BH1750_ADDR+1);         //�����豸��ַ+���ź�
	  for(i=0; i<3; i++)                      //������ȡ2����ַ���ݣ��洢��BUF
    {
        BH_Buf[i] = GY30_IIC_RcvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 3)
        {

           GY30_IIC_NACK();                //���һ��������Ҫ��NOACK
        }
        else
        {		
          GY30_IIC_ACK();                //��ӦACK
       }
   }
   GY30_IIC_Stop();                          //ֹͣ�ź�
}
//��ʼ��BH1750��������Ҫ��ο�pdf�����޸�****
void bsp_BH1750_Init(void)
{
	GPIO_InitTypeDef  GPIO_SCL_InitStructure,
	                  GPIO_SDA_InitStructure;
	
	GY30_I2C_GPIO_APBxClock_FUN(GY30_I2C_CLK_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SCL_InitStructure.GPIO_Pin = GY30_I2C_SCL_PIN;	 
 	GPIO_SCL_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SCL_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(GY30_I2C_SCL_PORT, &GPIO_SCL_InitStructure);	     //��ʼ��GPIOX
	
	GY30_I2C_GPIO_APBxClock_FUN(GY30_I2C_SDA_CLK, ENABLE);	 //ʹ��C�˿�ʱ��	
	GPIO_SDA_InitStructure.GPIO_Pin = GY30_I2C_SDA_PIN;	 
 	GPIO_SDA_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_SDA_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //�ٶ�50MHz
 	GPIO_Init(GY30_I2C_SDA_PORT, &GPIO_SDA_InitStructure);	     //��ʼ��GPIOX
	
	
	
	GY30_IIC_SCL = 1;		
	GY30_IIC_SDA = 1;
	
	GY30_IIC_Stop();                          //��Ҫ
	
  Single_Write_BH1750(0x01);  

	
}
//���¹�ǿ���� ��  ע�⣺��Ҫά��һ��ʱ����ܵõ����� 180ms����
void Updata_BH1750(CLASS_Light *light)
{

		Multiple_Read_BH1750();       //�����������ݣ��洢��BUF��

	  /* ���¿�ʼ :�������ݺ� ����׼����һ�ζ�ȡ����*/
		Single_Write_BH1750(0x01);   // power on
		Single_Write_BH1750(0x10);   // H- resolution mode
	
		/* ���ݴ��� */
    light->BH_Data=BH_Buf[0];
    light->BH_Data=(light->BH_Data<<8)+BH_Buf[1];//�ϳ����ݣ�����������
    light->BH_Voltage=(float)light->BH_Data/1.2;
}




