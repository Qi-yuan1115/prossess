/************************************************************************/
/*                                                                      */
/*  �����������пƼ����޹�˾                                            */
/*  Zhenshangyou Technologies Co.,Ltd.                                  */
/*                                                                      */
/*  ZLDS200 SDK�ڲ�ʹ�õ�ͷ�ļ�                                         */
/*                                                                      */
/************************************************************************/
#ifndef _DEV_LAN_INC_H_
        #define _DEV_LAN_INC_H_

/************************************************************************/
/* Includes                                                             */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

	typedef struct _UDP_DEVINFOBLOCK { 
		unsigned short				usDeviceType; 
		unsigned char				ucIP[4]; 
		unsigned char				ucMAC[6]; 
	 	unsigned char				ucInfo[256]; 
	}  UDP_DEVINFOBLOCK, *LPUDP_DEVINFOBLOCK; 

	typedef struct _RF_COMMAND_PACKET { 
		unsigned long				ucCommand; 
		unsigned long				ulAttachSize;
		unsigned long				ulOffset;
		unsigned long				ulSize;
	}  RF_COMMAND_PACKET, *LPRF_COMMAND_PACKET; 

	typedef struct _RF_IMAGE_RECT {
		unsigned short				wLeft;
		unsigned short				wTop;
		unsigned short				wWidth;
		unsigned short				wHeight;
	} RF_IMAGE_RECT, *LPRF_IMAGE_RECT;

//////////////////////////////////////////////////////////////////////////

	#define ZLDS200_Port			620
	#define UDP_Info_Port			6001

//////////////////////////////////////////////////////////////////////////

	#define RX_LAN_TimeOut			4000
	#define LANStackSize			(1 * 1024 * 1024)		// max 1MB

	#define LANRcvPackSize			32768
	#define LANTrPackSize			512
	
	#define ProfileSize				15000
	#define PixelsSize				(2 * 640)
	#define ImageSize				(512 * 640)

	#define UserCfgAreaSize			512
	#define FactCfgAreaSize			1024
	
	#define TablesSize				(2 * 2 * 640 * 512)
	#define FirmwareSize			(1 * 1024 * 1024)

//////////////////////////////////////////////////////////////////////////
//	User functions
	#define GetResult				0x01
	#define GetImage				0x02
	#define GetImageBuffer			        0x03
	#define ReadParams				0x04
	#define WriteParams				0x05
	#define FlushParams				0x06
	#define CalcAngle				0x07
	#define Reboot			        0x14
	#define Shutdown				0x16
	#define Disconnect				0x19
//	Factory functions
	#define GetPixels				0x81
	#define ReadFactoryParams		0x82
	#define WriteFactoryParams		0x83
	#define FlushFactoryParams		0x84
	#define ReadFactoryTables		0x85
	#define WriteFactoryTables		0x86
	#define FlushFactoryTables		0x87
//	Firmware functions
	#define ReadFirmware			0x88
	#define WriteFirmware			0x89
	#define FlushFirmware			0x8A

//////////////////////////////////////////////////////////////////////////

//	Sensor Errors
	#define MAX_ARRAY               32
	typedef enum errs{
		SENSOR_NOERR,                               //��ʼ״̬�޴���
			SENSOR_COMERROR,                            //����ͨ�Ŵ���
			SENSOR_TIMEOUT,                             //��ʱ����
			SENSOR_DATABREAK,                           //���ݶ�ʧ
			SENSOR_STATEERROR,                          //��������ǰ״̬��
			COM_STATEERROR,								//���ڵ�ǰ״̬��
			COM_MUTEXERROR,								//���봮���ٽ���Դ����
			SENSOR_LISTENEROVERFLOW,                    //listener���
			SENSOR_RESULTBUFFEROVERFLOW,                //������������
			SENSOR_SENSORNUMOVERFLOW,                   //�������������
			COM_COMNUMOVERFLOW,							//���ڶ������
			SENSOR_PARAERROR,                           //��ڲ�������
			SNESOR_LOGINITERROR,                        //LOG��ʼ������
			SENSOR_NETERROR,							//���ڽ��հ�����
			SENSOR_FUNCTION_INVALID,					//����δ����
			SENSOR_SERIALNUM_INVALID					//���������к�δ��Ȩ
	}SENSOR_ERR;

#endif
