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
  * 实验平台:ST实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "MpuTask.h"
#include "filter.h"

//MPU
int   MPU_Temperature;            //显示温度
u8    Way_Angle=2;                //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波
//float Angle_BalanceX;           //平衡倾角X 
float Angle_BalanceY;             //平衡倾角Y
//float Angle_BalanceZ;           //平衡倾角Z 
//float Gyro_BalanceX;            //陀螺仪X
float Gyro_BalanceY;              //陀螺仪Y
float Gyro_BalanceZ;              //陀螺仪Z
//float Acceleration_X;           //X轴加速度计
//float Acceleration_Y;           //Y轴加速度计
float Acceleration_Z;             //Z轴加速度计
float Mechanical_deviation = 0;   //机械偏差;
//MPU
#define PI 3.14159265   //系数


/* 函数声明 */
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
  * @brief    获取角度 三种算法都非常理想 
  * @param    获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
  * @retval   无
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
		float Gyro_SZ; //Accel_SY,Accel_SX,Accel_SZ用于过渡的
	   	MPU_Temperature=Read_Temperature();   //===读取MPU6050内置温度传感器数据，近似表示主板温度。
	
	    if(way==1)                            //===DMP的读取在数据采集中断提醒的时候，严格遵循时序要求
			{	
					Read_DMP();                       //===读取加速度、角速度、倾角
				
					Angle_BalanceY=Pitch;             //===更新平衡倾角
				
//				  Gyro_BalanceX=gyro[0];            //===更新平衡角速度
					Gyro_BalanceY=gyro[1];            //===更新平衡角速度
				  Gyro_BalanceZ=gyro[2];            //===更新平衡角速度
				
//				  Acceleration_X=accel[0];          //===更新X轴加速度计
//				  Acceleration_Y=accel[1];          //===更新Y轴加速度计
				  Acceleration_Z=accel[2];          //===更新Z轴加速度计
			}			
      else
      {
//			Gyro_SX=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //读取X轴陀螺仪
			Gyro_SY=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //读取Y轴陀螺仪
			Gyro_SZ=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //读取Z轴陀螺仪
		  Accel_SX=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //读取X轴加速度计
//		  Accel_SY=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //读取Y轴加速度计
	  	Accel_SZ=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //读取Z轴加速度计
//		  if(Gyro_SX>32768)  Gyro_SX-=65536;                        //数据类型转换  也可通过short强制类型转换
			if(Gyro_SY>32768)  Gyro_SY-=65536;                        //数据类型转换  也可通过short强制类型转换
			if(Gyro_SZ>32768)  Gyro_SZ-=65536;                        //数据类型转换
	  	if(Accel_SX>32768) Accel_SX-=65536;                       //数据类型转换
//			if(Accel_SY>32768) Accel_SY-=65536;                       //数据类型转换
		  if(Accel_SZ>32768) Accel_SZ-=65536;                       //数据类型转换
				
//			Gyro_BalanceX=-Gyro_SX;                                   //更新陀螺仪X
			Gyro_BalanceY=-Gyro_SY;                                   //更新陀螺仪Y
			Gyro_BalanceZ=-Gyro_SZ;                                   //更新陀螺仪Z
				
//			Acceleration_X=Accel_SX;                                   //===更新X轴加速度计		
//			Acceleration_Y=Accel_SY;                                   //===更新Y轴加速度计		
			Acceleration_Z=Accel_SZ;                                   //===更新Z轴加速度计	
				
//			Accel_X=atan2(Accel_SY,Accel_SZ)*180/PI;                  //计算 X 倾角
 	   	Accel_Y=atan2(Accel_SX,Accel_SZ)*180/PI;                  //计算 Y 倾角	
//		  Accel_Z=atan2(Accel_SX,Accel_SY)*180/PI;                  //计算 Z 倾角	
			
//      Gyro_X=Gyro_SX/16.4;                                      //陀螺仪量程转换				
  		Gyro_Y=Gyro_SY/16.4;                                      //陀螺仪量程转换	
//		  Gyro_Z=Gyro_SZ/16.4;                                      //陀螺仪量程转换
				
			//由陀螺仪和速度得出倾角
      if(way==2)		  	
			{
//				Kalman_Filter(Accel_X,-Gyro_X,1);                       //卡尔曼滤波	
 				Kalman_Filter(Accel_Y,-Gyro_Y,2);                       //卡尔曼滤波	
//				Kalman_Filter(Accel_Z,-Gyro_Z,3);                       //卡尔曼滤波	
			}
				
			else if(way==3)
			{
//			  Yijielvbo(Accel_X,-Gyro_X,1);                           //互补滤波
				Yijielvbo(Accel_Y,-Gyro_Y,2);                           //互补滤波
//				Yijielvbo(Accel_Z,-Gyro_Z,3);                           //互补滤波
			}
				
//			Angle_BalanceX=angle_X;                                    //更新平衡倾角X
	    Angle_BalanceY=angle_Y;                                    //更新平衡倾角Y
//			Angle_BalanceZ=angle_Z;                                    //更新平衡倾角Z(计算不了的)
			
			
		} 
}


