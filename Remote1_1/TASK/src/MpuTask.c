/**
  ******************************************************************************
  * @file    MpuTask.c
  * @author  lss
  * @version V1.0
  * @date    2019-xx-xx
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
#include "MpuTask.h"
#include "filter.h"

//MPU
int   MPU_Temperature;            //��ʾ�¶�
u8    Way_Angle=2;                //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲�
//float Angle_BalanceX;           //ƽ�����X 
float Angle_BalanceY;             //ƽ�����Y
//float Angle_BalanceZ;           //ƽ�����Z 
//float Gyro_BalanceX;            //������X
float Gyro_BalanceY;              //������Y
float Gyro_BalanceZ;              //������Z
//float Acceleration_X;           //X����ٶȼ�
//float Acceleration_Y;           //Y����ٶȼ�
float Acceleration_Z;             //Z����ٶȼ�
float Mechanical_deviation = 0;   //��еƫ��;
//MPU
#define PI 3.14159265   //ϵ��


/* �������� */
void Get_Angle(u8 way);
	


void vTaskMpu( void * pvParameters )
{
	
	while(1)
	{
		
////		Get_Angle(Way_Angle); 

//		OLED_DrawBMP(2,56,UI_NOSIGNAL8X8,8,8);	
//		OLED_DrawBMP(12,56,UI_ASIGNAL8X8,8,8);
//	
//		OLED_ShowNum(20,56,Angle_BalanceY,4,3,1);
//		OLED_ShowNum(20,46,Gyro_BalanceY,4,3,1);
//		OLED_ShowNum(20,36,Gyro_BalanceZ,4,3,1);
//		OLED_ShowNum(20,26,Acceleration_Z,4,3,1);
		
		
		vTaskDelay( 10 );
	}
	
}


/****************************************************************************
  * @brief    ��ȡ�Ƕ� �����㷨���ǳ����� 
  * @param    ��ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
  * @retval   ��
  * @author   LZM
  * @note      
  */
void Get_Angle(u8 way)
{ 		
		float Accel_Y;
//	  float Accel_X;
//		float Accel_Z;
//		float Accel_SY;
		float Accel_SX;
		float Accel_SZ;
//		float Gyro_X;
		float Gyro_Y;
//		float Gyro_Z;
//		float Gyro_SX;
		float Gyro_SY;
		float Gyro_SZ; //Accel_SY,Accel_SX,Accel_SZ���ڹ��ɵ�
	   	MPU_Temperature=Read_Temperature();   //===��ȡMPU6050�����¶ȴ��������ݣ����Ʊ�ʾ�����¶ȡ�
	
	    if(way==1)                            //===DMP�Ķ�ȡ�����ݲɼ��ж����ѵ�ʱ���ϸ���ѭʱ��Ҫ��
			{	
					Read_DMP();                       //===��ȡ���ٶȡ����ٶȡ����
				
					Angle_BalanceY=Pitch;             //===����ƽ�����
				
//				  Gyro_BalanceX=gyro[0];            //===����ƽ����ٶ�
					Gyro_BalanceY=gyro[1];            //===����ƽ����ٶ�
				  Gyro_BalanceZ=gyro[2];            //===����ƽ����ٶ�
				
//				  Acceleration_X=accel[0];          //===����X����ٶȼ�
//				  Acceleration_Y=accel[1];          //===����Y����ٶȼ�
				  Acceleration_Z=accel[2];          //===����Z����ٶȼ�
			}			
      else
      {
//			Gyro_SX=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //��ȡX��������
			Gyro_SY=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //��ȡY��������
			Gyro_SZ=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
		  Accel_SX=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //��ȡX����ٶȼ�
//		  Accel_SY=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //��ȡY����ٶȼ�
	  	Accel_SZ=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
//		  if(Gyro_SX>32768)  Gyro_SX-=65536;                        //��������ת��  Ҳ��ͨ��shortǿ������ת��
			if(Gyro_SY>32768)  Gyro_SY-=65536;                        //��������ת��  Ҳ��ͨ��shortǿ������ת��
			if(Gyro_SZ>32768)  Gyro_SZ-=65536;                        //��������ת��
	  	if(Accel_SX>32768) Accel_SX-=65536;                       //��������ת��
//			if(Accel_SY>32768) Accel_SY-=65536;                       //��������ת��
		  if(Accel_SZ>32768) Accel_SZ-=65536;                       //��������ת��
				
//			Gyro_BalanceX=-Gyro_SX;                                   //����������X
			Gyro_BalanceY=-Gyro_SY;                                   //����������Y
			Gyro_BalanceZ=-Gyro_SZ;                                   //����������Z
				
//			Acceleration_X=Accel_SX;                                   //===����X����ٶȼ�		
//			Acceleration_Y=Accel_SY;                                   //===����Y����ٶȼ�		
			Acceleration_Z=Accel_SZ;                                   //===����Z����ٶȼ�	
				
//			Accel_X=atan2(Accel_SY,Accel_SZ)*180/PI;                  //���� X ���
 	   	Accel_Y=atan2(Accel_SX,Accel_SZ)*180/PI;                  //���� Y ���	
//		  Accel_Z=atan2(Accel_SX,Accel_SY)*180/PI;                  //���� Z ���	
			
//      Gyro_X=Gyro_SX/16.4;                                      //����������ת��				
  		Gyro_Y=Gyro_SY/16.4;                                      //����������ת��	
//		  Gyro_Z=Gyro_SZ/16.4;                                      //����������ת��
				
			//�������Ǻ��ٶȵó����
      if(way==2)		  	
			{
//				Kalman_Filter(Accel_X,-Gyro_X,1);                       //�������˲�	
 				Kalman_Filter(Accel_Y,-Gyro_Y,2);                       //�������˲�	
//				Kalman_Filter(Accel_Z,-Gyro_Z,3);                       //�������˲�	
			}
				
			else if(way==3)
			{
//			  Yijielvbo(Accel_X,-Gyro_X,1);                           //�����˲�
				Yijielvbo(Accel_Y,-Gyro_Y,2);                           //�����˲�
//				Yijielvbo(Accel_Z,-Gyro_Z,3);                           //�����˲�
			}
				
//			Angle_BalanceX=angle_X;                                    //����ƽ�����X
	    Angle_BalanceY=angle_Y;                                    //����ƽ�����Y
//			Angle_BalanceZ=angle_Z;                                    //����ƽ�����Z(���㲻�˵�)
			
			
		} 
}


