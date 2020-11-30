#include "StdAfx.h"
#include "MachineControl.h"
#include "mscomm1.h"

#define NegativeLimit -383934
#define PositiveLimit 640000
#define MotorMoveLimit 60
//CMscomm1* m_pMscommL;
//CMscomm1* m_pMscommR;

//extern CMscomm1 m_Mscomm_L;
//extern CMscomm1 m_Mscomm_R;
 

CMachineControl::CMachineControl(void)
{
}
CMachineControl::~CMachineControl(void)
{
}
bool CMachineControl::ConnectMotor(short PortNum,CString PortBaud,CMscomm1& m_pMscomm)
{		
	bool IsConnected=false;
	CString strBaudtemp=PortBaud+_T(",n,8,2");//8,N,2		
	m_pMscomm.put_CommPort(PortNum);	
	m_pMscomm.put_Settings(strBaudtemp);	//���ö˿�	
	m_pMscomm.put_InputMode(1);					//�Զ����Ʒ�ʽ��ȡ
	m_pMscomm.put_RThreshold(1);				//������������һ�������ַ�ʱ�����¼�
	if (!m_pMscomm.get_PortOpen())//�������û�д����
	{
		m_pMscomm.put_PortOpen(TRUE);		
	} 
	if (m_pMscomm.get_PortOpen())
	{

		m_pMscomm.put_InputLen(0);					//��ȡ�ؼ��л�������ȫ������
		m_pMscomm.get_Input();						//Ԥ���������������������		
		IsConnected=true;
	}
	else
	{
		IsConnected=false;
	}
	return IsConnected;

}
bool CMachineControl::DisConnectMotor(CMscomm1& m_pMscomm,bool bFlagPrMode,bool IsOnlyDisconn)
{
	bool IsDisConnect=false;	
	bool IsReturnLimit=true;
	//�Ͽ���������	
	if (m_pMscomm.get_PortOpen())
	{
		if (IsOnlyDisconn)//ֻ�Ͽ�����
		{
			/*unsigned char TxData[8];
			TxData[0]=0x01;
			TxData[1]=0x06;
			TxData[2]=0x02;
			TxData[3]=0x14;
			TxData[4]=0x01;
			TxData[5]=0x00;	
			Transimit(TxData,m_pMscomm);*/
			/*Sleep(50);*/
			m_pMscomm.put_PortOpen(FALSE);	
		}
		else//��Ҫ�ص�����λ��
		{
			//IsReturnLimit=MotorReturnRLimit(m_pMscomm,bFlagPrMode);
			
			if (IsReturnLimit)
			{
				Sleep(50);
				unsigned char TxData[8];
				TxData[0]=0x01;
				TxData[1]=0x06;
				TxData[2]=0x02;
				TxData[3]=0x14;
				TxData[4]=0x01;
				TxData[5]=0x00;	
				Transimit(TxData,m_pMscomm);
				Sleep(50);
				m_pMscomm.put_PortOpen(FALSE);			
			}	
			/*else
			{
				CMachineControl::DisConnectMotor(m_pMscomm,bFlagPrMode,IsOnlyDisconn);
			}*/
		}
				
	}
	if (!m_pMscomm.get_PortOpen())
	{
		IsDisConnect=true;
	}
	return IsDisConnect;
}
bool CMachineControl::SetSpeed(CMscomm1& m_pMscomm,int Speed)
{
	bool IsSetSpeed=false;
	int m_Speed;
	m_Speed=Speed*10;
	unsigned char TxData[8];
	COleSafeArray SafeArray_temp;
	m_pMscomm.get_Input();
	//�������ٶ�P5-61����Ҫ����Ϊ100rpm����Ҫ��P5-61��ַ057AHд��100*10=1000
	int nH_Speed,nL_Speed;
	nH_Speed=m_Speed>>8;
	nL_Speed=m_Speed&0x00FF;
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x05;
	TxData[3]=0x7A;
	TxData[4]=nH_Speed;
	TxData[5]=nL_Speed;
	Transimit(TxData,m_pMscomm);
	Sleep(50);
	SafeArray_temp=m_pMscomm.get_Input();
	if (SafeArray_temp.GetOneDimSize())
	{
		IsSetSpeed=true;
	}
	else
	{
		IsSetSpeed=false;
	}
	return IsSetSpeed;
}
void CMachineControl::MotorPowerON(CMscomm1& m_pMscomm)
{

	unsigned char TxData[8];
	unsigned char TxData_32[13];
	//��ʼ��P306��P407
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x01;
	TxData[3]=0x02;
	TxData[4]=0x00;
	TxData[5]=0x01;
	Transimit(TxData,m_pMscomm);

	Sleep(50);

	int nFlagP0101=0;
	nFlagP0101=m_pMscomm.get_CommEvent();
	
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x03;
	TxData[3]=0x0C;
	TxData[4]=0x00;
	TxData[5]=0x01;
	Transimit(TxData,m_pMscomm);
	Sleep(50);	

	//int nFlagP306=0;
	//nFlagP306=m_pMscomm.get_CommEvent();

	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x04;
	TxData[3]=0x0E;
	TxData[4]=0x00;
	TxData[5]=0x01;
	Transimit(TxData,m_pMscomm);
	Sleep(50);	

	//int nFlagP407=0;
	//nFlagP407=m_pMscomm.get_CommEvent();

	//Ȼ���ϵ�P210��1
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x02;
	TxData[3]=0x14;
	TxData[4]=0x00;
	TxData[5]=0x01;	
	Transimit(TxData,m_pMscomm);
	//int nFlagP210=0;
	//nFlagP210=m_pMscomm.get_CommEvent();
	Sleep(50);
	
	//P6-02()��0x0001 3382����INP,��OVLP��INC������λ,10rpm,�����ֹͣ
	TxData_32[0]=0x01;//վ���
	TxData_32[1]=0x10;//�����д����Ĵ���
	TxData_32[2]=0x06;//��ʼ��ַ��λ
	TxData_32[3]=0x04;//��ʼ��ַ��λ
	TxData_32[4]=0x00;//
	TxData_32[5]=0x02;//д�����Ĵ���
	TxData_32[6]=0x04;//�����ֽ���
	TxData_32[7]=0x33;
	TxData_32[8]=0x52;//��Զ�λ
	TxData_32[9]=0x00;
	TxData_32[10]=0x01;//0605Hд0001H	
	Transimit_32(TxData_32,m_pMscomm);
	Sleep(50);

	TxData_32[0]=0x01;//վ���
	TxData_32[1]=0x10;//�����д����Ĵ���
	TxData_32[2]=0x06;//��ʼ��ַ��λ
	TxData_32[3]=0x08;//��ʼ��ַ��λ
	TxData_32[4]=0x00;//
	TxData_32[5]=0x02;//д�����Ĵ���
	TxData_32[6]=0x04;//�����ֽ���
	TxData_32[7]=0x33;
	TxData_32[8]=0x52;//0608Hд3352H
	TxData_32[9]=0x00;
	TxData_32[10]=0x01;//0609Hд0001H	
	Transimit_32(TxData_32,m_pMscomm);
	Sleep(50);
	

	
}
void CMachineControl::MotorStop(CMscomm1& m_pMscomm)
{
	unsigned char TxData[8];
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x05;
	TxData[3]=0x0E;
	TxData[4]=0x03;
	TxData[5]=0xE8;
	Transimit(TxData,m_pMscomm);
}
bool CMachineControl::MotorMove(double Round,bool bFlagPrMode,CMscomm1& m_pMscomm)
{
	
	double m_Round;
	
	int m_NumPPU;//�û���λ�ĸ���
	int nH_PPU,nL_PPU;

	m_Round=Round;
	
	//���ӳ��ֱ�Ĭ��Ϊ128:10,�ҵ���ֱ���Ϊ1,280,000������£�ÿ100,000��PPU��Ӧ�������һȦ
	m_NumPPU=(int)(m_Round*100000.0);
	
	nH_PPU=m_NumPPU>>16;
	nL_PPU=m_NumPPU&0x0000FFFF;
	unsigned char TxData_32[13];
	unsigned char TxData[8];
		

	if (bFlagPrMode)
	{
		bFlagPrMode=!bFlagPrMode;
		

		//��m_NumPPUд��P06-03����16λ��ַΪ0606H����16λ��ַΪ0607H��
		TxData_32[0]=0x01;//վ���
		TxData_32[1]=0x10;//�����д����Ĵ���
		TxData_32[2]=0x06;//��ʼ��ַ��λ
		TxData_32[3]=0x06;//��ʼ��ַ��λ
		TxData_32[4]=0x00;//
		TxData_32[5]=0x02;//д�����Ĵ���
		TxData_32[6]=0x04;//�����ֽ���
		TxData_32[7]=nL_PPU>>8;
		TxData_32[8]=nL_PPU&0x00FF;//0604Hд0082H
		TxData_32[9]=nH_PPU>>8;
		TxData_32[10]=nH_PPU&0x00FF;//0605Hд0001H	
		Transimit_32(TxData_32,m_pMscomm);
		Sleep(50);

		//P5-07(��ַ050Eд��1)
		TxData[0]=0x01;
		TxData[1]=0x06;
		TxData[2]=0x05;
		TxData[3]=0x0E;
		TxData[4]=0x00;
		TxData[5]=0x01;
		Transimit(TxData,m_pMscomm); 
	} 
	else if(!bFlagPrMode)
	{
		bFlagPrMode=!bFlagPrMode;
		//P6-04��0x0001 3352 ����16λ��ַΪ0608H����16λ��ַΪ0609H��
		//P6-05��m_NumPPU��  ����16λ��ַΪ060AH����16λ��ַΪ060BH��
			
		//��m_NumPPUд��P06-05����16λ��ַΪ060AH����16λ��ַΪ060BH��
		TxData_32[0]=0x01;//վ���
		TxData_32[1]=0x10;//�����д����Ĵ���
		TxData_32[2]=0x06;//��ʼ��ַ��λ
		TxData_32[3]=0x0A;//��ʼ��ַ��λ
		TxData_32[4]=0x00;//
		TxData_32[5]=0x02;//д�����Ĵ���
		TxData_32[6]=0x04;//�����ֽ���
		TxData_32[7]=nL_PPU>>8;
		TxData_32[8]=nL_PPU&0x00FF;//0604Hд0082H
		TxData_32[9]=nH_PPU>>8;
		TxData_32[10]=nH_PPU&0x00FF;//0605Hд0001H	
		Transimit_32(TxData_32,m_pMscomm);
		Sleep(50);
		//P5-07(��ַ050Eд��2)��ʾ����PR2
		TxData[0]=0x01;
		TxData[1]=0x06;
		TxData[2]=0x05;
		TxData[3]=0x0E;
		TxData[4]=0x00;
		TxData[5]=0x02;
		Transimit(TxData,m_pMscomm);   
	}
	return bFlagPrMode;
	  
}
int CMachineControl::Transimit(unsigned char TxData[],CMscomm1& m_pMscomm)
{
	//����CRC
	unsigned char data[6];
	for(int i=0;i<6;i++)
	{
		*(data+i) =TxData[i];
	}

	int CRCtemp = crc_chk(data,6);
	int HCRC,LCRC;
	HCRC = CRCtemp >>8;
	LCRC = CRCtemp &0x00FF;
	TxData[6]=LCRC;
	TxData[7]=HCRC;
	
	int i;
	CByteArray array;
	array.RemoveAll();
	array.SetSize(8);
	for (i=0;i<8;i++)
	{
		array.SetAt(i,TxData[i]);//��TxData���ݴ���ByteArray������
	}
	//����TxData�ڵ�ָ��
	m_pMscomm.put_Output(COleVariant(array));

	return 1;
}
bool CMachineControl::OnlyMotorPowerOFF(CMscomm1& m_pMscomm)
{
	bool IsPowerOFF=false;
	COleSafeArray SafeArray_temp;
	m_pMscomm.get_Input();
	unsigned char TxData[8];
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x02;
	TxData[3]=0x14;
	TxData[4]=0x00;
	TxData[5]=0x00;	
	Transimit(TxData,m_pMscomm);
	Sleep(50);
	SafeArray_temp=m_pMscomm.get_Input();
	if (SafeArray_temp.GetOneDimSize())
	{
		IsPowerOFF=true;
	}
	else
	{
		IsPowerOFF=false;
	}
	
	return IsPowerOFF;
}
bool CMachineControl::OnlyMotorPowerON(CMscomm1& m_pMscomm)
{
	bool IsPowerON=false;
	if (!m_pMscomm.get_PortOpen())
	{
		m_pMscomm.put_PortOpen(TRUE);
	}
	if (m_pMscomm.get_PortOpen())
	{
		COleSafeArray SafeArray_temp;
		m_pMscomm.get_Input();
		unsigned char TxData[8];
		TxData[0]=0x01;
		TxData[1]=0x06;
		TxData[2]=0x02;
		TxData[3]=0x14;
		TxData[4]=0x00;
		TxData[5]=0x01;	
		Transimit(TxData,m_pMscomm);
		Sleep(50);
		SafeArray_temp=m_pMscomm.get_Input();
		if (SafeArray_temp.GetOneDimSize())
		{
			IsPowerON=true;
		}
		else
		{
			IsPowerON=false;
		}
	}
	return IsPowerON;
}
int CMachineControl::Transimit_32(unsigned char TxData_32[],CMscomm1& m_pMscomm)
{
	unsigned char data[11];
	for(int i=0;i<11;i++)
	{
		*(data+i) =TxData_32[i];
	}

	int CRCtemp = crc_chk(data,11);
	int HCRC,LCRC;
	HCRC = CRCtemp >>8;
	LCRC = CRCtemp &0x00FF;
	TxData_32[11]=LCRC;
	TxData_32[12]=HCRC;

	int i;
	CByteArray array;
	array.RemoveAll();
	array.SetSize(13);
	for (i=0;i<13;i++)
	{
		array.SetAt(i,TxData_32[i]);//��TxData���ݴ���ByteArray������
	}
	//����TxData�ڵ�ָ��
	m_pMscomm.put_Output(COleVariant(array));

	return 1;
}
unsigned int CMachineControl::crc_chk(unsigned char * data, unsigned char length)
{


	int j;
	unsigned int crc_reg=0xFFFF;              
	{
		while(length--)
		{
			crc_reg^=*(data++);
			for(j=0;j<8;j++)
			{
				if(crc_reg&0x01)
				{
					crc_reg=(crc_reg>>1)^0xA001;

				}
				else
				{
					crc_reg=crc_reg>>1;
				}
			}	
		}
		return crc_reg;
	}

}
int CMachineControl::HexToDec(CString HexData)
{
	int DecData;	
	int nTemp[2];	
	CString strZero=_T("0");
	if(HexData.GetLength()==1)
	{
		HexData=strZero+HexData;
	}
	char* s=(char*)HexData.GetBuffer(HexData.GetLength());
	
	for (int i=0;i<2;i++)
	{
		if (s[i]<='9')
		{
			nTemp[i]=s[i]-'0';
		}
		else if(s[i]>='A'&&s[i]<='Z')
		{
			nTemp[i]=s[i]-'A'+10;
		}
		else if(s[i]>='a'&&s[i]<='z')
		{
			nTemp[i]=s[i]-'a'+10;
		}

	}	
	DecData=nTemp[0]*16+nTemp[1];
	return DecData;
}
int CMachineControl::ReadRegData(int RegAddr_H,int RegAddr_L,CMscomm1& m_pMscomm)
{	
	unsigned char TxData[8];	
	VARIANT variant_inp;//�Ӵ��ڽ�������ԭʼ���ݾ���VARIANT��
	//VARIANT variant_temp;
	COleSafeArray safearray_inp;//
	long len,k;
	byte rxdata[1024];//����BYTE�����飬byte������typedef���unsigned char��0~255��
	CString strtemp,strtemp1,strHData,strLData;
	int nHData,nLData,nResData;
	TxData[0]=0x01;
	TxData[1]=0x03;
	TxData[2]=RegAddr_H;
	TxData[3]=RegAddr_L;
	TxData[4]=0x00;
	TxData[5]=0x01;
	Transimit(TxData,m_pMscomm);
	Sleep(50);
	variant_inp =m_pMscomm.get_Input();//�Ƚ����ջ����������ݴ���variant_inp
	
	safearray_inp = variant_inp;//����ת��VARIANT��COleSafearray(ǿ��ת��)
	len =safearray_inp.GetOneDimSize();//len��ʾsafearray����ĳ���
	for (k =0;k<len;k++) //����ѭ��
	{
		//�����յ������ݴ���byte������rxdata��
		//��һ������k��ʾ
		safearray_inp.GetElement(&k,rxdata +k);
	}
	for (k =0;k <len;k++)//�������ʽ��ΪCString�ͱ���
	{
		strtemp.Format(_T("%02X "), *(rxdata +k));			
		strtemp = strtemp.Right(3);
		strtemp1 += strtemp;			
	}
	strHData=strtemp1.Mid(9,2);
	strLData=strtemp1.Mid(12,2);
	nHData=String2hex(strHData);
	nLData=String2hex(strLData);

	////nHData=HexToDec(strHData);
	////nLData=HexToDec(strLData);
	nResData=(nHData<<8)+nLData;
	return nResData;
}
int CMachineControl::String2hex(CString str)
{
	int hexdata,lowhexdata;
	int hexdatalen = 0;
	CByteArray senddata;
	int len = str.GetLength();
	hexdata=0;
	senddata.SetSize(len/2);
	int i;
	for(i=0;i<len;)
	{
		char lstr,hstr=str[i];
		if(hstr == ' ')
		{
			i++;
			continue;
		}	
		i++;
		if(i>=len)
			break;
		lstr = str[i];
		hexdata= ConvertHexChar(hstr);
		lowhexdata= ConvertHexChar(lstr);
		if((hexdata==16)||(lowhexdata==16))
			break;
		else
			hexdata =hexdata*16 + lowhexdata;
		i++;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdata;
}
char CMachineControl::ConvertHexChar(char ch) 
{  
	if((ch>='0')&&(ch<='9')) return ch-0x30;  
	else if((ch>='A')&&(ch<='F')) return ch-'A'+10;  
	else if((ch>='a')&&(ch<='f')) return ch-'a'+10; 
	else return (-1); 
} 
int CMachineControl::OnlyReadPPU(CMscomm1& m_pMscomm)
{
	int nNum_PPU=0;

	CString* strRes=NULL;
	strRes=new CString[2];
	COleSafeArray safearrayTemp;
	DWORD SafeArrayLen;
	unsigned char TxData[8];

	COleSafeArray safearray_inp;//
	long len,k;
	byte rxdata[1024];//����BYTE�����飬byte������typedef���unsigned char��0~255��
	CString strtemp,strtemp1,strHData,strLData/*,strFullData*/;
	CString strLAdd_HData,strLAdd_LData;
	CString strHAdd_HData,strHAdd_LData;
	
	//P0-49��0062H��д��2�Ը���������
	m_pMscomm.get_Input();//Ԥ���������������������
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x00;
	TxData[3]=0x62;
	TxData[4]=0x00;				
	TxData[5]=0x02;
	Transimit(TxData,m_pMscomm);
	
	Sleep(50);
	safearrayTemp=m_pMscomm.get_Input();
	SafeArrayLen= safearrayTemp.GetOneDimSize();
	if (SafeArrayLen)
	{
		//��ȡP0-52(0068H)���32λ����
		Sleep(50);
		m_pMscomm.get_Input();//Ԥ���������������������
		TxData[0]=0x01;
		TxData[1]=0x03;
		TxData[2]=0x00;
		TxData[3]=0x68;
		TxData[4]=0x00;
		TxData[5]=0x02;//���޸ĳ�Ϊ��ȡ2���֣���32λ��
		Transimit(TxData,m_pMscomm);
		Sleep(50);
		safearrayTemp=m_pMscomm.get_Input();
		SafeArrayLen= safearrayTemp.GetOneDimSize();
		if (SafeArrayLen)
		{			
			safearray_inp = safearrayTemp;//����ת��VARIANT��COleSafearray(ǿ��ת��)
			len =safearray_inp.GetOneDimSize();//len��ʾsafearray����ĳ���
			for (k =0;k<len;k++) //����ѭ��
			{
				//�����յ������ݴ���byte������rxdata��
				//��һ������k��ʾ
				safearray_inp.GetElement(&k,rxdata +k);
			}
			for (k =0;k <len;k++)//�������ʽ��ΪCString�ͱ���
			{
				strtemp.Format(_T("%02X "), *(rxdata +k));			
				strtemp = strtemp.Right(3);
				strtemp1 += strtemp;			
			}
			strRes[0]=strtemp1;
			strLAdd_HData=strtemp1.Mid(9,2);//�ȵ��ֽڣ��ٸ��ֽ�
			strLAdd_LData=strtemp1.Mid(12,2);
			strHAdd_HData=strtemp1.Mid(15,2);
			strHAdd_LData=strtemp1.Mid(18,2);
			strRes[1]=strHAdd_HData+strHAdd_LData+strLAdd_HData+strLAdd_LData;
			nNum_PPU=StringToMultiBitHex(strRes[1]);
		}
	}		
	if (strRes)
	{
		delete[] strRes;
		strRes=NULL;
	}
	return nNum_PPU;
}
bool CMachineControl::MotorReturnZero(CMscomm1& m_pMscomm,bool bFlagPrMode)
{
	bool IsReturn=false;
	int nResNumPPU=0;	
	double fRound=0;
	nResNumPPU=OnlyReadPPU(m_pMscomm);
	fRound=(double)nResNumPPU/100000.0;
	MotorMove(-fRound,bFlagPrMode,m_pMscomm);
	//nResNumPPU=OnlyReadPPU(m_pMscomm);
	//if (fabs(nResNumPPU)<1000)
	//{
	//	IsReturn=true;
	//}
	return IsReturn;
}
bool CMachineControl::MotorReturnRLimit(CMscomm1& m_pMscomm,bool bFlagPrMode)
{
	bool IsReturn=false;
	int nResNumPPU=0;
	SetSpeed(m_pMscomm,1000);
	MotorMove(-MotorMoveLimit,bFlagPrMode,m_pMscomm);
	
	//Sleep(1000);
	////int n=2;
	////while(n--)
	////{
	////	Sleep(1000);
	////	nResNumPPU=OnlyReadPPU(m_pMscomm);
	////	if (nResNumPPU<NegativeLimit)//˵���Ѿ���������λ����
	////	{
	////		IsReturn=true;
	////	}
	////}	
	IsReturn = true;
	Sleep(2000);
	return IsReturn;
}
int CMachineControl::IsMotorLimit(CMscomm1& m_pMscomm)
{
	int IsPosLimit=0;
	int nResNumPPU=0;	
	nResNumPPU=OnlyReadPPU(m_pMscomm);
	if (nResNumPPU>0)
	{
		if (nResNumPPU>PositiveLimit)
		{
			IsPosLimit=1;//������
		}
	}
	else if (nResNumPPU<0)
	{
		if (nResNumPPU<NegativeLimit)
		{
			IsPosLimit=-1;//������
		}
	}
	return IsPosLimit;
}
int CMachineControl::StringToMultiBitHex(CString str)
{
	int hexdata;	
	int ResData[8]={0};		
	int len = str.GetLength();
	CString cstrTemp=str;
	char strTemp;
	hexdata=0;	
	int i;
	for(i=0;i<len;i++)
	{			
		strTemp=cstrTemp[i];
		if(strTemp == ' ')
		{
			i++;
			continue;
		}	

		if(i>=len)
			break;		
		hexdata= ConvertHexChar(strTemp);
		ResData[i]=hexdata;		
	}
	hexdata=0;
	hexdata=ResData[0]*268435456+ResData[1]*16777216+ResData[2]*1048576+ResData[3]*65536
		+ResData[4]*4096+ResData[5]*256+ResData[6]*16+ResData[7]*1;
	return hexdata;

}

bool CMachineControl::MotorPause(CMscomm1& m_pMscomm)
{
	unsigned char TxData[8];
	TxData[0]=0x01;
	TxData[1]=0x06;
	TxData[2]=0x05;
	TxData[3]=0x0E;
	TxData[4]=0x03;
	TxData[5]=0xE8;
	Transimit(TxData,m_pMscomm);
	Sleep(50);
	return true;
}


bool CMachineControl::MotorStart(CMscomm1& m_pMscomm)
{
	this->MotorMove(0,true,m_pMscomm);
	return true;
}
