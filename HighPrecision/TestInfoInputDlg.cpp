// TestInfoInputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "TestInfoInputDlg.h"
#include "afxdialogex.h"
#include "string"
using namespace std;



TestInfo     g_TestInfo_L={1,0,0.0,_T("k"),_T("顺"),_T(""),0,false};     //左轨作业信息
TestInfo     g_TestInfo_R={1,0,0.0,_T("k"),_T("顺"),_T(""),0,false};     //右轨作业信息
double       Encoder_Distance = 0.1;			//采集的里程单位


// CTestInfoInputDlg 对话框

IMPLEMENT_DYNAMIC(CTestInfoInputDlg, CDialogEx)

CTestInfoInputDlg::CTestInfoInputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestInfoInputDlg::IDD, pParent)
	, m_TrackSel(1)
	, m_XmQianHou(0)
	, m_TestXianBie(_T("K"))
	, m_Direction(0)
	, m_TestBegin_First(_T("0"))
	, m_TestBegin_Last(_T("0"))
	, m_TestBegin_Mid(_T("0"))
{

}

CTestInfoInputDlg::~CTestInfoInputDlg()
{
}

void CTestInfoInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_INPUTINFO_TRACKSEL, m_TrackSel);
	DDX_Radio(pDX, IDC_RADIO_XIMOQIAN, m_XmQianHou);
	DDX_Text(pDX, IDC_EDIT_INPUTINFO_XIANBIE, m_TestXianBie);
	DDX_Radio(pDX, IDC_RADIO_INPUTINFO_UP, m_Direction);
	DDX_Text(pDX, IDC_EDIT_INPUTINFO_START1, m_TestBegin_First);
	DDX_Text(pDX, IDC_EDIT_INPUTINFO_START2, m_TestBegin_Last);
	DDX_Text(pDX, IDC_EDIT_INPUTINFO_START3, m_TestBegin_Mid);
}


BEGIN_MESSAGE_MAP(CTestInfoInputDlg, CDialogEx)
	//ON_CBN_SELCHANGE(IDC_INPUTINFO_TRACKSEL, &CTestInfoInputDlg::OnCbnSelchangeInputinfoTracksel)
	ON_BN_CLICKED(IDOK, &CTestInfoInputDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_INPUTINFO_START1, &CTestInfoInputDlg::OnEnChangeEditInputinfoStart1)
	ON_EN_CHANGE(IDC_EDIT_INPUTINFO_START2, &CTestInfoInputDlg::OnEnChangeEditInputinfoStart2)
	ON_EN_CHANGE(IDC_EDIT_INPUTINFO_START3, &CTestInfoInputDlg::OnEnChangeEditInputinfoStart3)
	ON_BN_CLICKED(IDC_RADIO_XIMOHOU, &CTestInfoInputDlg::OnBnClickedRadioXimohou)
	ON_BN_CLICKED(IDCANCEL, &CTestInfoInputDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_INPUTINFO_UP, &CTestInfoInputDlg::OnBnClickedRadioInputinfoUp)
	ON_BN_CLICKED(IDC_RADIO_INPUTINFO_DOWN, &CTestInfoInputDlg::OnBnClickedRadioInputinfoDown)
END_MESSAGE_MAP()


// CTestInfoInputDlg 消息处理程序

BOOL CTestInfoInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);
	m_TrackSel = 1;//默认60轨

	UpdateData(FALSE);
	Encoder_Distance = 0.1;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE

}

void CTestInfoInputDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	g_TestInfo_L.TrackSel        = m_TrackSel;
	g_TestInfo_L.XM_QianHou      = m_XmQianHou;
	g_TestInfo_L.Xianbie         = m_TestXianBie;
	g_TestInfo_L.DistanceStart   = atoi(m_TestBegin_First)*1000+atoi(m_TestBegin_Mid)+atoi(m_TestBegin_Last)*0.1;
	g_TestInfo_L.Direction       = (m_Direction==0)?_T("下"):_T("上");

	g_TestInfo_R.TrackSel        = m_TrackSel;
	g_TestInfo_R.XM_QianHou      = m_XmQianHou;
	g_TestInfo_R.Xianbie         = m_TestXianBie;
	g_TestInfo_R.DistanceStart   = atoi(m_TestBegin_First)*1000+atoi(m_TestBegin_Mid)+atoi(m_TestBegin_Last)*0.1;
	g_TestInfo_R.Direction       = (m_Direction==0)?_T("下"):_T("上");

	if(0==m_XmQianHou)//铣磨前
		g_TestInfo_L.TestInfoYES_NO = true;//铣磨前直接就可以开始检测
	/////自动识别上下行//////
	if (1==m_XmQianHou)
	{
		GetDlgItem(IDC_RADIO_INPUTINFO_DOWN)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO_INPUTINFO_UP)->EnableWindow(TRUE);
	}
	CDialogEx::OnOK();
	UpdateData(FALSE);
}


void CTestInfoInputDlg::OnEnChangeEditInputinfoStart1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(strlen(m_TestBegin_First)>3)
	{
		MessageBox(_T("请输入一个0-1000之间的数"),_T("钢轨轮廓检测软件"));
		m_TestBegin_First = _T("999");
	}

	UpdateData(FALSE);
}


void CTestInfoInputDlg::OnEnChangeEditInputinfoStart2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(strlen(m_TestBegin_Last)>1)
	{
		MessageBox(_T("请输入一个0-10之间的数"),_T("钢轨轮廓检测软件"));
		m_TestBegin_Last = _T("9");
	}

	UpdateData(FALSE);
}


void CTestInfoInputDlg::OnEnChangeEditInputinfoStart3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(strlen(m_TestBegin_Mid)>3)
	{
		MessageBox(_T("请输入一个0-1000之间的数"),_T("钢轨轮廓检测软件"));
		m_TestBegin_Mid = _T("999");
	}

	UpdateData(FALSE);
}


