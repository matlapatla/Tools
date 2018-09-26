#pragma once
#include "afxcmn.h"
#include <memory.h>
#include "CElement.h"
#include "CPlc.h"

// VariableControl dialog

class VariableControl : public CDialogEx
{
	DECLARE_DYNAMIC(VariableControl)

public:
	VariableControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~VariableControl();
	BOOL OnInitDialog();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VARIABLECONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CString lowestVal;
	CString highestVal;
	CString currentVal;
	CString requestedVal;
	CString ElementAddress;
	CString VarType;

	unsigned __int64 ui64lowestVal;
	unsigned __int64 ui64highestVal;
	unsigned __int64 ui64currentVal;

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SliderCtrl;
	//CString m_SliderValue;

	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int m_SliderVal;
	std::shared_ptr<CElement> pElement;
	std::shared_ptr<CElement> pPlc;
	CString m_RequestedValue;
	afx_msg void OnBnClickedButton1Forcevalue();
	CString m_lowThrHld;
	CString m_highThrHld;
};
