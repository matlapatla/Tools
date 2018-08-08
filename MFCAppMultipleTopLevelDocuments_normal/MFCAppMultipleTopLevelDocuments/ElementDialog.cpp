// ElementDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "ElementDialog.h"
#include "afxdialogex.h"


// CElementDialog dialog

IMPLEMENT_DYNAMIC(CElementDialog, CDialogEx)

CElementDialog::CElementDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ELEMENT, pParent)
	, m_ElementName(_T(""))
	, m_PlcName(_T(""))
	, m_ElementAddress(_T(""))
	, m_VarType(_T(""))
	, m_LowestValue(_T(""))
	, m_HighestValue(_T(""))
	, m_ElementNameVarlist(_T(""))
{

}

CElementDialog::CElementDialog(std::shared_ptr<CElement> ptr, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_PLC, pParent)

{
	BOOL x;
	m_pPlcSelected = ptr;
	m_pPlcSelected->setDlgRunning(true);
	m_pPlcSelected->getElementName(m_ElementName);
	m_pPlcSelected->getPlcName(m_PlcName);
	m_pPlcSelected->getElementAddress(m_ElementAddress);
	m_pPlcSelected->getVarType(m_VarType);
	m_pPlcSelected->getDlgRunning(x);
	m_pPlcSelected->getLowestValue(m_LowestValue);
	m_pPlcSelected->getHighestValue(m_HighestValue);
	//PostMessage(pParent->GetTopWindow, WM_REFRESHPICTURE, 0);
	m_pPlcSelected->getElementNameVarlist(m_ElementNameVarlist);

}

CElementDialog::~CElementDialog()
{
}

void CElementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ELEMNAME, m_ElementName);
	DDX_Text(pDX, IDC_EDIT_PLCNAME, m_PlcName);
	DDX_Text(pDX, IDC_EDIT_ELEMADDRESS, m_ElementAddress);
	DDX_Text(pDX, IDC_EDIT_VARTYPE, m_VarType);
	DDX_Text(pDX, IDC_EDITLOWESTVALUE, m_LowestValue);
	DDX_Text(pDX, IDC_EDITHIGHESTVALUE, m_HighestValue);
	DDX_Text(pDX, IDC_EDIT_ELEMENTNAME, m_ElementNameVarlist);
	DDX_Control(pDX, IDC_EDIT_ELEMNAME, m_ElementNameCtrl);
	DDX_Control(pDX, IDC_EDIT_PLCNAME, m_PlcNameCtrl);
	DDX_Control(pDX, IDC_EDIT_ELEMENTNAME, m_ElementNameVarlistCtrl);
	DDX_Control(pDX, IDC_EDIT_ELEMADDRESS, m_ElementAddressCtrl);
	DDX_Control(pDX, IDC_EDIT_VARTYPE, m_VarTypeCtrl);
	DDX_Control(pDX, IDC_EDITLOWESTVALUE, m_LowestValueCtrl);
	DDX_Control(pDX, IDC_EDITHIGHESTVALUE, m_HighestValueCtrl);
}


BEGIN_MESSAGE_MAP(CElementDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CElementDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CElementDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CElementDialog message handlers


void CElementDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_pPlcSelected->setElementName(m_ElementName);
	m_pPlcSelected->setPlcName(m_PlcName);
	m_pPlcSelected->setElementAddress(m_ElementAddress);
	m_pPlcSelected->setVarType(m_VarType);
	m_pPlcSelected->setDlgRunning(false);
	m_pPlcSelected->setLowestValue(m_LowestValue);
	m_pPlcSelected->setHighestValue(m_HighestValue);

	m_pPlcSelected->setElementNameVarlist(m_ElementNameVarlist);
	//InvalidateRect(nullptr);
	//UpdateWindow();
	CDialogEx::OnOK();
}


void CElementDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_pPlcSelected->setDlgRunning(false);
	InvalidateRect(nullptr);
	UpdateWindow();
	CDialogEx::OnCancel();
}


void CElementDialog::FillEditBox(std::shared_ptr<CElement> ptr)
{
	m_ElementNameCtrl.SetWindowTextW(m_ElementName);
	m_PlcNameCtrl.SetWindowTextW(m_PlcName);
	m_ElementAddressCtrl.SetWindowTextW(m_ElementAddress);
	m_VarTypeCtrl.SetWindowTextW(m_VarType);
	m_LowestValueCtrl.SetWindowTextW(m_LowestValue);
	m_HighestValueCtrl.SetWindowTextW(m_HighestValue);
	m_ElementNameVarlistCtrl.SetWindowTextW(m_ElementNameVarlist);
}