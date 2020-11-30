#pragma once


// CMyFileDialog

class CMyFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CMyFileDialog)

public:
	CMyFileDialog(BOOL bOpenFileDialog, // ���� FileOpen Ϊ TRUE������ FileSaveAs Ϊ FALSE
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	virtual ~CMyFileDialog();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal();
};


