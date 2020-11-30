#pragma once



struct TestInfo
{
	int          TrackSel;      //����ѡ��
	int          XM_QianHou;    //ϳĥǰ��	
	double       DistanceStart; //��ҵ���
	CString      Xianbie;       //�����߱�
	CString      Direction;     //��ҵ����
	CString      XMH_BaseFile[30];  //ϳĥ������Ļ�׼�ļ���
	int          XMH_BaseFileNum;
	bool         TestInfoYES_NO;//��ҵ��Ϣ�Ƿ�������ɣ�true��ʾ���Կ�ʼ���

};
// CTestInfoInputDlg �Ի���

class CTestInfoInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestInfoInputDlg)

public:
	CTestInfoInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestInfoInputDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_TESTINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnCbnSelchangeInputinfoTracksel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:
	CStdioFile fStandardFile;
	int m_TrackSel;
	
public:
	int m_XmQianHou;
	CString m_TestXianBie;
	int m_Direction;
	CString m_TestBegin_First;
	CString m_TestBegin_Mid;
	CString m_TestBegin_Last;
	afx_msg void OnEnChangeEditInputinfoStart1();
	afx_msg void OnEnChangeEditInputinfoStart2();
	
	afx_msg void OnEnChangeEditInputinfoStart3();
	afx_msg void OnBnClickedRadioXimohou();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadioInputinfoUp();
	afx_msg void OnBnClickedRadioInputinfoDown();
};
