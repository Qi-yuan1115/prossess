#pragma once


// CBomo_TestDlg �Ի���

class CBomo_TestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBomo_TestDlg)

public:
	CBomo_TestDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBomo_TestDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOMO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
