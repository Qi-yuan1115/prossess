// ConnectDeviceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "ConnectDeviceDlg.h"
#include "afxdialogex.h"
#include "include/ZLDS200_TCP_DLL.H"
#include "HighPrecisionDlg.h"


//#define  PortNum_L	4       //��������
//#define  PortNum_R  6		//�ҵ������

#define  PortNum_L	4      //��������
#define  PortNum_R  3		//�ҵ������

// CConnectDeviceDlg �Ի���
int IsPowerON_L=-1;
int IsPowerON_R=-1;

///ȫ�ֱ�������������
int g_InitiChooseL=0;    ///���ҹ���������
int g_InitiChooseR=1;

bool g_bFlagSensorL=false;//���Ҵ��������ӳɹ��ı�־
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
	   SetDlgItemText(IDC_STATIC_SENSORL4,_T("   ����"));
	else
	   SetDlgItemText(IDC_STATIC_SENSORL4,_T("   �����"));
	if(g_bFlagSensorR)
	   SetDlgItemText(IDC_STATIC_SENSORR4,_T("   ����"));
	else
	   SetDlgItemText(IDC_STATIC_SENSORR4,_T("   �����"));
	if(g_bFlagMotor_L)
	   SetDlgItemText(IDC_MOTORON_L,_T("   �ϵ�ɹ�"));
	else
	   SetDlgItemText(IDC_MOTORON_L,_T("   ���ϵ�"));
	if(g_bFlagMotor_R)
	   SetDlgItemText(IDC_MOTORON_R,_T("   �ϵ�ɹ�"));
	else
	   SetDlgItemText(IDC_MOTORON_R,_T("   ���ϵ�"));
	if(g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L&&g_bFlagMotor_R*/)
		SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("�Ͽ��豸"));
	else
		SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("�����豸"));

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//bFlag_Keydown = FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
// CConnectDeviceDlg ��Ϣ�������


