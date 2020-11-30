#pragma once



struct TestInfo
{
	int          TrackSel;      //轨形选择
	int          XM_QianHou;    //铣磨前后	
	double       DistanceStart; //作业起点
	CString      Xianbie;       //测试线别
	CString      Direction;     //作业方向
	CString      XMH_BaseFile[30];  //铣磨后测量的基准文件名
	int          XMH_BaseFileNum;
	bool         TestInfoYES_NO;//作业信息是否输入完成，true表示可以开始检测

};
// CTestInfoInputDlg 对话框

class CTestInfoInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTestInfoInputDlg)

public:
	CTestInfoInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTestInfoInputDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TESTINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
