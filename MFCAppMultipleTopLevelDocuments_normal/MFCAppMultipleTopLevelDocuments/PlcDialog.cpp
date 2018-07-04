// PlcDialog.cpp : implementation file
//

#include "stdafx.h"

#include "PlcDialog.h"



// CPlcDialog dialog

IMPLEMENT_DYNAMIC(CPlcDialog, CDialogEx)

CPlcDialog::CPlcDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PLC, pParent)
	, m_PlcName(_T(""))
	, m_PlcAccessPath(_T(""))
	, m_PlcConfigString(_T(""))
	, m_FilePathEditBox(_T(""))
{
	
}


CPlcDialog::CPlcDialog(std::shared_ptr<CElement> ptr, CWnd* pParent )
	: CDialogEx(IDD_DIALOG_PLC, pParent)
	, m_PlcName(_T(""))
	, m_PlcAccessPath(_T(""))
	, m_PlcConfigString(_T(""))
{

	//std::shared_ptr<CElement> m_pPlcSelected(ptr);
	m_pPlcSelected = ptr;

	m_PlcName = m_pPlcSelected->getName();
	m_PlcAccessPath = m_pPlcSelected->getAccessPath();
	m_PlcConfigString = m_pPlcSelected->getConfigString();
}




CPlcDialog::~CPlcDialog()
{
}

void CPlcDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PLCNAME, m_PlcName);
	DDX_Text(pDX, IDC_EDITPLCACCPATH, m_PlcAccessPath);
	DDX_Text(pDX, IDC_EDITPLCCONFSTRING, m_PlcConfigString);
	DDX_Text(pDX, IDC_VARLISTFILE, m_FilePathEditBox);
	DDX_Control(pDX, IDC_VARLISTFILE, m_FilePathEditBoxCtrl);
}


BEGIN_MESSAGE_MAP(CPlcDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PLCNAME, &CPlcDialog::OnEnChangeEditPlcname)
	ON_BN_CLICKED(IDOK, &CPlcDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONLINKVALISTFILE, &CPlcDialog::OnBnClickedButtonlinkvalistfile)
END_MESSAGE_MAP()


// CPlcDialog message handlers


void CPlcDialog::OnEnChangeEditPlcname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CPlcDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	//CMFCAppMultipleTopLevelDocumentsView * parent = (CMFCAppMultipleTopLevelDocumentsView*) GetParent();
	//CMFCAppMultipleTopLevelDocumentsView * parentowner = (CMFCAppMultipleTopLevelDocumentsView*)GetParentOwner();
	UpdateData(TRUE);
	m_pPlcSelected->setName(m_PlcName);
	m_pPlcSelected->setAccessPath(m_PlcAccessPath);
	m_pPlcSelected->setConfigString(m_PlcConfigString);
	CDialogEx::OnOK();
}


void CPlcDialog::OnBnClickedButtonlinkvalistfile()
{
	// TODO: Add your control notification handler code here
	const TCHAR szFilter[] = _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T("csv"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		m_FilePathEditBoxCtrl.SetWindowText(sFilePath);
		std::static_pointer_cast<CPlc> (m_pPlcSelected)->setVarlistFilePath(sFilePath);
	}

}
