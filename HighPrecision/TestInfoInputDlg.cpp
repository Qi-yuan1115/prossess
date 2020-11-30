// TestInfoInputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "TestInfoInputDlg.h"
#include "afxdialogex.h"
#include "string"
using namespace std;



TestInfo     g_TestInfo_L={1,0,0.0,_T("k"),_T("˳"),_T(""),0,false};     //�����ҵ��Ϣ
TestInfo     g_TestInfo_R={1,0,0.0,_T("k"),_T("˳"),_T(""),0,false};     //�ҹ���ҵ��Ϣ
double       Encoder_Distance = 0.1;			//�ɼ�����̵�λ


// CTestInfoInputDlg �Ի���

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


// CTestInfoInputDlg ��Ϣ�������

BOOL CTestInfoInputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(TRUE);
	m_TrackSel = 1;//Ĭ��60��

	UpdateData(FALSE);
	Encoder_Distance = 0.1;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE

}

void CTestInfoInputDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	g_TestInfo_L.TrackSel        = m_TrackSel;
	g_TestInfo_L.XM_QianHou      = m_XmQianHou;
	g_TestInfo_L.Xianbie         = m_TestXianBie;
	g_TestInfo_L.DistanceStart   = atoi(m_TestBegin_First)*1000+atoi(m_TestBegin_Mid)+atoi(m_TestBegin_Last)*0.1;
	g_TestInfo_L.Direction       = (m_Direction==0)?_T("��"):_T("��");

	g_TestInfo_R.TrackSel        = m_TrackSel;
	g_TestInfo_R.XM_QianHou      = m_XmQianHou;
	g_TestInfo_R.Xianbie         = m_TestXianBie;
	g_TestInfo_R.DistanceStart   = atoi(m_TestBegin_First)*1000+atoi(m_TestBegin_Mid)+atoi(m_TestBegin_Last)*0.1;
	g_TestInfo_R.Direction       = (m_Direction==0)?_T("��"):_T("��");

	if(0==m_XmQianHou)//ϳĥǰ
		g_TestInfo_L.TestInfoYES_NO = true;//ϳĥǰֱ�ӾͿ��Կ�ʼ���
	/////�Զ�ʶ��������//////
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(strlen(m_TestBegin_First)>3)
	{
		MessageBox(_T("������һ��0-1000֮�����"),_T("�ֹ�����������"));
		m_TestBegin_First = _T("999");
	}

	UpdateData(FALSE);
}


void CTestInfoInputDlg::OnEnChangeEditInputinfoStart2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(strlen(m_TestBegin_Last)>1)
	{
		MessageBox(_T("������һ��0-10֮�����"),_T("�ֹ�����������"));
		m_TestBegin_Last = _T("9");
	}

	UpdateData(FALSE);
}


void CTestInfoInputDlg::OnEnChangeEditInputinfoStart3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(strlen(m_TestBegin_Mid)>3)
	{
		MessageBox(_T("������һ��0-1000֮�����"),_T("�ֹ�����������"));
		m_TestBegin_Mid = _T("999");
	}

	UpdateData(FALSE);
}


void CTestInfoInputDlg::OnBnClickedRadioXimohou()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��ѡ��ļ��ģʽΪϳĥ���������赼���׼����"),_T("�ֹ�����������"));			
	TCHAR szFilter[] =_T("�����ļ�(*.Hnu)|*.Hnu");
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
				if(strHnutemp.find("��ʵ���׼��")!=string::npos)//��ʵ���׼�������
				{														
					g_TestInfo_L.XMH_BaseFile[SCBZD_FileNum_L] = HnuPath+strLinetemp+".txt";								
					SCBZD_FileNum_L++;
				}
				if(strHnutemp.find("��ʵ���׼��")!=string::npos)//��ʵ���׼�������
				{														
					g_TestInfo_R.XMH_BaseFile[SCBZD_FileNum_R] = HnuPath+strLinetemp+".txt";								
					SCBZD_FileNum_R++;
				}
				//////�Զ�ʶ��������//////
				if (strHnutemp.find("��") != string::npos)
				{
					Encoder_Distance = 0.1;
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_UP))->SetCheck(TRUE);
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_DOWN))->SetCheck(FALSE);
				}
				if (strHnutemp.find("��")!= string::npos)
				{
					Encoder_Distance = -0.1;
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_UP))->SetCheck(FALSE);
					((CButton*)GetDlgItem(IDC_RADIO_INPUTINFO_DOWN))->SetCheck(TRUE);
				}
				

				GetDlgItem(IDC_RADIO_INPUTINFO_DOWN)->EnableWindow(FALSE);
				GetDlgItem(IDC_RADIO_INPUTINFO_UP)->EnableWindow(FALSE);
			}
			HnuFile.Close();
			g_TestInfo_L.XMH_BaseFileNum = SCBZD_FileNum_L;//��ʾ�м�����׼�ļ�
			g_TestInfo_R.XMH_BaseFileNum = SCBZD_FileNum_R;//��ʾ�м�����׼�ļ�
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
					tmpStart = tmpInfo.Mid(Pos+1,6);//������ʼ��
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
			Mesg.Format("��׼�ļ�����ɹ������ļ���̷�ΧΪ%s--%s",tmpStart,tmpEnd);
			MessageBox(_T(Mesg),_T("�ֹ�����������"));
		}
		else
		{
			MessageBox(_T("�ļ�����ʧ�ܣ�"),_T("�ֹ�����������"));
			g_TestInfo_L.TestInfoYES_NO = false;
		}
	}
	else
	{
		MessageBox(_T("�ļ�����ʧ�ܣ�"),_T("�ֹ�����������"));
		g_TestInfo_L.TestInfoYES_NO = false;
		return;
	}
}


void CTestInfoInputDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_TestInfo_L.TestInfoYES_NO = false;
	g_TestInfo_R.TestInfoYES_NO = false;
	CDialogEx::OnCancel();
}


void CTestInfoInputDlg::OnBnClickedRadioInputinfoUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Encoder_Distance = 0.1;
	m_TestBegin_First = "0";
	GetDlgItem(IDC_EDIT_INPUTINFO_START1)->SetWindowTextA(_T("0"));
}


void CTestInfoInputDlg::OnBnClickedRadioInputinfoDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Encoder_Distance = -0.1;
	m_TestBegin_First = "100";
	GetDlgItem(IDC_EDIT_INPUTINFO_START1)->SetWindowTextA(_T("100"));

}
