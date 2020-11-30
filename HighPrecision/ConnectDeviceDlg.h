#pragma once
#define DeviceNum_L 19114
#define DeviceNum_R 206201
#include "MachineControl.h"
#include "mscomm1.h"
// CConnectDeviceDlg �Ի���

class CConnectDeviceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConnectDeviceDlg)

public:
	CConnectDeviceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConnectDeviceDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	
	DECLARE_MESSAGE_MAP()

	//������Ӻ�������
private:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
private:
	//bool bFlag_Keydown;
public:
	afx_msg void OnBnClickedButtonLinkdevice();	
	afx_msg void OnStnClickedStaticSensorl();
	afx_msg void OnStnClickedMotoronL();
	afx_msg void OnBnClickedOk();
};
