
// MFCAppMultipleTopLevelDocuments.h : main header file for the MFCAppMultipleTopLevelDocuments application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCAppMultipleTopLevelDocumentsApp:
// See MFCAppMultipleTopLevelDocuments.cpp for the implementation of this class
//


class CMFCAppMultipleTopLevelDocumentsApp : public CWinAppEx
{
public:
	CMFCAppMultipleTopLevelDocumentsApp();
	UINT PicWidth = 50;
	UINT PicHeight = 50;
	bool SetTheWidthHeight(int height, int width);

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:
	CDialog * p_Dlg;
// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnFileNewFrame();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
//	afx_msg void PokusDialogOnBnClickedOk();
	
	
};

extern CMFCAppMultipleTopLevelDocumentsApp theApp;
