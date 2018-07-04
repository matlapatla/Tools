#pragma once
class CAddPlcDialog : public CDialogEx
{
public:
	CAddPlcDialog();
	~CAddPlcDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditPlcname();
	afx_msg void OnEnChangeEditPlcpath();
};

