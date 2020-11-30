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
	m_pMscomm.put_Settings(strBaudtemp);	//设置端口	
	m_pMscomm.put_InputMode(1);					//以二进制方式捡取
	m_pMscomm.put_RThreshold(1);				//当缓冲区中有一个以上字符时触发事件
	if (!m_pMscomm.get_PortOpen())//如果串口没有打开则打开
	{
		m_pMscomm.put_PortOpen(TRUE);		
	} 
	if (m_pMscomm.get_PortOpen())
	{

		m_pMscomm.put_InputLen(0);					//读取控件中缓冲区中全部内容
		m_pMscomm.get_Input();						//预读缓冲区，清除残留数据		
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
	//断开串口连接	
	if (m_pMscomm.get_PortOpen())
	{
		if (IsOnlyDisconn)//只断开连接
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
		else//还要回到极限位置
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
	//先设置速度P5-61，若要设置为100rpm，需要向P5-61地址057AH写入100*10=1000
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
	//初始化P306，P407
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

	//然后上电P210置1
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
	
	//P6-02()置0x0001 3382，无INP,无OVLP，INC增量定位,10rpm,完毕则停止
	TxData_32[0]=0x01;//站点号
	TxData_32[1]=0x10;//命令，读写多个寄存器
	TxData_32[2]=0x06;//起始地址高位
	TxData_32[3]=0x04;//起始地址低位
	TxData_32[4]=0x00;//
	TxData_32[5]=0x02;//写两个寄存器
	TxData_32[6]=0x04;//数据字节数
	TxData_32[7]=0x33;
	TxData_32[8]=0x52;//相对定位
	TxData_32[9]=0x00;
	TxData_32[10]=0x01;//0605H写0001H	
	Transimit_32(TxData_32,m_pMscomm);
	Sleep(50);

	TxData_32[0]=0x01;//站点号
	TxData_32[1]=0x10;//命令，读写多个寄存器
	TxData_32[2]=0x06;//起始地址高位
	TxData_32[3]=0x08;//起始地址低位
	TxData_32[4]=0x00;//
	TxData_32[5]=0x02;//写两个寄存器
	TxData_32[6]=0x04;//数据字节数
	TxData_32[7]=0x33;
	TxData_32[8]=0x52;//0608H写3352H
	TxData_32[9]=0x00;
	TxData_32[10]=0x01;//0609H写0001H	
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
	
	int m_NumPPU;//用户单位的个数
	int nH_PPU,nL_PPU;

	m_Round=Round;
	
	//电子齿轮比默认为128:10,且电机分辨率为1,280,000的情况下，每100,000个PPU对应电机运行一圈
	m_NumPPU=(int)(m_Round*100000.0);
	
	nH_PPU=m_NumPPU>>16;
	nL_PPU=m_NumPPU&0x0000FFFF;
	unsigned char TxData_32[13];
	unsigned char TxData[8];
		

	if (bFlagPrMode)
	{
		bFlagPrMode=!bFlagPrMode;
		

		//将m_NumPPU写入P06-03（低16位地址为0606H，高16位地址为0607H）
		TxData_32[0]=0x01;//站点号
		TxData_32[1]=0x10;//命令，读写多个寄存器
		TxData_32[2]=0x06;//起始地址高位
		TxData_32[3]=0x06;//起始地址低位
		TxData_32[4]=0x00;//
		TxData_32[5]=0x02;//写两个寄存器
		TxData_32[6]=0x04;//数据字节数
		TxData_32[7]=nL_PPU>>8;
		TxData_32[8]=nL_PPU&0x00FF;//0604H写0082H
		TxData_32[9]=nH_PPU>>8;
		TxData_32[10]=nH_PPU&0x00FF;//0605H写0001H	
		Transimit_32(TxData_32,m_pMscomm);
		Sleep(50);

		//P5-07(地址050E写入1)
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
		//P6-04置0x0001 3352 （低16位地址为0608H，高16位地址为0609H）
		//P6-05置m_NumPPU，  （低16位地址为060AH，高16位地址为060BH）
			
		//将m_NumPPU写入P06-05（低16位地址为060AH，高16位地址为060BH）
		TxData_32[0]=0x01;//站点号
		TxData_32[1]=0x10;//命令，读写多个寄存器
		TxData_32[2]=0x06;//起始地址高位
		TxData_32[3]=0x0A;//起始地址低位
		TxData_32[4]=0x00;//
		TxData_32[5]=0x02;//写两个寄存器
		TxData_32[6]=0x04;//数据字节数
		TxData_32[7]=nL_PPU>>8;
		TxData_32[8]=nL_PPU&0x00FF;//0604H写0082H
		TxData_32[9]=nH_PPU>>8;
		TxData_32[10]=nH_PPU&0x00FF;//0605H写0001H	
		Transimit_32(TxData_32,m_pMscomm);
		Sleep(50);
		//P5-07(地址050E写入2)表示运行PR2
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
	//计算CRC
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
		array.SetAt(i,TxData[i]);//将TxData数据存入ByteArray型数组
	}
	//发送TxData内的指令
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
		array.SetAt(i,TxData_32[i]);//将TxData数据存入ByteArray型数组
	}
	//发送TxData内的指令
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
	VARIANT variant_inp;//从串口接收来的原始数据就是VARIANT型
	//VARIANT variant_temp;
	COleSafeArray safearray_inp;//
	long len,k;
	byte rxdata[1024];//设置BYTE型数组，byte本质是typedef后的unsigned char（0~255）
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
	variant_inp =m_pMscomm.get_Input();//先将接收缓冲区的数据存入variant_inp
	
	safearray_inp = variant_inp;//变量转换VARIANT到COleSafearray(强制转换)
	len =safearray_inp.GetOneDimSize();//len表示safearray数组的长度
	for (k =0;k<len;k++) //遍历循环
	{
		//将接收到的数据传至byte型数组rxdata中
		//第一个参数k表示
		safearray_inp.GetElement(&k,rxdata +k);
	}
	for (k =0;k <len;k++)//将数组格式化为CString型变量
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
	byte rxdata[1024];//设置BYTE型数组，byte本质是typedef后的unsigned char（0~255）
	CString strtemp,strtemp1,strHData,strLData/*,strFullData*/;
	CString strLAdd_HData,strLAdd_LData;
	CString strHAdd_HData,strHAdd_LData;
	
	//P0-49（0062H）写入2以更新脉冲数
	m_pMscomm.get_Input();//预读缓冲区以清楚残留数据
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
		//读取P0-52(0068H)里的32位内容
		Sleep(50);
		m_pMscomm.get_Input();//预读缓冲区以清楚残留数据
		TxData[0]=0x01;
		TxData[1]=0x03;
		TxData[2]=0x00;
		TxData[3]=0x68;
		TxData[4]=0x00;
		TxData[5]=0x02;//需修改成为读取2个字（即32位）
		Transimit(TxData,m_pMscomm);
		Sleep(50);
		safearrayTemp=m_pMscomm.get_Input();
		SafeArrayLen= safearrayTemp.GetOneDimSize();
		if (SafeArrayLen)
		{			
			safearray_inp = safearrayTemp;//变量转换VARIANT到COleSafearray(强制转换)
			len =safearray_inp.GetOneDimSize();//len表示safearray数组的长度
			for (k =0;k<len;k++) //遍历循环
			{
				//将接收到的数据传至byte型数组rxdata中
				//第一个参数k表示
				safearray_inp.GetElement(&k,rxdata +k);
			}
			for (k =0;k <len;k++)//将数组格式化为CString型变量
			{
				strtemp.Format(_T("%02X "), *(rxdata +k));			
				strtemp = strtemp.Right(3);
				strtemp1 += strtemp;			
			}
			strRes[0]=strtemp1;
			strLAdd_HData=strtemp1.Mid(9,2);//先低字节，再高字节
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
	////	if (nResNumPPU<NegativeLimit)//说明已经到负极限位置了
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
			IsPosLimit=1;//正极限
		}
	}
	else if (nResNumPPU<0)
	{
		if (nResNumPPU<NegativeLimit)
		{
			IsPosLimit=-1;//负极限
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
