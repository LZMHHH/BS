

/*
			��һ������ ulBitsToClearOnEntry�����ã�����ִ��ǰ����
		          ulNotifiedValue &= ~ulBitsToClearOnEntry
		          �򵥵�˵���ǲ���ulBitsToClearOnEntry�Ǹ�λ��1����ônotification value
		          ���Ǹ�λ�ͻᱻ���㡣

		          ����ulBitsToClearOnEntry = 0x00000000���Ǻ���ִ��ǰ��������λ��
		
		    �ڶ������� ulBitsToClearOnExit�����ã������˳�ǰ����			
				  ulNotifiedValue &= ~ulBitsToClearOnExit
		          �򵥵�˵���ǲ���ulBitsToClearOnEntry�Ǹ�λ��1����ônotification value
		          ���Ǹ�λ�ͻᱻ���㡣

				  ����ulBitsToClearOnExi = 0xFFFFFFFF���Ǻ����˳�ǰ�������λ��
		
		    ע��ulNotifiedValue��ʾ����vTaskMsgPro��������ƿ�����ı�����		
		*/
		
		xResult = xTaskNotifyWait(0x00000000,      
						          0xFFFFFFFF,      
						          &ulValue,        /* ����ulNotifiedValue������ulValue�� */
						          xMaxBlockTime);  /* ��������ӳ�ʱ�� */
								  
*/

/*
	SD�� + FATFS�ļ�ϵͳ�Ѿ���ͨ��ע�����������ر�����detect���ţ��궨��SD_DETECT_CON��
*/