void CConnectDeviceDlg::OnBnClickedButtonLinkdevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int device_num = 0;
	int MachineLink = 0;
	int ComNumber =0;
	int devicetype = 65535;//����������//
	int sn[255]={0};
	
	COleSafeArray safearray_L;
	COleSafeArray safearray_R;
	////����2D������������Ƿ�����
	/*g_bFlagSensorL=1;g_bFlagSensorR=1;*/
	if(!g_bFlagSensorL/*||!g_bFlagSensorR||!g_bFlagMotor_L||!g_bFlagMotor_R*/)//������������
	{	
		g_bFlagMotor_L = 1;
		//g_bFlagMotor_R = 1;
		/*********************���*******************/
		if (!g_bFlagMotor_L/*||!g_bFlagMotor_R*/)//û����ȷ����
	/*	if(FALSE)*/
		{
			//�ȶϿ��豸			
			m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_L,true,true);
			/*m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_R,true,true);*/
			//�����Ӵ���
			bIsConnectedL=m_MachineCtrl_ConnectDev.ConnectMotor(PortNum_L,_T("19200"),m_Mscomm_L);
			/*bIsConnectedR=m_MachineCtrl_ConnectDev.ConnectMotor(PortNum_R,_T("19200"),m_Mscomm_R);*/
			//���������Ͼͼ����ϵ�
			if (bIsConnectedL/*&&bIsConnectedR*/)
			{
				//������ϵ�
				IsPowerON_L=0;
				IsPowerON_R=0;

				m_Mscomm_L.get_Input();				
				m_MachineCtrl_ConnectDev.MotorPowerON(m_Mscomm_L);//������ϵ�
				Sleep(10);
				safearray_L=m_Mscomm_L.get_Input();
				DWORD SafeArrayLen_L= safearray_L.GetOneDimSize();
				
				if(SafeArrayLen_L)
				{
					g_bFlagMotor_L=true;
					SetDlgItemText(IDC_MOTORON_L,_T("�ϵ�ɹ�"));				
				}	
				else
				{
					g_bFlagMotor_L=false;
					IsPowerON_L=-1;
					SetDlgItemText(IDC_MOTORON_L,_T("�ϵ�ʧ��"));
				}
				//�Ҳ����ϵ�
			//	m_Mscomm_R.get_Input();
			//	m_MachineCtrl_ConnectDev.MotorPowerON(m_Mscomm_R);//�Ҳ����ϵ�
			//	Sleep(10);
			//	safearray_R=m_Mscomm_R.get_Input();
			//	DWORD SafeArrayLen_R= safearray_R.GetOneDimSize();
			//	if (SafeArrayLen_R)
			//	{
			//		g_bFlagMotor_R=true;
			//		SetDlgItemText(IDC_MOTORON_R,_T("�ϵ�ɹ�"));					
			//	} 
			//	else
			//	{
			//		g_bFlagMotor_R=false;
			//		IsPowerON_R=-1;
			//		SetDlgItemText(IDC_MOTORON_R,_T("�ϵ�ʧ��"));
			//	}
				if (/*g_bFlagMotor_R&&*/g_bFlagMotor_L)//�������������������˲��õ������
				{
					m_MachineCtrl_ConnectDev.SetSpeed(m_Mscomm_L,30);
				/*	m_MachineCtrl_ConnectDev.SetSpeed(m_Mscomm_R,1000);*/
					m_MachineCtrl_ConnectDev.MotorReturnZero(m_Mscomm_L,bFlagPOrder_L);
				/*	m_MachineCtrl_ConnectDev.MotorReturnZero(m_Mscomm_R,bFlagPOrder_R);*/
				}
			}
			else//����û����
			{
				SetDlgItemText(IDC_MOTORON_L,_T("�����쳣"));
				g_bFlagMotor_L=false;
				SetDlgItemText(IDC_MOTORON_R,_T("�����쳣"));
				g_bFlagMotor_R=false;
			}
		}
		else//�Ѿ���ȷ����
		{
			g_bFlagMotor_L=true;
			g_bFlagMotor_R=true;
			SetDlgItemText(IDC_MOTORON_R,_T("�ϵ�ɹ�"));
			SetDlgItemText(IDC_MOTORON_L,_T("�ϵ�ɹ�"));			
		}				
		/************************������**************/
		if (!g_bFlagSensorL/*||!g_bFlagSensorR*/)
		{
			ZLDS200DisConnectAll();
			//��ʼ���Ӵ�����
			SetDlgItemText(IDC_STATIC_SENSORL4,_T("   ������..."));
			//SetDlgItemText(IDC_STATIC_SENSORR4,_T("   ������..."));	
			if( ( device_num =  ZLDS200ConnectAll(devicetype,sn) )<=0 )
			{				
				SetDlgItemText(IDC_STATIC_SENSORL4,_T("   �쳣"));
				//SetDlgItemText(IDC_STATIC_SENSORR4,_T("   �쳣"));	
				g_bFlagSensorL =FALSE;
				g_bFlagSensorR = FALSE;
			}
			else
			{

				if(sn[0]==DeviceNum_L)
				{ 
					g_InitiChooseL = 0;
					SetDlgItemText(IDC_STATIC_SENSORL4,_T("   ����"));
					g_bFlagSensorL = TRUE;
					/*if(sn[1]==DeviceNum_R)
					{
						g_InitiChooseR = 1;
						SetDlgItemText(IDC_STATIC_SENSORR4,_T("   ����"));
						g_bFlagSensorR = TRUE;
					}
					else
					{
						g_InitiChooseR = 1;
						SetDlgItemText(IDC_STATIC_SENSORR4,_T("   �쳣"));
						g_bFlagSensorR = FALSE;
					}*/
				}
				/*if(sn[0]==DeviceNum_R)
				{
					g_InitiChooseR = 0;
					SetDlgItemText(IDC_STATIC_SENSORR4,_T("   ����"));
					g_bFlagSensorR = TRUE;
					if(sn[1]==DeviceNum_L)
					{
						g_InitiChooseL = 1;
						SetDlgItemText(IDC_STATIC_SENSORL4,_T("   ����"));
						g_bFlagSensorL = TRUE;
					}
					else
					{
						g_InitiChooseL = 1;
						SetDlgItemText(IDC_STATIC_SENSORL4,_T("   �쳣"));
						g_bFlagSensorL = FALSE;
					}
				}	*/		
			}
		}				
		if(g_bFlagSensorL/*&&g_bFlagSensorR&&g_bFlagMotor_L*//*&&g_bFlagMotor_R*/)
		{
			SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("�Ͽ�����"));
		}
	}
	else //����������,�������
	{
		ZLDS200DisConnectAll();//�Ͽ����д���������
		
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





		//m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_L,true,false);//�Ͽ��������
		//m_MachineCtrl_ConnectDev.DisConnectMotor(m_Mscomm_R,true,false);
		SetDlgItemText(IDC_STATIC_SENSORL4,_T("�����"));
		SetDlgItemText(IDC_STATIC_SENSORR4,_T("�����"));
		SetDlgItemText(IDC_MOTORON_L,_T("���ϵ�"));
		SetDlgItemText(IDC_MOTORON_R,_T("���ϵ�"));
		SetDlgItemText(IDC_BUTTON_LINKDEVICE,_T("�����豸"));
		g_bFlagSensorL=false;
		g_bFlagSensorR=false;
		g_bFlagMotor_L=false;
		g_bFlagMotor_R=false;
	}
}


BOOL CConnectDeviceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CConnectDeviceDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}
