// VariableControl.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "VariableControl.h"
#include "afxdialogex.h"


// VariableControl dialog

IMPLEMENT_DYNAMIC(VariableControl, CDialogEx)

VariableControl::VariableControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VARIABLECONTROL, pParent)
	//, m_SliderValue(0)
	, m_SliderVal(0)
	, m_RequestedValue(_T(""))
{

}

VariableControl::~VariableControl()
{
}

void VariableControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER2, m_SliderCtrl);
	//DDX_Slider(pDX, IDC_SLIDER2, m_SliderValue);
	DDX_Slider(pDX, IDC_SLIDER2, m_SliderVal);
	DDX_Text(pDX, IDC_EDIT1, m_RequestedValue);
}


BEGIN_MESSAGE_MAP(VariableControl, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &VariableControl::OnNMCustomdrawSlider2)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_BUTTON1_FORCEVALUE, &VariableControl::OnBnClickedButton1Forcevalue)
END_MESSAGE_MAP()


// VariableControl message handlers


void VariableControl::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	
}


void VariableControl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	//CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar == (CScrollBar *)&m_SliderCtrl) {
		int value = m_SliderCtrl.GetPos();
		//m_SliderCtrl.Format(_T("%d"), value);
		m_SliderVal = value;
		m_RequestedValue.Format(_T("%d"), value);
		 
		UpdateData(FALSE);
	}
	else {
		CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	}

}


BOOL VariableControl::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog. The framework does this automatically
	// when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);            // Set big icon
	//SetIcon(m_hIcon, FALSE);            // Set small icon

										// TODO: Add extra initialization here
	
	
	pElement->getLowestValue(lowestVal);
	_stscanf_s((LPCTSTR)lowestVal, _T("%I64u"), &ui64lowestVal);
	pElement->getHighestValue(highestVal);
	_stscanf_s((LPCTSTR)highestVal, _T("%I64u"), &ui64highestVal);
	m_SliderCtrl.SetRange((int)ui64lowestVal, (int)ui64highestVal, TRUE);
	pElement->getValue(currentVal);
	m_RequestedValue = currentVal;
	if (currentVal == "")
	{
		m_SliderCtrl.SetPos((int)ui64lowestVal);
	}
	else
	{
		_stscanf_s((LPCTSTR)currentVal, _T("%I64u"), &ui64currentVal);
		m_SliderCtrl.SetPos((int)ui64currentVal);
	}
	//m_SliderValue.Format(_T("%d"), 0);
	UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
}

void VariableControl::OnBnClickedButton1Forcevalue()
{
	// TODO: Add your control notification handler code here
}
