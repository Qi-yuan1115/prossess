// MyFileDialog.cpp : ʵ���ļ�
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



// CMyFileDialog ��Ϣ�������




BOOL CMyFileDialog::OnInitDialog()
{
	
	CFileDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
 INT_PTR CMyFileDialog:: DoModal()
{
	
	CFileDialog::DoModal();
	return 0;
}