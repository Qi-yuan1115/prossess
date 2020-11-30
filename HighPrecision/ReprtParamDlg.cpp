// ReprtParamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "ReprtParamDlg.h"
#include "HighPrecisionDlg.h"
#include "afxdialogex.h"

extern CHighPrecisionDlg* pdlg;
// CReprtParamDlg 对话框
double dPositiveLimit=0.5;//正极限
double dNegetiveLimit=-0.5;//负极限
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


// CReprtParamDlg 消息处理程序


void CReprtParamDlg::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_posVal=="" || m_negVal=="")
	{
		MessageBox(_T("请输入正极限和负极限值！"),_T("钢轨轮廓检测软件"));
		
		UpdateData(FALSE);
		return ;
	}
	char* str = m_posVal.GetBufferSetLength(m_posVal.GetLength());
	dPositiveLimit=atof(str);//获得正极值
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
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


BOOL CReprtParamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_posVal.Format("%.2f",dPositiveLimit);
	m_negVal.Format("%.2f",dNegetiveLimit);
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CReprtParamDlg::OnBnClickedButtonFile()
{
	// TODO: 在此添加控件通知处理程序代码
}
