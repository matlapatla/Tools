#pragma once
#include "CPlc.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "MFCAppMultipleTopLevelDocumentsView.h"
#include "afxdialogex.h"


// CPlcDialog dialog

class CPlcDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPlcDialog)

public:
	CPlcDialog(CWnd* pParent = NULL);   // standard constructor
	CPlcDialog(std::shared_ptr<CElement> ptr, CWnd* pParent = NULL);   // standard constructor
	virtual ~CPlcDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PLC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//CMFCAppMultipleTopLevelDocumentsView * parentView;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditPlcname();
	CString m_PlcName;
	CString m_PlcAccessPath;
	CString m_PlcConfigString;
	afx_msg void OnBnClickedOk();
	CWnd* pParentCwnd;
	std::shared_ptr<CElement> m_pPlcSelected;
};
