// MotorPara.cpp : 实现文件
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "MotorPara.h"
#include "afxdialogex.h"
#include "HighPrecisionDlg.h"
#include "MachineControl.h"
double g_MotorSpeed_Qian=800;//电机转速
double g_MotorSpeed_Hou=400;//电机转速
CString g_MotorBaud=_T("19200");//电机波特率
CString strpath;
extern CMscomm1 m_Mscomm_L;
extern CMscomm1 m_Mscomm_R;
// MotorPara 对话框
CMachineControl m_MachineCtrl_MtPara;
IMPLEMENT_DYNAMIC(MotorPara, CDialogEx)

	MotorPara::MotorPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(MotorPara::IDD, pParent)
	, m_editMotorSpeed_Before(800)

	, m_editMotorSpeed_After(400)
{
	/*m_editMotorSpeed_Before = m_MachineCtrl_MtPara.ReadRegData(0x05,0x7A,m_Mscomm_L);
	m_editMotorSpeed_After = m_MachineCtrl_MtPara.ReadRegData(0x05,0x7A,m_Mscomm_L);
	m_editMotorSpeed_Before/=10;
	m_editMotorSpeed_After/=10;*/
	CStdioFile SpeedInfo;
	CString strLinetemp;
	bool openflag=SpeedInfo.Open(_T("D:\\config\\MotorSpeed.txt"),CFile::modeRead);
	if (openflag)
	{

		SpeedInfo.SeekToBegin();
		SpeedInfo.ReadString(strLinetemp);//读取第一行，读入开始里程
		char *str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
		if(str != NULL)
		{
			char *TopData1 = str;
			g_MotorSpeed_Qian=atof(TopData1);
		}
		SpeedInfo.ReadString(strLinetemp);
		str = strLinetemp.GetBufferSetLength(strLinetemp.GetLength());
		if(str != NULL)
		{
			char *TopData1 = str;
			g_MotorSpeed_Hou=atof(TopData1);
		}
		SpeedInfo.Close();
	}
	
	m_editMotorSpeed_Before=g_MotorSpeed_Qian;
	m_editMotorSpeed_After=g_MotorSpeed_Hou;
}

MotorPara::~MotorPara()
{
}

void MotorPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MOTORSPEED_L, m_editMotorSpeed_Before);	
	DDX_Control(pDX, IDC_COMBO_BAUD_L, m_comboMotorBaud);	
	DDV_MinMaxDouble(pDX,m_editMotorSpeed_Before,0,3000);

	DDX_Text(pDX, IDC_EDIT_MOTORSPEED_HOU, m_editMotorSpeed_After);
}


BEGIN_MESSAGE_MAP(MotorPara, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SETMOTOR_L, &MotorPara::OnBnClickedButtonSetmotorL)
	ON_BN_CLICKED(IDC_BUTTON_MOTORPARA_OK, &MotorPara::OnBnClickedButtonMotorparaOk)
	ON_BN_CLICKED(IDC_BUTTON_MOTORPARA_CANCEL, &MotorPara::OnBnClickedButtonMotorparaCancel)
	ON_BN_CLICKED(IDC_BUTTON_SETMOTOR_BAUD, &MotorPara::OnBnClickedButtonSetmotorBaud)

	ON_BN_CLICKED(IDC_BUTTON_SETMOTOR_HOU, &MotorPara::OnBnClickedButtonSetmotorHou)
END_MESSAGE_MAP()


// MotorPara 消息处理程序


void MotorPara::OnBnClickedButtonSetmotorL()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	bool nResSpeed_L=false;
	bool nResSpeed_R=false;
	g_MotorSpeed_Qian=m_editMotorSpeed_Before;

	nResSpeed_L = m_MachineCtrl_MtPara.SetSpeed(m_Mscomm_L,g_MotorSpeed_Qian);
	nResSpeed_R = m_MachineCtrl_MtPara.SetSpeed(m_Mscomm_R,g_MotorSpeed_Qian);
	if(nResSpeed_L && nResSpeed_R)
	{
		AfxMessageBox(_T("铣磨前速度设置完成"));
	}
	else
	{
		AfxMessageBox(_T("铣磨前速度设置失败，请重试"));
	}
	//UpdateData(false);
}


BOOL MotorPara::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(FALSE);
	m_comboMotorBaud.InsertString(0,_T("19200"));
	m_comboMotorBaud.InsertString(1,_T("115200"));
	m_comboMotorBaud.SetCurSel(0);
	//m_editMotorSpeed_Before = m_MachineCtrl_MtPara.ReadRegData(0x05,0x7A,m_Mscomm_L);
	//m_editMotorSpeed_After = m_MachineCtrl_MtPara.ReadRegData(0x05,0x7A,m_Mscomm_L);
	
	UpdateData(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void MotorPara::OnBnClickedButtonMotorparaOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	g_MotorSpeed_Hou=m_editMotorSpeed_After;
	g_MotorSpeed_Qian=m_editMotorSpeed_Before;
	strpath=_T("D:\\config");
	if (!PathIsDirectory(strpath))
	{
		CreateDirectory(strpath, 0);
	}
	CString str;
	CFile SpeedInfo;	
	CString filename(_T("D:\\config\\MotorSpeed.txt"));//文件保存路径	
	bool openflag=SpeedInfo.Open(filename,CFile::modeCreate|CFile::modeReadWrite);
	if (openflag)
	{
		str.Format(_T("%.2f\r\n"),m_editMotorSpeed_Before);
		SpeedInfo.Write(str,strlen(str));
		str.Format(_T("%.2f\r\n"),m_editMotorSpeed_After);
		SpeedInfo.Write(str,strlen(str));
		SpeedInfo.Close();
	}
	
	//fp2D00DistHdm.Write(strDist,strlen(strDist));	
	CDialogEx::OnOK();
}


void MotorPara::OnBnClickedButtonMotorparaCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void MotorPara::OnBnClickedButtonSetmotorBaud()
{
	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);

	switch(m_comboMotorBaud.GetCurSel())
	{
	case 0:
		{
			g_MotorBaud=_T("19200");
			break;
		}
	case 1:
		{
			g_MotorBaud=_T("115200");
			break;
		}
	}
	m_Mscomm_L.put_Settings(g_MotorBaud+_T(",n,8,2"));//设置波特率
	m_Mscomm_R.put_Settings(g_MotorBaud+_T(",n,8,2"));//设置波特率

	//m_editMotorSpeed_Before=m_MachineCtrl_MtPara.ReadRegData(0x03,0x02,m_Mscomm_L);
	//UpdateData(FALSE);
}


void MotorPara::OnBnClickedButtonSetmotorHou()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	bool nResSpeed_L=false;
	bool nResSpeed_R=false;
	g_MotorSpeed_Hou=m_editMotorSpeed_After;

	nResSpeed_L = m_MachineCtrl_MtPara.SetSpeed(m_Mscomm_L, g_MotorSpeed_Hou);
	nResSpeed_R = m_MachineCtrl_MtPara.SetSpeed(m_Mscomm_R, g_MotorSpeed_Hou);
	if (nResSpeed_L && nResSpeed_R)
	{
		AfxMessageBox(_T("铣磨后速度设置完成"));
	}
	else
	{
		AfxMessageBox(_T("铣磨后速度设置失败，请重试"));
	}
	//UpdateData(FALSE);	

}
