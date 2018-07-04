#pragma once


// ConnectingToPlcDlg dialog

class ConnectingToPlcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConnectingToPlcDlg)

public:
	ConnectingToPlcDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ConnectingToPlcDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGCONNECTINGPLC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