void CTestInfoInputDlg::OnBnClickedRadioXimohou()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("您选择的检测模式为铣磨量测量，需导入基准数据"),_T("钢轨轮廓检测软件"));			
	TCHAR szFilter[] =_T("测量文件(*.Hnu)|*.Hnu");
	CString lpszFileName = _T("D:\\Result\\.Hnu");
	CFileDialog fileDlg( TRUE, NULL, lpszFileName/*LastFilePath*/, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL,0,FALSE);
	CString strFilePath;
	if(IDOK == fileDlg.DoModal())
	{

		CString    HnuName = fileDlg.GetPathName();
		CString    HnuPath = HnuName.Left(strlen(HnuName)-12);
		CStdioFile HnuFile;
		CString strLinetemp;
		string strHnutemp;
		int SCBZD_FileNum_L=0;
		int SCBZD_FileNum_R=0;
		BOOL IsOpen=HnuFile.Open(HnuName,CFile::modeRead);
		if(IsOpen)
		{
			while(HnuFile.ReadString(strLinetemp))
			{
				strHnutemp=strLinetemp;
				if(strHnutemp.find("左实测标准点")!=string::npos)//有实测标准点的字样
				{														
					g_TestInfo_L.XMH_BaseFile[SCBZD_FileNum_L] = HnuPath+strLinetemp+".txt";								
					SCBZD_FileNum_L++;
				}
				if(strHnutemp.find("右实测标准点")!=string::npos)//有实测标准点的字样
				{														
					g_TestInfo_R.XMH_BaseFile[SCBZD_FileNum_R] = HnuPath+strLinetemp+".txt";								
					SCBZD_FileNum_R++;
				}
				//////自动识别上下行//////
				if (strHnutemp.find("下") != string::npos)
				{
					Encoder_Distance = 0.1;
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_UP))->SetCheck(TRUE);
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_DOWN))->SetCheck(FALSE);
				}
				if (strHnutemp.find("上")!= string::npos)
				{
					Encoder_Distance = -0.1;
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_UP))->SetCheck(FALSE);
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_DOWN))->SetCheck(TRUE);
				}
				

				GetDlgItem(IDC_RADIO_INPUTINFO_DOWN)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_INPUTINFO_UP)->EnableWindow(FALSE);
			}
			HnuFile.Close();
			g_TestInfo_L.XMH_BaseFileNum = SCBZD_FileNum_L;//表示有几个基准文件
			g_TestInfo_R.XMH_BaseFileNum = SCBZD_FileNum_R;//表示有几个基准文件
			CString tmpInfo;
			CString tmpStart;
			CString tmpEnd;
			CString tmpDirection;
			CString tmpXianbie;
			CString tmpGuiXing;
			char Flagchar = '\\';
			for(int i=0;i<g_TestInfo_L.XMH_BaseFileNum;i++)
			{
				tmpDirection = g_TestInfo_L.Direction;
				tmpXianbie = g_TestInfo_L.Xianbie;
				int Pos = g_TestInfo_L.XMH_BaseFile[i].ReverseFind(Flagchar);
				tmpInfo = g_TestInfo_L.XMH_BaseFile[i].Right(strlen(g_TestInfo_L.XMH_BaseFile[i])-Pos-1);
				Pos = tmpInfo.FindOneOf("-");
				if(0==i)
				{
					tmpStart = tmpInfo.Mid(Pos+1,6);//保存起始点
					int iK=atoi(tmpStart)/1000;
					int iD=atoi(tmpStart)%1000;
					tmpStart.Format("%s%d+%d",tmpXianbie,iK,iD);
					//////////////////////////////////////////////////////////////////////////
					m_TestBegin_First.Format("%d",iK);
					m_TestBegin_Mid.Format("%d",iD);
					m_TestBegin_Last.Format("%d",(atoi(tmpStart)%1000 -iD)*10);
					m_TestXianBie = tmpXianbie;
					GetDlgItem(IDC_EDIT_INPUTINFO_XIANBIE)->SetWindowTextA(tmpXianbie);
					GetDlgItem(IDC_EDIT_INPUTINFO_START1)->SetWindowTextA(m_TestBegin_First);
					GetDlgItem(IDC_EDIT_INPUTINFO_START3)->SetWindowTextA(m_TestBegin_Mid);
					GetDlgItem(IDC_EDIT_INPUTINFO_START2)->SetWindowTextA(m_TestBegin_Last);

				}				
				tmpEnd = tmpInfo.Mid(Pos+8,6);
				int iK=atoi(tmpEnd)/1000;
				int iD=atoi(tmpEnd)%1000;
				tmpEnd.Format("%s%d+%d",tmpXianbie,iK,iD);;
			}
			g_TestInfo_L.TestInfoYES_NO  = true;
			CString Mesg;
			Mesg.Format("基准文件导入成功，该文件里程范围为%s--%s",tmpStart,tmpEnd);
			MessageBox(_T(Mesg),_T("钢轨轮廓检测软件"));
		}
		else
		{
			MessageBox(_T("文件导入失败！"),_T("钢轨轮廓检测软件"));
			g_TestInfo_L.TestInfoYES_NO = false;
		}
	}
	else
	{
		MessageBox(_T("文件导入失败！"),_T("钢轨轮廓检测软件"));
		g_TestInfo_L.TestInfoYES_NO = false;
		return;
	}
}


void CTestInfoInputDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	g_TestInfo_L.TestInfoYES_NO = false;
	g_TestInfo_R.TestInfoYES_NO = false;
	CDialogEx::OnCancel();
}


void CTestInfoInputDlg::OnBnClickedRadioInputinfoUp()
{
	// TODO: 在此添加控件通知处理程序代码
	Encoder_Distance = 0.1;
	m_TestBegin_First = "0";
	GetDlgItem(IDC_EDIT_INPUTINFO_START1)->SetWindowTextA(_T("0"));
}


void CTestInfoInputDlg::OnBnClickedRadioInputinfoDown()
{
	// TODO: 在此添加控件通知处理程序代码
	Encoder_Distance = -0.1;
	m_TestBegin_First = "100";
	GetDlgItem(IDC_EDIT_INPUTINFO_START1)->SetWindowTextA(_T("100"));

}
