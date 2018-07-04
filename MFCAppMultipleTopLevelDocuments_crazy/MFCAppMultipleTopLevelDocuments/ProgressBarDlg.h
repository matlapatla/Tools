#pragma once
#include "afxcmn.h"
#include "Resource.h"
#define WM_MY_THREAD_MESSAGE (WM_USER + 101)

// ProgressBarDlg dialog

class ProgressBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ProgressBarDlg)

public:
	ProgressBarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ProgressBarDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROGRESSBAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CString textDlg;

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_progCtrl;
	static UINT ThreadProc(LPVOID ptr);
	void runProgBar(CString);
	LRESULT OnThreadMessage(WPARAM wParam, LPARAM);
};
