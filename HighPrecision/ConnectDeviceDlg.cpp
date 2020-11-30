// ConnectDeviceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "ConnectDeviceDlg.h"
#include "afxdialogex.h"
#include "include/ZLDS200_TCP_DLL.H"
#include "HighPrecisionDlg.h"


//#define  PortNum_L	4       //左电机串口
//#define  PortNum_R  6		//右电机串口

#define  PortNum_L	4      //左电机串口
#define  PortNum_R  3		//右电机串口

// CConnectDeviceDlg 对话框
int IsPowerON_L=-1;
int IsPowerON_R=-1;

///全局变量的声明定义
int g_InitiChooseL=0;    ///左右轨的排列序号
int g_InitiChooseR=1;

bool g_bFlagSensorL=false;//左右传感器连接成功的标志
bool g_bFlagSensorR=false;

bool g_bFlagMotor_L=false;
bool g_bFlagMotor_R=false;

bool bIsConnectedL=false;
bool bIsConnectedR=false;

CMachineControl m_MachineCtrl_ConnectDev;
extern CMscomm1 m_Mscomm_L;
extern CMscomm1 m_Mscomm_R;
extern bool bFlagPOrder_R;
extern bool bFlagPOrder_L;
/*extern CMscomm1 m_Mscomm_R;*/

IMPLEMENT_DYNAMIC(CConnectDeviceDlg, CDialogEx)

CConnectDeviceDlg::CConnectDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConnectDeviceDlg::IDD, pParent)
{

}

CConnectDeviceDlg::~CConnectDeviceDlg()
{
}

void CConnectDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CConnectDeviceDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LINKDEVICE, &CConnectDeviceDlg::OnBnClickedButtonLinkdevice)

	ON_STN_CLICKED(IDC_MOTORON_L, &CConnectDeviceDlg::OnStnClickedMotoronL)
	ON_BN_CLICKED(IDOK, &CConnectDeviceDlg::OnBnClickedOk)
END_MESSAGE_MAP()




BOOL CConnectDeviceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(TRUE);
	if(g_bFlagSensorL)
	   SetDlgItemText(IDC_STATIC_SENSORL4,_T("   正常"));
	else
	   SetDlgItemText(IDC_STATIC_SENSORL4,_T("   待检测"));
	if(g_bFlagSensorR)
	   SetDlgItemText(IDC_STATIC_SENSORR4,_T("   正常"));
	else
	   SetDlgItemText(IDC_STATIC_SENSORR4,_T("   待检测"));
	if(g_bFlagMotor_L)
	   SetDlgItemText(IDC_MOTORON_L,_T("   上电成功"));
	else
	   SetDlgItemText(IDC_MOTORON_L,_T("   待上电"));
	if(g_bFlagMotor_R)
	   SetDlgItemText(IDC_MOTORON_R,_T("   上电成功"));
	else
	   SetDlgItemText(IDC_MOTORON_R,_T("   待上电"));
	if(g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L&&g_bFlagMotor_R*/)
		SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("断开设备"));
	else
		SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("连接设备"));

	// TODO:  在此添加额外的初始化
	//bFlag_Keydown = FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
// CConnectDeviceDlg 消息处理程序


