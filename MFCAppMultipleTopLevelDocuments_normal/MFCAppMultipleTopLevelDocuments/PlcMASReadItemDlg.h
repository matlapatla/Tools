#pragma once
#include "CPlc.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "MFCAppMultipleTopLevelDocumentsView.h"
#include "afxdialogex.h"
#include "afxwin.h"

// CPlcMASReadItemDlg dialog
#define WM_REFRESHPICTURE (WM_USER + 100)

class CPlcMASReadItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPlcMASReadItemDlg)

public:
	CPlcMASReadItemDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlcMASReadItemDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGMASREADITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonmasreaditem();

protected:
	std::shared_ptr<CElement> m_pPlcSelected;

public:
	void setpPlc(std::shared_ptr<CElement>);

	CString varAbsAddr;
	CString sVariableSelectronType;
	afx_msg void OnBnClickedButtonsetmonitorlist();
	afx_msg void OnBnClickedButtonreadmonitorlist();
	afx_msg void OnBnClickedButtongeneratemonitorlist();
	afx_msg void OnBnClickedButtongetmonitorliststate();
	CString m_MasReadItemVar;
	CEdit m_EditControl;
	CString m_RequestedVariableValue;
	BOOL m_IncludeToForceList;
	afx_msg void OnBnClickedButtonmassetitem();
	afx_msg void OnBnClickedButtonrunmasforceremoveabsolut();
	afx_msg void OnBnClickedButtonmaswriteitemabsolute();
};
