#include "stdafx.h"
#include "CAddPlcDialog.h"


CAddPlcDialog::CAddPlcDialog()
{
}


CAddPlcDialog::~CAddPlcDialog()
{
}
BEGIN_MESSAGE_MAP(CAddPlcDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddPlcDialog::OnBnClickedOk)
//	ON_EN_CHANGE(IDC_EDIT_PLCNAME, &CAddPlcDialog::OnEnChangeEditPlcname)
//	ON_EN_CHANGE(IDC_EDIT_PLCPATH, &CAddPlcDialog::OnEnChangeEditPlcpath)
END_MESSAGE_MAP()


void CAddPlcDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnOK();
}


void CAddPlcDialog::OnEnChangeEditPlcname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CAddPlcDialog::OnEnChangeEditPlcpath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
