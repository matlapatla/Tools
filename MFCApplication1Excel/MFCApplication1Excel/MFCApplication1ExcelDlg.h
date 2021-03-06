
// MFCApplication1ExcelDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCApplication1ExcelDlg dialog
class CMFCApplication1ExcelDlg : public CDialog
{
// Construction
public:
	CMFCApplication1ExcelDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1EXCEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedRun();
	CButton m_bFillWithStrings;
	afx_msg void OnBnClickedGetvalues();
	CApplication oExcel;
	CWorkbook oBook;
};
