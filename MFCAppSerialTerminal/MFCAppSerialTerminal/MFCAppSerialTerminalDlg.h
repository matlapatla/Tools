
// MFCAppSerialTerminalDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "SerialPort.h"
#include "afxcmn.h"



#pragma comment (lib, "Setupapi.lib")
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <bthdef.h>
#include <bluetoothleapis.h>


#define ID_VIEW_BASE		WM_USER
#define WM_MY_MESSAGE WM_USER + 100

UINT MyThreadProc(LPVOID Param);

enum VIEW_TYPE { VIEW_2D, VIEW_OPENGL };

// CMFCAppSerialTerminalDlg dialog
class CMFCAppSerialTerminalDlg : public CDialog
{
// Construction
public:
	CMFCAppSerialTerminalDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPSERIALTERMINAL_DIALOG };
	
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT TestMessageCall(WPARAM wpD, LPARAM lpD);
	DECLARE_MESSAGE_MAP()

	CObList		m_listViews;
	void SelectTab(int nTab);




public:
	CString receivedBytes;
	CString sendBytes;
	CString m_strItemSelected;
	afx_msg void OnBnClickedButtonSend();
	CEdit m_SendEditControl;
	afx_msg void OnBnClickedButtonClear();
	CListBox m_ListBoxComPorts;
	afx_msg void OnLbnSelchangeList1Comport();
	afx_msg void LoadListBoxCOMPort();
	afx_msg void LoadListBoxBluetooth();
	afx_msg void OnBnClickedButton4Listcomports();
	CMFCButton m_ConnectSerialPortButton;
	afx_msg void OnBnClickedButtonConnectSerial();
	
	afx_msg void OnEnChangeEditPrintouts();
	CString m_EditPrintouts;
	SerialPort ComPort;

	BOOL xRxThreadAct = FALSE;
	

	CBitmap m_bitmapStart;
	CBitmap m_bitmapStop;
	//CButton m_buttonStart;
	CBitmapButton m_buttonStart;
	afx_msg void OnBnClickedButtonBitmapstart();
	afx_msg void OnBnClickedButton2dview();

	void AddView(VIEW_TYPE viewType);

	//CTabCtrl	m_tabCtrl;


	CTabCtrl m_tabCtrl;
	afx_msg void OnBnClickedButtonCreateDynamicView();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDisconnectSerialPort();
	afx_msg void OnBnClickedButton1Listbluetooth();
	CListBox m_ListBoxBluetooth;
	CListCtrl m_ListControlA;
	afx_msg void OnBnClickedButton1Createtable();
	//afx_msg void OnLvnItemchangedList2Listcontrola(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnBnClickedButton1Createmainframe();
	afx_msg void OnPokusHokus();
};






struct StructDataTransfer {
	CMFCAppSerialTerminalDlg * DlgInstancePtr;
	HWND HwndInstance;
	BOOL StopThread = FALSE;
	BOOL ThreadStopped = FALSE;
};





