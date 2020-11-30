#pragma once
#define DeviceNum_L 19114
#define DeviceNum_R 206201
#include "MachineControl.h"
#include "mscomm1.h"
// CConnectDeviceDlg 对话框

class CConnectDeviceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConnectDeviceDlg)

public:
	CConnectDeviceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConnectDeviceDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	
	DECLARE_MESSAGE_MAP()

	//以下添加函数声明
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
