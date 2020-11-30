// SetParameterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "SetParameterDlg.h"
#include "afxdialogex.h"
#include "include/ZLDS200_TCP_DLL.H"


//引入外部变量
extern int    g_InitiChooseL;    ///左右轨的排列序号
extern int    g_InitiChooseR;
// CSetParameterDlg 对话框

IMPLEMENT_DYNAMIC(CSetParameterDlg, CDialogEx)

CSetParameterDlg::CSetParameterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetParameterDlg::IDD, pParent)
	
{

}

CSetParameterDlg::~CSetParameterDlg()
{
}

void CSetParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LaserLevel_SLIDER, m_LaserLevel_Slider);
	DDX_Control(pDX, IDC_EXPOSURETIME_SLIDER, m_ExposureTime_Slider);
	//DDX_CBIndex(pDX, IDC_SENSOR_MODE, m_SensorMode);
	DDX_Control(pDX, IDC_LASERLEVER_STATIC, m_Laser_Static);
	DDX_Control(pDX, IDC_EXPOSURETIME_STATIC, m_ExposureTime_Static);
}


BEGIN_MESSAGE_MAP(CSetParameterDlg, CDialogEx)
	ON_WM_HSCROLL()
	
	ON_BN_CLICKED(IDC_LaserLeverBn, &CSetParameterDlg::OnBnClickedLaserleverbn)
	ON_BN_CLICKED(IDC_ExpTimeBn, &CSetParameterDlg::OnBnClickedExptimebn)
	ON_BN_CLICKED(IDOK, &CSetParameterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RestoreSetting_BUTTON, &CSetParameterDlg::OnBnClickedRestoresettingButton)
END_MESSAGE_MAP()


// CSetParameterDlg 消息处理程序


BOOL CSetParameterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);
	//设置滑动条的范围/////
	CString strtemp;
	m_LaserLevel_Slider.SetRange(1,255); 
	m_ExposureTime_Slider.SetRange(1,3600);
	byte paradata[512];
	ZLDS200ReadParams(paradata,g_InitiChooseL);
	m_laserlever   = paradata[2];
	m_ExposureTime = paradata[4]*256+paradata[3];

	m_LaserLevel_Slider.SetPos(m_laserlever);
	strtemp.Format("Laser Level:%d",m_laserlever);
	m_Laser_Static.SetWindowText(strtemp);
	m_ExposureTime_Slider.SetPos(m_ExposureTime);
	strtemp.Format("Laser Level:%d",m_ExposureTime);
	m_ExposureTime_Static.SetWindowText(strtemp);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetParameterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl *pLaserLeverSliderCtrl=(CSliderCtrl *)GetDlgItem(IDC_LaserLevel_SLIDER);
	CSliderCtrl *pExposureTimeSliderCtrl=(CSliderCtrl *)GetDlgItem(IDC_EXPOSURETIME_SLIDER);
	CString strtemp="";

	if (pScrollBar->m_hWnd==pLaserLeverSliderCtrl->m_hWnd)
	{
		m_laserlever=pLaserLeverSliderCtrl->GetPos(); 
		strtemp.Format("Laser Level:%d",m_laserlever);
		m_Laser_Static.SetWindowText(strtemp);
	}

	if (pScrollBar->m_hWnd==pExposureTimeSliderCtrl->m_hWnd)
	{
		m_ExposureTime=pExposureTimeSliderCtrl->GetPos(); 
		strtemp.Format("Exposure Time:%d",m_ExposureTime);
		m_ExposureTime_Static.SetWindowText(strtemp);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}







void CSetParameterDlg::OnBnClickedLaserleverbn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	byte paradata[512];
	ZLDS200ReadParams(paradata,g_InitiChooseL);
	paradata[2]=m_laserlever;
	ZLDS200WriteParams(paradata,g_InitiChooseL);
	ZLDS200ReadParams(paradata,g_InitiChooseR);
	paradata[2]=m_laserlever;
	ZLDS200WriteParams(paradata,g_InitiChooseR);
	UpdateData(false);

}


void CSetParameterDlg::OnBnClickedExptimebn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	byte paradata[512];
	ZLDS200ReadParams(paradata,g_InitiChooseL);
	paradata[4]=m_ExposureTime/256;
	paradata[3]=m_ExposureTime%256;
	ZLDS200WriteParams(paradata,g_InitiChooseL);
	ZLDS200ReadParams(paradata,g_InitiChooseR);
	paradata[4]=m_ExposureTime/256;
	paradata[3]=m_ExposureTime%256;
	ZLDS200WriteParams(paradata,g_InitiChooseR);
	UpdateData(FALSE);
}


void CSetParameterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	byte paradata[512];
	ZLDS200ReadParams(paradata,g_InitiChooseL);
	paradata[2]=m_laserlever;	
	paradata[3]=m_ExposureTime%256;
	paradata[4]=m_ExposureTime/256;
	ZLDS200WriteParams(paradata,g_InitiChooseL);
	//右侧
	ZLDS200ReadParams(paradata,g_InitiChooseR);
	paradata[2]=m_laserlever;
	paradata[3]=m_ExposureTime%256;
	paradata[4]=m_ExposureTime/256;	
	ZLDS200WriteParams(paradata,g_InitiChooseR);
	UpdateData(FALSE);
	CDialogEx::OnOK();
}


void CSetParameterDlg::OnBnClickedRestoresettingButton()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL nRes=MessageBox(_T("是否确定恢复出厂设置"),_T("恢复出厂设置"),MB_OKCANCEL|MB_ICONQUESTION);
	if(IDOK==nRes)
	{
		
		//if(ZLDS200FlushParams(false,g_InitiChooseL)&&ZLDS200FlushParams(false,g_InitiChooseR))
		//	AfxMessageBox(_T("恢复出厂设置成功"));
		//else
		//	AfxMessageBox(_T("恢复出厂设置失败"));
	}
}
