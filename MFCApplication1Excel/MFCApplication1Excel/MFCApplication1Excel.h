
// MFCApplication1Excel.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplication1ExcelApp:
// See MFCApplication1Excel.cpp for the implementation of this class
//

class CMFCApplication1ExcelApp : public CWinApp
{
public:
	CMFCApplication1ExcelApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication1ExcelApp theApp;
