// SetParameterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "SetParameterDlg.h"
#include "afxdialogex.h"
#include "include/ZLDS200_TCP_DLL.H"


//�����ⲿ����
extern int    g_InitiChooseL;    ///���ҹ���������
extern int    g_InitiChooseR;
// CSetParameterDlg �Ի���

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


// CSetParameterDlg ��Ϣ�������


BOOL CSetParameterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(TRUE);
	//���û������ķ�Χ/////
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSetParameterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	byte paradata[512];
	ZLDS200ReadParams(paradata,g_InitiChooseL);
	paradata[2]=m_laserlever;	
	paradata[3]=m_ExposureTime%256;
	paradata[4]=m_ExposureTime/256;
	ZLDS200WriteParams(paradata,g_InitiChooseL);
	//�Ҳ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL nRes=MessageBox(_T("�Ƿ�ȷ���ָ���������"),_T("�ָ���������"),MB_OKCANCEL|MB_ICONQUESTION);
	if(IDOK==nRes)
	{
		
		//if(ZLDS200FlushParams(false,g_InitiChooseL)&&ZLDS200FlushParams(false,g_InitiChooseR))
		//	AfxMessageBox(_T("�ָ��������óɹ�"));
		//else
		//	AfxMessageBox(_T("�ָ���������ʧ��"));
	}
}
