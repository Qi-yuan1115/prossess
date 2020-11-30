/************************************************************************/
/*                                                                      */
/*  深圳市真尚有科技有限公司                                            */
/*  Zhenshangyou Technologies Co.,Ltd.                                  */
/*                                                                      */
/*  ZLDS200 SDK内部使用的头文件                                         */
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
		SENSOR_NOERR,                               //初始状态无错误
			SENSOR_COMERROR,                            //串口通信错误
			SENSOR_TIMEOUT,                             //超时错误
			SENSOR_DATABREAK,                           //数据丢失
			SENSOR_STATEERROR,                          //传感器当前状态错
			COM_STATEERROR,								//串口当前状态错
			COM_MUTEXERROR,								//进入串口临界资源错误
			SENSOR_LISTENEROVERFLOW,                    //listener溢出
			SENSOR_RESULTBUFFEROVERFLOW,                //结果缓冲区溢出
			SENSOR_SENSORNUMOVERFLOW,                   //传感器定义溢出
			COM_COMNUMOVERFLOW,							//串口定义溢出
			SENSOR_PARAERROR,                           //入口参数错误
			SNESOR_LOGINITERROR,                        //LOG初始化错误
			SENSOR_NETERROR,							//网口接收包出错
			SENSOR_FUNCTION_INVALID,					//功能未交费
			SENSOR_SERIALNUM_INVALID					//传感器序列号未授权
	}SENSOR_ERR;

#endif
