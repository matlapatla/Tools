// ProgressBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "ProgressBarDlg.h"
#include "afxdialogex.h"


// ProgressBarDlg dialog

IMPLEMENT_DYNAMIC(ProgressBarDlg, CDialogEx)

ProgressBarDlg::ProgressBarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROGRESSBAR, pParent)
{
	
}


ProgressBarDlg::~ProgressBarDlg()
{
}

void ProgressBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progCtrl);
}


BEGIN_MESSAGE_MAP(ProgressBarDlg, CDialogEx)
	ON_MESSAGE(WM_MY_THREAD_MESSAGE, OnThreadMessage)
END_MESSAGE_MAP()


// ProgressBarDlg message handlers

UINT ProgressBarDlg::ThreadProc(LPVOID ptr)
{
	ProgressBarDlg* pThis = (ProgressBarDlg*)ptr;
	for (int i = 0; i <= 120; i++) 
	{
		pThis->SendMessage(WM_MY_THREAD_MESSAGE, i);
		Sleep(1000);
	}
	return 0;
}
void ProgressBarDlg::runProgBar(CString text)
{
	// TODO: Add your control notification handler code here
	textDlg = text;
	
	CWinThread *pThread = AfxBeginThread(ThreadProc, this);
}

LRESULT ProgressBarDlg::OnThreadMessage(WPARAM wParam, LPARAM)
{
	int nProgress = (int)wParam;

	// update progress bar
	m_progCtrl.SetPos(nProgress);

	CString strStatus;
	strStatus.Format(L"Processing item: %d", nProgress);

	// update status text
	m_progCtrl.SetWindowText(strStatus);

	return 0;
}