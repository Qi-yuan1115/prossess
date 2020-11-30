// ReprtParamDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "ReprtParamDlg.h"
#include "HighPrecisionDlg.h"
#include "afxdialogex.h"

extern CHighPrecisionDlg* pdlg;
// CReprtParamDlg �Ի���
double dPositiveLimit=0.5;//������
double dNegetiveLimit=-0.5;//������
IMPLEMENT_DYNAMIC(CReprtParamDlg, CDialogEx)

CReprtParamDlg::CReprtParamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReprtParamDlg::IDD, pParent)
	, m_posVal(_T(""))
	, m_negVal(_T(""))
{

}

CReprtParamDlg::~CReprtParamDlg()
{
}

void CReprtParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POSNUM, m_posVal);
	DDX_Text(pDX, IDC_EDIT_NEGNUM, m_negVal);
}


BEGIN_MESSAGE_MAP(CReprtParamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &CReprtParamDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCLE, &CReprtParamDlg::OnBnClickedBtnCancle)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CReprtParamDlg::OnBnClickedButtonFile)
END_MESSAGE_MAP()


// CReprtParamDlg ��Ϣ�������


void CReprtParamDlg::OnBnClickedBtnOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_posVal=="" || m_negVal=="")
	{
		MessageBox(_T("�����������޺͸�����ֵ��"),_T("�ֹ�����������"));
		
		UpdateData(FALSE);
		return ;
	}
	char* str = m_posVal.GetBufferSetLength(m_posVal.GetLength());
	dPositiveLimit=atof(str);//�������ֵ
	str = m_negVal.GetBufferSetLength(m_negVal.GetLength());
	dNegetiveLimit=atof(str);
	UpdateData(FALSE);
	pdlg->m_havePressAnalyse=FALSE;

	pdlg->OverValueHdmVec.clear();
	pdlg->RightOverValueHdmVec.clear();
	for (int CntLine=0;CntLine<(pdlg->m_PrecisionNumCnt);++CntLine)
	{
		for (int k=0;k<pdlg->precisionPointNum;++k)
		{
			if ((pdlg->localFileHdmVec[k][CntLine]>=0 && pdlg->localFileHdmVec[k][CntLine]>dPositiveLimit) ||(pdlg->localFileHdmVec[k][CntLine]<0 && pdlg->localFileHdmVec[k][CntLine]<dNegetiveLimit))
			{
				pdlg->OverValueHdmVec.push_back(pdlg->m_startAndEndVec[0][0]+0.1*CntLine);
				break;
			}
		}
	}
	for (int CntLine=0;CntLine<(pdlg->m_PrecisionNumCnt);++CntLine)
	{
		for (int k=0;k<pdlg->precisionPointNum;++k)
		{
			if ((pdlg->RightlocalFileHdmVec[k][CntLine]>=0 && pdlg->RightlocalFileHdmVec[k][CntLine]>dPositiveLimit) ||(pdlg->RightlocalFileHdmVec[k][CntLine]<0 && pdlg->RightlocalFileHdmVec[k][CntLine]<dNegetiveLimit))
			{
				pdlg->RightOverValueHdmVec.push_back(pdlg->m_startAndEndVec[0][0]+0.1*CntLine);
				break;
			}
		}
	}
	OnOK();
}
void CReprtParamDlg::OnBnClickedBtnCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


BOOL CReprtParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_posVal.Format("%.2f",dPositiveLimit);
	m_negVal.Format("%.2f",dNegetiveLimit);
	UpdateData(FALSE);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CReprtParamDlg::OnBnClickedButtonFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
