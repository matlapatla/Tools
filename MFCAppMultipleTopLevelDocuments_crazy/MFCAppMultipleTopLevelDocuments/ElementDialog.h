#pragma once
#include <memory> // for std::shared_ptr
#include "CElement.h"

#define WM_REFRESHPICTURE (WM_USER + 100)
// CElementDialog dialog

class CElementDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CElementDialog)

public:
	CElementDialog(CWnd* pParent = NULL);   // standard constructor
	CElementDialog(std::shared_ptr<CElement> ptr, CWnd* pParent = NULL);
	virtual ~CElementDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ELEMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	std::shared_ptr<CElement> m_pPlcSelected;

public:
	CString m_ElementName;
	CString m_PlcName;
	CString m_ElementAddress;
	afx_msg void OnBnClickedOk();
	CString m_VarType;
	afx_msg void OnBnClickedCancel();
	CString m_LowestValue;
	CString m_HighestValue;
};
