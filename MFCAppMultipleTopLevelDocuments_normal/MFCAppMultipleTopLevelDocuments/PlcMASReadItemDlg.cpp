// PlcMASReadItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "PlcMASReadItemDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// CPlcMASReadItemDlg dialog

IMPLEMENT_DYNAMIC(CPlcMASReadItemDlg, CDialogEx)


CPlcMASReadItemDlg::CPlcMASReadItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOGMASREADITEM, pParent)
	, varAbsAddr(_T(""))
	, sVariableSelectronType(_T(""))
	, m_MasReadItemVar(_T(""))
	, m_RequestedVariableValue(_T(""))
	, m_IncludeToForceList(FALSE)
{

}

CPlcMASReadItemDlg::~CPlcMASReadItemDlg()
{
}

void CPlcMASReadItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, varAbsAddr);
	DDX_Text(pDX, IDC_EDIT2, sVariableSelectronType);
	DDX_Text(pDX, IDC_EDITMASREADITEMVAL, m_MasReadItemVar);
	DDX_Control(pDX, IDC_EDITMASREADITEMVAL, m_EditControl);
	DDX_Text(pDX, IDC_EDITREQUESTEDVARVALUE, m_RequestedVariableValue);
	DDX_Check(pDX, IDC_CHECKINCLUDETOFORCELIST, m_IncludeToForceList);
}


BEGIN_MESSAGE_MAP(CPlcMASReadItemDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONMASREADITEM, &CPlcMASReadItemDlg::OnBnClickedButtonmasreaditem)
	ON_BN_CLICKED(IDC_BUTTONSETMONITORLIST, &CPlcMASReadItemDlg::OnBnClickedButtonsetmonitorlist)
	ON_BN_CLICKED(IDC_BUTTONREADMONITORLIST, &CPlcMASReadItemDlg::OnBnClickedButtonreadmonitorlist)
	ON_BN_CLICKED(IDC_BUTTONGENERATEMONITORLIST, &CPlcMASReadItemDlg::OnBnClickedButtongeneratemonitorlist)
	ON_BN_CLICKED(IDC_BUTTONGETMONITORLISTSTATE, &CPlcMASReadItemDlg::OnBnClickedButtongetmonitorliststate)
	ON_BN_CLICKED(IDC_BUTTONMASSETITEM, &CPlcMASReadItemDlg::OnBnClickedButtonmassetitem)
	ON_BN_CLICKED(IDC_BUTTONRUNMASFORCEREMOVEABSOLUT, &CPlcMASReadItemDlg::OnBnClickedButtonrunmasforceremoveabsolut)
	ON_BN_CLICKED(IDC_BUTTONMASWRITEITEMABSOLUTE, &CPlcMASReadItemDlg::OnBnClickedButtonmaswriteitemabsolute)
END_MESSAGE_MAP()


// CPlcMASReadItemDlg message handlers

void CPlcMASReadItemDlg::setpPlc(std::shared_ptr<CElement> ptr)
{

	m_pPlcSelected = ptr;

}

void CPlcMASReadItemDlg::OnBnClickedButtonmasreaditem()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->callMASReadItem(varAbsAddr, sVariableSelectronType, m_MasReadItemVar);
	m_EditControl.SetWindowTextW(m_MasReadItemVar);
	//UpdateData(TRUE);
}


void CPlcMASReadItemDlg::OnBnClickedButtonsetmonitorlist()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->Set_MonitorList();
}


void CPlcMASReadItemDlg::OnBnClickedButtonreadmonitorlist()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->Read_MonitorList();
	//pPlc->getMainWindowHnd();
	
	(pPlc->getMainWindowCwnd())->SendMessage(WM_REFRESHPICTURE, 0, 0);
	
}




void CPlcMASReadItemDlg::OnBnClickedButtongeneratemonitorlist()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->GenerateMonitorList();

}


void CPlcMASReadItemDlg::OnBnClickedButtongetmonitorliststate()
{
	// TODO: Add your control notification handler code here
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->Get_MonitorListState();
}


void CPlcMASReadItemDlg::OnBnClickedButtonmassetitem()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->callMASForceAddAbsolute(varAbsAddr, sVariableSelectronType, m_RequestedVariableValue);
	
}


void CPlcMASReadItemDlg::OnBnClickedButtonrunmasforceremoveabsolut()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->callMASForceRemoveAbsolut(varAbsAddr, sVariableSelectronType, m_RequestedVariableValue);

}


void CPlcMASReadItemDlg::OnBnClickedButtonmaswriteitemabsolute()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pPlcSelected.get());
	pPlc->callMASWriteItemAbsolute(varAbsAddr, sVariableSelectronType, m_RequestedVariableValue);

}