void CConnectDeviceDlg::OnBnClickedButtonLinkdevice()
{
	// TODO: 在此添加控件通知处理程序代码

	int device_num = 0;
	int MachineLink = 0;
	int ComNumber =0;
	int devicetype = 65535;//传感器类型//
	int sn[255]={0};
	
	COleSafeArray safearray_L;
	COleSafeArray safearray_R;
	////连接2D传感器。检测是否正常
	/*g_bFlagSensorL=1;g_bFlagSensorR=1;*/
	if(!g_bFlagSensorL/*||!g_bFlagSensorR||!g_bFlagMotor_L||!g_bFlagMotor_R*/)//不正常，重连
	{	
		g_bFlagMotor_L = 1;
		//g_bFlagMotor_R = 1;
		/*********************电机*******************/
		if (!g_bFlagMotor_L/*||!g_bFlagMotor_R*/)//没有正确连接
	/*	if(FALSE)*/
		{
			//先断开设备			
			m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_L,true,true);
			/*m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_R,true,true);*/
			//先连接串口
			bIsConnectedL=m_MachineCtrl_ConnectDev.ConnectMotor(PortNum_L,_T("19200"),m_Mscomm_L);
			/*bIsConnectedR=m_MachineCtrl_ConnectDev.ConnectMotor(PortNum_R,_T("19200"),m_Mscomm_R);*/
			//串口连接上就继续上电
			if (bIsConnectedL/*&&bIsConnectedR*/)
			{
				//左侧电机上电
				IsPowerON_L=0;
				IsPowerON_R=0;

				m_Mscomm_L.get_Input();				
				m_MachineCtrl_ConnectDev.MotorPowerON(m_Mscomm_L);//左侧电机上电
				Sleep(10);
				safearray_L=m_Mscomm_L.get_Input();
				DWORD SafeArrayLen_L= safearray_L.GetOneDimSize();
				
				if(SafeArrayLen_L)
				{
					g_bFlagMotor_L=true;
					SetDlgItemText(IDC_MOTORON_L,_T("上电成功"));				
				}	
				else
				{
					g_bFlagMotor_L=false;
					IsPowerON_L=-1;
					SetDlgItemText(IDC_MOTORON_L,_T("上电失败"));
				}
				//右侧电机上电
			//	m_Mscomm_R.get_Input();
			//	m_MachineCtrl_ConnectDev.MotorPowerON(m_Mscomm_R);//右侧电机上电
			//	Sleep(10);
			//	safearray_R=m_Mscomm_R.get_Input();
			//	DWORD SafeArrayLen_R= safearray_R.GetOneDimSize();
			//	if (SafeArrayLen_R)
			//	{
			//		g_bFlagMotor_R=true;
			//		SetDlgItemText(IDC_MOTORON_R,_T("上电成功"));					
			//	} 
			//	else
			//	{
			//		g_bFlagMotor_R=false;
			//		IsPowerON_R=-1;
			//		SetDlgItemText(IDC_MOTORON_R,_T("上电失败"));
			//	}
				if (/*g_bFlagMotor_R&&*/g_bFlagMotor_L)//如果两个电机都连接上了才让电机归零
				{
					m_MachineCtrl_ConnectDev.SetSpeed(m_Mscomm_L,30);
				/*	m_MachineCtrl_ConnectDev.SetSpeed(m_Mscomm_R,1000);*/
					m_MachineCtrl_ConnectDev.MotorReturnZero(m_Mscomm_L,bFlagPOrder_L);
				/*	m_MachineCtrl_ConnectDev.MotorReturnZero(m_Mscomm_R,bFlagPOrder_R);*/
				}
			}
			else//串口没连上
			{
				SetDlgItemText(IDC_MOTORON_L,_T("串口异常"));
				g_bFlagMotor_L=false;
				SetDlgItemText(IDC_MOTORON_R,_T("串口异常"));
				g_bFlagMotor_R=false;
			}
		}
		else//已经正确连接
		{
			g_bFlagMotor_L=true;
			g_bFlagMotor_R=true;
			SetDlgItemText(IDC_MOTORON_R,_T("上电成功"));
			SetDlgItemText(IDC_MOTORON_L,_T("上电成功"));			
		}				
		/************************传感器**************/
		if (!g_bFlagSensorL/*||!g_bFlagSensorR*/)
		{
			ZLDS200DisConnectAll();
			//开始连接传感器
			SetDlgItemText(IDC_STATIC_SENSORL4,_T("   连接中..."));
			//SetDlgItemText(IDC_STATIC_SENSORR4,_T("   连接中..."));	
			if( ( device_num =  ZLDS200ConnectAll(devicetype,sn) )<=0 )
			{				
				SetDlgItemText(IDC_STATIC_SENSORL4,_T("   异常"));
				//SetDlgItemText(IDC_STATIC_SENSORR4,_T("   异常"));	
				g_bFlagSensorL =FALSE;
				g_bFlagSensorR = FALSE;
			}
			else
			{

				if(sn[0]==DeviceNum_L)
				{ 
					g_InitiChooseL = 0;
					SetDlgItemText(IDC_STATIC_SENSORL4,_T("   正常"));
					g_bFlagSensorL = TRUE;
					/*if(sn[1]==DeviceNum_R)
					{
						g_InitiChooseR = 1;
						SetDlgItemText(IDC_STATIC_SENSORR4,_T("   正常"));
						g_bFlagSensorR = TRUE;
					}
					else
					{
						g_InitiChooseR = 1;
						SetDlgItemText(IDC_STATIC_SENSORR4,_T("   异常"));
						g_bFlagSensorR = FALSE;
					}*/
				}
				/*if(sn[0]==DeviceNum_R)
				{
					g_InitiChooseR = 0;
					SetDlgItemText(IDC_STATIC_SENSORR4,_T("   正常"));
					g_bFlagSensorR = TRUE;
					if(sn[1]==DeviceNum_L)
					{
						g_InitiChooseL = 1;
						SetDlgItemText(IDC_STATIC_SENSORL4,_T("   正常"));
						g_bFlagSensorL = TRUE;
					}
					else
					{
						g_InitiChooseL = 1;
						SetDlgItemText(IDC_STATIC_SENSORL4,_T("   异常"));
						g_bFlagSensorL = FALSE;
					}
				}	*/		
			}
		}				
		if(g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L*//*&&g_bFlagMotor_R*/)
		{
			SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("断开连接"));
		}
	}
	else //传感器正常,电机正常
	{
		ZLDS200DisConnectAll();//断开所有传感器连接
		
		/*if (g_bFlagMotor_L)
		{
			m_MachineCtrl_ConnectDev.SetSpeed(m_Mscomm_L,30);
			m_MachineCtrl_ConnectDev.MotorMove(-MotorMoveLmt,bFlagPOrder_L,m_Mscomm_L);
		}
		if (g_bFlagMotor_R)
		{
			m_MachineCtrl_ConnectDev.SetSpeed(m_Mscomm_R,1500);
			m_MachineCtrl_ConnectDev.MotorMove(-MotorMoveLmt,bFlagPOrder_R,m_Mscomm_R);
		}
		if (g_bFlagMotor_L||g_bFlagMotor_R)
		{
			Sleep(2000);
		}
		if (g_bFlagMotor_L)
		{
			g_bFlagMotor_L = m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_L,bFlagPOrder_L,false);
		}
		if (g_bFlagMotor_R)
		{
			g_bFlagMotor_R = m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_R,bFlagPOrder_R,false);
		}
*/





		//m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_L,true,false);//断开电机连接
		//m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_R,true,false);
		SetDlgItemText(IDC_STATIC_SENSORL4,_T("待检测"));
		SetDlgItemText(IDC_STATIC_SENSORR4,_T("待检测"));
		SetDlgItemText(IDC_MOTORON_L,_T("待上电"));
		SetDlgItemText(IDC_MOTORON_R,_T("待上电"));
		SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("连接设备"));
		g_bFlagSensorL=false;
		g_bFlagSensorR=false;
		g_bFlagMotor_L=false;
		g_bFlagMotor_R=false;
	}
}


BOOL CConnectDeviceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
 //  if(bFlag_Keydown)
 //  {
	//if(pMsg->message==WM_LBUTTONDOWN)
	//	return TRUE;
	//if(pMsg->message==WM_RBUTTONDOWN)
	//	return TRUE;
 //  }
	return CDialogEx::PreTranslateMessage(pMsg);
}







void CConnectDeviceDlg::OnStnClickedMotoronL()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CConnectDeviceDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
