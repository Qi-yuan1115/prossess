/************************************************************************/
/*                                                                      */
/*  深圳市真尚有科技有限公司                                            */
/*  Zhenshangyou Technologies Co.,Ltd.                                  */
/*                                                                      */
/*  ZLDS200 SDK公共头文件                                               */
/*                                                                      */
/************************************************************************/

#ifndef _DEV_LAN_LIB_H_
        #define _DEV_LAN_LIB_H_

/************************************************************************/
/* Includes                                                             */
/************************************************************************/

        //#include <WINSOCK2.H>
        //#include <windows.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
        #ifdef __cplusplus
        extern "C" {
        #endif

        typedef struct _UDP_DEVINFOBLOCK_PC {
	        unsigned short				usDeviceType;
        	unsigned char				ucIP[4];
	        unsigned char				ucMAC[6];
         	unsigned char				ucInfo[256];
	        _UDP_DEVINFOBLOCK_PC  *		pNext;
        }  UDP_DEVINFOBLOCK_PC, *LPUDP_DEVINFOBLOCK_PC;

		typedef struct _TCP_PARAINFODevice625_PC {
			unsigned char				ucLaserLevel;
			unsigned char				wExposureTime[2];
			unsigned char				wProcessingTime[2];
			unsigned char				ucWindowLeft;
			unsigned char				ucWindowWidth;
			unsigned char				ucWindowTop;
			unsigned char				ucWindowHeight;
			unsigned char				ucReserved1;
			unsigned char				sRotationAngle[2];
			unsigned char				wExtSyncSignal[2];
			unsigned char				ucExtSyncDivider;
			unsigned char				ucExtSyncDelay;
			unsigned char				ucAnalogDotCount;
			unsigned char				ucAnalogDotHold;
			unsigned char				ucTCPAddress[4];
			unsigned char				ucTCPSubnetMask[4];
			unsigned char				ucUDPAddress[4];
			unsigned char				wUDPPort[2];
			unsigned char				ucUDPFrequency;
			unsigned char				wTCPPort[2];
			unsigned char				ucDHCP;
			unsigned char				ucSyncInOutLine;
			unsigned char				ucAutoExposure;
			unsigned char				ucPixelBrightnessThres;
			unsigned char				ucLegacyMode;
			unsigned char				ucRawImageMode;
			unsigned char				cInterpolation;
			unsigned char				ucModbusTcpEnabled;
			unsigned char				ucModbusTcpAddr[3];
			unsigned char				wModbusTcpPort;
			unsigned char                ucReserved2[471];
			_TCP_PARAINFODevice625_PC  *	pNext;
        }  PARAINFODevice625_PC, *TCP_PARAINFODevice625_PC;

//////////////////////////////////////////////////////////////////////////
//
//	ZLDS200 Device Type
//

        #define ZLDS200_Device1	620
        #define ZLDS200_Device2	625

//////////////////////////////////////////////////////////////////////////
//
//	Common function
//

        UDP_DEVINFOBLOCK_PC* _stdcall   Dev_Search				(USHORT, USHORT);
        void  _stdcall                  Dev_ClearList			(UDP_DEVINFOBLOCK_PC *);

//////////////////////////////////////////////////////////////////////////
//
//	ZLDS200 LAN functions
//
//		User functions
        SOCKET _stdcall                 ZLDS200_Connect             ( UDP_DEVINFOBLOCK_PC * );
        BOOL _stdcall                   ZLDS200_Disconnect          ( SOCKET );
        BOOL _stdcall					ZLDS200_GetResult	        ( SOCKET, void * ,int *);
        BOOL _stdcall					ZLDS200_GetImage	        ( SOCKET, void * );
        BOOL _stdcall					ZLDS200_ReadParams          ( SOCKET, void * );
        BOOL _stdcall					ZLDS200_WriteParams         ( SOCKET, void * );
        BOOL _stdcall					ZLDS200_FlushParams	    	( SOCKET, BOOL );
        BOOL _stdcall					ZLDS200_CalcAngle			( SOCKET, void *);
		BOOL _stdcall					ZLDS200_Reboot		    	( SOCKET);
		BOOL _stdcall					ZLDS200_Shutdown	 		( SOCKET);

//////////////////////////////////////////////////////////////////////////

		class DES
		{
			public: 
				BOOL CDesEnter(const BYTE* in, BYTE* out, int datalen, const BYTE key[8], BOOL type); 
				BOOL CDesMac(const BYTE* mac_data, BYTE* mac_code, int datalen, const BYTE key[8]); 
			private: 
				void XOR(const BYTE in1[8], const BYTE in2[8], BYTE out[8]); 
				LPBYTE Bin2ASCII(const BYTE byte[64], BYTE bit[8]); 
				LPBYTE ASCII2Bin(const BYTE bit[8], BYTE byte[64]); 
				void GenSubKey(const BYTE oldkey[8], BYTE newkey[16][8]); 
				void endes(const BYTE m_bit[8], const BYTE k_bit[8], BYTE e_bit[8]); 
				void undes(const BYTE m_bit[8], const BYTE k_bit[8], BYTE e_bit[8]); 
			void SReplace(BYTE s_bit[8]); 	
		};

        #ifdef __cplusplus
        }
        #endif

//////////////////////////////////////////////////////////////////////////
#endif
