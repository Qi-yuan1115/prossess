#pragma once
#include "afxwin.h"


// MotorPara �Ի���

class MotorPara : public CDialogEx
{
	DECLARE_DYNAMIC(MotorPara)

public:
	MotorPara(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MotorPara();

	// �Ի�������
	enum { IDD = IDD_DIALOG_MOTORPARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_editMotorSpeed_Before;

	CComboBox m_comboMotorBaud;

	afx_msg void OnBnClickedButtonSetmotorL();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMotorparaOk();
	afx_msg void OnBnClickedButtonMotorparaCancel();
	afx_msg void OnBnClickedButtonSetmotorBaud();
	//afx_msg void OnBnClickedRadioSetmtparaRadioHou();
	//afx_msg void OnBnClickedRadioSetmtparaRadio();
	double m_editMotorSpeed_After;
	afx_msg void OnBnClickedButtonSetmotorHou();
};
