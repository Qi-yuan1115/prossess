// MyFileDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "HighPrecision.h"
#include "MyFileDialog.h"


// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	skinppSetNoSkinHwnd(m_hWnd,TRUE);
}

CMyFileDialog::~CMyFileDialog()
{
}


BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
END_MESSAGE_MAP()



// CMyFileDialog 消息处理程序




BOOL CMyFileDialog::OnInitDialog()
{
	
	CFileDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
 INT_PTR CMyFileDialog:: DoModal()
{
	
	CFileDialog::DoModal();
	return 0;
}