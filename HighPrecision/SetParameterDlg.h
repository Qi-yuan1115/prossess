#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetParameterDlg 对话框

class CSetParameterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetParameterDlg)

public:
	CSetParameterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetParameterDlg();

// 对话框数据
	enum { IDD = IDD_SENSORPARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
