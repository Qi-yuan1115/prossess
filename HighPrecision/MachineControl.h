#pragma once
#include "mscomm1.h"

class CMachineControl
{
public:
	CMachineControl(void);
	//定义带参构造函数，用外部定义的指针pMscommL去初始化类成员变量指针m_pMscommL
	//
	//CMachineControl(CMscomm1* pMscommL,CMscomm1* pMscommR):m_pMscommL(pMscommL),m_pMscommR(pMscommR){};
	
	//CMachineControl(int* pTEST):ptest(pTEST){};
	~CMachineControl(void);

public:
	
		
	bool ConnectMotor(short PortNum,CString PortBaud,CMscomm1& m_pMscomm);	
	bool DisConnectMotor(CMscomm1& m_pMscomm,bool bFlagPrMode,bool IsOnlyDisconn);	
	
	void MotorPowerON(CMscomm1& m_pMscomm);	
	void MotorStop(CMscomm1& m_pMscomm);
	bool SetSpeed(CMscomm1& m_pMscomm,int Speed);
	//Speed的单位为rpm，Round单位为圈,
	bool MotorMove(double Round,bool bFlagPrMode,CMscomm1& m_pMscomm);	
	bool OnlyMotorPowerOFF(CMscomm1& m_pMscomm);
	bool OnlyMotorPowerON(CMscomm1& m_pMscomm);
	unsigned int crc_chk(unsigned char * data, unsigned char length);
	int Transimit(unsigned char TxData[],CMscomm1& m_pMscomm);
	int Transimit_32(unsigned char TxData_32[],CMscomm1& m_pMscomm);
	int HexToDec(CString HexData);
	int ReadRegData(int RegAddr_H,int RegAddr_L,CMscomm1& m_pMscomm);
	int String2hex(CString str);
	char ConvertHexChar(char ch);
	int OnlyReadPPU(CMscomm1& m_pMscomm);
	
	bool MotorReturnZero(CMscomm1& m_pMscomm,bool bFlagPrMode);
	bool MotorReturnRLimit(CMscomm1& m_pMscomm,bool bFlagPrMode);
	int StringToMultiBitHex(CString str);
	int IsMotorLimit(CMscomm1& m_pMscomm);
public:
	int m_ComNumL;
	int m_ComNumR;
	CMscomm1* m_pMscommL;
	CMscomm1* m_pMscommR;
	CMscomm1* m_MscomT;
	int* ptest;
	bool MotorPause(CMscomm1& m_pMscomm);
	bool MotorStart(CMscomm1& m_pMscomm);
};

