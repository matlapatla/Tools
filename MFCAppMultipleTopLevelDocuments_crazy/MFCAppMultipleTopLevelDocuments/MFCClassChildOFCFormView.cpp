// MFCClassChildOFCFormView.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "MFCClassChildOFCFormView.h"


// MFCClassChildOFCFormView

IMPLEMENT_DYNCREATE(MFCClassChildOFCFormView, CWinApp)



MFCClassChildOFCFormView::MFCClassChildOFCFormView()
{
}

MFCClassChildOFCFormView::~MFCClassChildOFCFormView()
{
}

BOOL MFCClassChildOFCFormView::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int MFCClassChildOFCFormView::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinApp::ExitInstance();
}

BEGIN_MESSAGE_MAP(MFCClassChildOFCFormView, CWinApp)

END_MESSAGE_MAP()


// MFCClassChildOFCFormView message handlers
