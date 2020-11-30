#pragma once


// CBomo_TestDlg 对话框

class CBomo_TestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBomo_TestDlg)

public:
	CBomo_TestDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBomo_TestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOMO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
