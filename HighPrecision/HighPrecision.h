
// HighPrecision.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHighPrecisionApp:
// �йش����ʵ�֣������ HighPrecision.cpp
//

class CHighPrecisionApp : public CWinApp
{
public:
	CHighPrecisionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CHighPrecisionApp theApp;