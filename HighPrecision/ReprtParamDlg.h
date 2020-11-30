#pragma once


// CReprtParamDlg 对话框

class CReprtParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReprtParamDlg)

public:
	CReprtParamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReprtParamDlg();

// 对话框数据
	enum { IDD = IDD_REPORT_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_posVal;
	CString m_negVal;
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFile();
};
