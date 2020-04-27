/**
  ******************************************************************************
  * @file    
  * @author  lss
  * @version V1.0
  * @date    2020-xx-xx
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 实验平台:双创实验室-LZM
  * 
  * Wechat：qabc132321
  *
  ******************************************************************************
  */
#include "MpuTask.h"	



//MPU
CLASS_mpu_data mpu_data; 



void vTaskMpu( void * pvParameters )
{
	BaseType_t xReturn = pdPASS;/* 定义一个创建信息返回值，默认为pdPASS */
	
	while(1)
	{

		//获取二值信号量 xSemaphore,没获取到则一直等待
		xReturn = xSemaphoreTake(BinarySem_Mpu,/* 二值信号量句柄 */
                              portMAX_DELAY); /* 等待时间 */
		
		if(pdTRUE == xReturn)
       Period_Control();
		
	}
	
}



//5ms 周期处理
u8 Period_Control(void)
{
	
	Get_Angle(&mpu_data,2);
	
	return 0;
}


/****************************************************************************
  * @brief    获取角度 三种算法都非常理想 
  * @param    获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
  * @retval   无
  * @author   LZM
  * @note      
  */
void Get_Angle(CLASS_mpu_data *mpudata,u8 way)
{ 		
//			float Accel_Y;
//			float Accel_X;
//			float Accel_Z;
//			float Accel_SY;
//			float Accel_SX;
//			float Accel_SZ;
//			float Gyro_X;
//			float Gyro_Y;
//			float Gyro_Z;
//			float Gyro_SX;
//			float Gyro_SY;
//			float Gyro_SZ; //Accel_SY,Accel_SX,Accel_SZ用于过渡的
//				mpudata->Temperature=Read_Temperature();   //===读取MPU6050内置温度传感器数据，近似表示主板温度。
//		
//				if(way==1)                            //===DMP的读取在数据采集中断提醒的时候，严格遵循时序要求
//				{	
//						Read_DMP();                       //===读取加速度、角速度、倾角
//					
//	//					mpudata->Angle_BalanceY=Pitch;             //===更新平衡倾角
//	//				
//	//				  mpudata->Gyro_BalanceX=gyro[0];            //===更新平衡角速度
//	//					mpudata->Gyro_BalanceY=gyro[1];            //===更新平衡角速度
//	//				  mpudata->Gyro_BalanceZ=gyro[2];            //===更新平衡角速度
//					
//						mpudata->Acceleration_X=accel[0];          //===更新X轴加速度计
//						mpudata->Acceleration_Y=accel[1];          //===更新Y轴加速度计
//						mpudata->Acceleration_Z=accel[2];          //===更新Z轴加速度计
//				}			
//				else
//				{
//						Gyro_SX=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_XOUT_L);    //读取X轴陀螺仪
//						Gyro_SY=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //读取Y轴陀螺仪
//						Gyro_SZ=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //读取Z轴陀螺仪
//						Accel_SX=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //读取X轴加速度计
//						Accel_SY=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_YOUT_L); //读取Y轴加速度计
//						Accel_SZ=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //读取Z轴加速度计
//						if(Gyro_SX>32768)  Gyro_SX-=65536;                        //数据类型转换  也可通过short强制类型转换
//						if(Gyro_SY>32768)  Gyro_SY-=65536;                        //数据类型转换  也可通过short强制类型转换
//						if(Gyro_SZ>32768)  Gyro_SZ-=65536;                        //数据类型转换
//						if(Accel_SX>32768) Accel_SX-=65536;                       //数据类型转换
//						if(Accel_SY>32768) Accel_SY-=65536;                       //数据类型转换
//						if(Accel_SZ>32768) Accel_SZ-=65536;                       //数据类型转换
//							
//	//					mpudata->Gyro_BalanceX=-Gyro_SX;                                   //更新陀螺仪X(就是角速度)
//	//					mpudata->Gyro_BalanceY=-Gyro_SY;                                   //更新陀螺仪Y
//	//					mpudata->Gyro_BalanceZ=-Gyro_SZ;                                   //更新陀螺仪Z
//							
//						mpudata->Acceleration_X=Accel_SX;                                   //===更新X轴加速度计		
//						mpudata->Acceleration_Y=Accel_SY;                                   //===更新Y轴加速度计		
//						mpudata->Acceleration_Z=Accel_SZ;                                   //===更新Z轴加速度计	
//							
//						
//							
//						Accel_X=atan2(Accel_SY,Accel_SZ)*180/PI;                  //计算 X 倾角
//						Accel_Y=atan2(Accel_SX,Accel_SZ)*180/PI;                  //计算 Y 倾角	
//	//					Accel_Z=atan2(Accel_SX,Accel_SY)*180/PI;                  //计算 Z 倾角	
//						
//						Gyro_X=Gyro_SX/16.4;                                      //陀螺仪量程转换				
//						Gyro_Y=Gyro_SY/16.4;                                      //陀螺仪量程转换	
//	//					Gyro_Z=Gyro_SZ/16.4;                                      //陀螺仪量程转换
//							
//						//由陀螺仪和速度得出倾角
//						if(way==2)		  	
//						{
//							Kalman_Filter(Accel_X,-Gyro_X,1);                       //卡尔曼滤波	
//							Kalman_Filter(Accel_Y,-Gyro_Y,2);                       //卡尔曼滤波	
//	//						Kalman_Filter(Accel_Z,-Gyro_Z,3);                       //卡尔曼滤波	
//						}
//							
//						else if(way==3)
//						{
//	//						Yijielvbo(Accel_X,-Gyro_X,1);                           //互补滤波
//	//						Yijielvbo(Accel_Y,-Gyro_Y,2);                           //互补滤波
//	//						Yijielvbo(Accel_Z,-Gyro_Z,3);                           //互补滤波
//						}
//							
//						mpudata->Angle_BalanceX=angle_X;                                    //更新平衡倾角X
//						mpudata->Angle_BalanceY=angle_Y;                                    //更新平衡倾角Y
//	//					mpudata->Angle_BalanceZ=angle_Z;                                    //更新平衡倾角Z(计算不了的)		
//				
//			} 
}


