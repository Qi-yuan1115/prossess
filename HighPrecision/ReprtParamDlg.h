#pragma once


// CReprtParamDlg �Ի���

class CReprtParamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReprtParamDlg)

public:
	CReprtParamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReprtParamDlg();

// �Ի�������
	enum { IDD = IDD_REPORT_PARAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_posVal;
	CString m_negVal;
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancle();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonFile();
};
