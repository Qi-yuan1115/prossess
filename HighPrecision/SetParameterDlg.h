#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetParameterDlg �Ի���

class CSetParameterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetParameterDlg)

public:
	CSetParameterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetParameterDlg();

// �Ի�������
	enum { IDD = IDD_SENSORPARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_LaserLevel_Slider;
	CSliderCtrl m_ExposureTime_Slider;
	
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
	int m_ExposureTime;
	int m_laserlever;
public:
	CStatic m_Laser_Static;
	CStatic m_ExposureTime_Static;
	afx_msg void OnBnClickedLaserleverbn();
	afx_msg void OnBnClickedExptimebn();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRestoresettingButton();
};
