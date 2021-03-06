
// MFCAppSerialTerminalDlg.cpp : implementation file
//

#include "stdafx.h"

#include "MFCAppSerialTerminal.h"
#include "MFCAppSerialTerminalDlg.h"
#include "afxdialogex.h"
#include "CMyView.h"
#include "COpenGLView.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/*
struct StructDataTransfer
{
	CMFCAppSerialTerminalDlg * DlgInstancePtr;
	HWND HwndInstance;
	BOOL StopThread=FALSE;
};
*/
//StructDataTransfer DataTransfer, *DataTransferPtr;

StructDataTransfer DataTransferRxThrd, *DataTransferPtrRxThrd;

//#define WM_MY_MESSAGE WM_USER + 100

UINT __cdecl MyThreadProc(LPVOID Param) {
	
	CString nameTestMessage = __T("Call From Message");
	CString ErrorMsg;
	CString receivedBytes;
	DWORD dwBytesRead;
	CMFCAppSerialTerminalDlg *ptr = ((StructDataTransfer*)Param)->DlgInstancePtr;
	HWND hDlg = ((StructDataTransfer*)Param)->HwndInstance;
	while (!((StructDataTransfer*)Param)->StopThread) {
		
			ptr->ComPort.ReceiveFrame(receivedBytes, ErrorMsg, dwBytesRead);
			ptr->receivedBytes = receivedBytes;
			if (dwBytesRead > 0)
			{
				::SendMessage(hDlg, WM_MY_MESSAGE, (WPARAM)(&nameTestMessage), 0);
			}
	}
	((StructDataTransfer*)Param)->ThreadStopped = TRUE;
	AfxEndThread(1,TRUE);	
	return 0;
}


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCAppSerialTerminalDlg dialog



CMFCAppSerialTerminalDlg::CMFCAppSerialTerminalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MFCAPPSERIALTERMINAL_DIALOG, pParent)
	, receivedBytes(_T(""))
	, sendBytes(_T(""))
	
	, m_EditPrintouts(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCAppSerialTerminalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, receivedBytes);
	DDX_Text(pDX, IDC_EDIT2, sendBytes);
	DDX_Control(pDX, IDC_EDIT2, m_SendEditControl);
	DDX_Control(pDX, IDC_LIST1_COMPORT, m_ListBoxComPorts);
	DDX_Control(pDX, IDC_BUTTON_CONNECTSERIAL, m_ConnectSerialPortButton);

	DDX_Text(pDX, IDC_EDIT_PRINTOUTS, m_EditPrintouts);
	DDX_Control(pDX, IDC_BUTTON_BITMAPSTART, m_buttonStart);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	DDX_Control(pDX, IDC_LIST1_BLUETOOTH, m_ListBoxBluetooth);
	DDX_Control(pDX, IDC_LIST2_ListControlA, m_ListControlA);
}

BEGIN_MESSAGE_MAP(CMFCAppSerialTerminalDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCAppSerialTerminalDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMFCAppSerialTerminalDlg::OnBnClickedButtonClear)
	ON_LBN_SELCHANGE(IDC_LIST1_COMPORT, &CMFCAppSerialTerminalDlg::OnLbnSelchangeList1Comport)
	ON_BN_CLICKED(IDC_BUTTON4_LISTCOMPORTS, &CMFCAppSerialTerminalDlg::OnBnClickedButton4Listcomports)
	ON_BN_CLICKED(IDC_BUTTON_CONNECTSERIAL, &CMFCAppSerialTerminalDlg::OnBnClickedButtonConnectSerial)
	ON_EN_CHANGE(IDC_EDIT_PRINTOUTS, &CMFCAppSerialTerminalDlg::OnEnChangeEditPrintouts)
	ON_MESSAGE(WM_MY_MESSAGE, TestMessageCall)
	ON_BN_CLICKED(IDC_BUTTON_BITMAPSTART, &CMFCAppSerialTerminalDlg::OnBnClickedButtonBitmapstart)
	ON_BN_CLICKED(IDC_BUTTON_2DVIEW, &CMFCAppSerialTerminalDlg::OnBnClickedButton2dview)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_DYNAMIC_VIEW, &CMFCAppSerialTerminalDlg::OnBnClickedButtonCreateDynamicView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMFCAppSerialTerminalDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT_SERIAL_PORT, &CMFCAppSerialTerminalDlg::OnBnClickedButtonDisconnectSerialPort)
	ON_BN_CLICKED(IDC_BUTTON1_LISTBLUETOOTH, &CMFCAppSerialTerminalDlg::OnBnClickedButton1Listbluetooth)
	ON_BN_CLICKED(IDC_BUTTON1_CREATETABLE, &CMFCAppSerialTerminalDlg::OnBnClickedButton1Createtable)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2_ListControlA, &CMFCAppSerialTerminalDlg::OnLvnItemchangedList2Listcontrola)
	//ON_BN_CLICKED(IDC_BUTTON1_CREATEMAINFRAME, &CMFCAppSerialTerminalDlg::OnBnClickedButton1Createmainframe)
	ON_COMMAND(ID_POKUS_HOKUS, &CMFCAppSerialTerminalDlg::OnPokusHokus)
END_MESSAGE_MAP()


// CMFCAppSerialTerminalDlg message handlers

LRESULT CMFCAppSerialTerminalDlg::TestMessageCall(WPARAM wpD, LPARAM lpD)
{
	//CString *pwpD = (CString *)wpD;
	//CString ec_nameTestmessage = *pwpD;
	//CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_PRINTOUTS);
	//INT LineCount = pEdit->GetLineCount();
	//pEdit->LineScroll(pEdit->GetLineCount());
	//pEdit->LineScroll(LineCount);
	UpdateData(FALSE);
	return LRESULT();
}



BOOL CMFCAppSerialTerminalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	sendBytes = L"write a message here";
	m_ConnectSerialPortButton.SetTooltip(_T("This is the Button to initialize the Serial Port chosen below!"));

	m_bitmapStart.LoadBitmap(IDB_BITMAP_START);
	m_bitmapStop.LoadBitmap(IDB_BITMAP_STOP);
	HBITMAP hBitmapStart = (HBITMAP)m_bitmapStart.GetSafeHandle();
	
	m_buttonStart.SetBitmap(hBitmapStart);



	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCAppSerialTerminalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCAppSerialTerminalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCAppSerialTerminalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCAppSerialTerminalDlg::LoadListBoxBluetooth() {
	CString str = _T("");
	CStringList BluetoothDevs;
	HDEVINFO hDI;
	SP_DEVINFO_DATA did;
	DWORD i;


	while (m_ListBoxBluetooth.GetCount() > 0)
	{
		m_ListBoxBluetooth.DeleteString(0);
	}
	
	// Create a HDEVINFO with all present devices.
	// hDI = SetupDiGetClassDevs(&GUID_DEVCLASS_BLUETOOTH, NULL, NULL, DIGCF_PRESENT);
	 hDI = SetupDiGetClassDevs(&GUID_DEVCLASS_PORTS, NULL, NULL, DIGCF_PRESENT);
	 

	 if (hDI != INVALID_HANDLE_VALUE)
	 {
		 
		 // Enumerate through all devices in Set.
		 did.cbSize = sizeof(SP_DEVINFO_DATA);
		 //for (i = 0; SetupDiEnumDeviceInfo(hDI, i, &did); i++)
	     for (i = 0; i < 255; i++)
		 {
			 SetupDiEnumDeviceInfo(hDI, i, &did);
			 bool hasError = false;

			 DWORD nameData;
			 LPTSTR nameBuffer = NULL;
			 DWORD nameBufferSize = 0;

			 while (!SetupDiGetDeviceRegistryProperty(
				 hDI,
				 &did,
				 SPDRP_FRIENDLYNAME,
				 &nameData,
				 (PBYTE)nameBuffer,
				 nameBufferSize,
				 &nameBufferSize))
			 {
				 if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				 {
					 if (nameBuffer) delete(nameBuffer);
					 nameBuffer = new wchar_t[nameBufferSize * 2];
				 }
				 else
				 {
					 hasError = true;
					 break;
				 }
			 }

			 DWORD addressData;
			 LPTSTR addressBuffer = NULL;
			 DWORD addressBufferSize = 0;

			 while (!SetupDiGetDeviceRegistryProperty(
				 hDI,
				 &did,
				 SPDRP_HARDWAREID,
				 &addressData,
				 (PBYTE)addressBuffer,
				 addressBufferSize,
				 &addressBufferSize))
			 {
				 if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				 {
					 if (addressBuffer) delete(addressBuffer);
					 addressBuffer = new wchar_t[addressBufferSize * 2];
				 }
				 else
				 {
					 hasError = true;
					 break;
				 }
			 }

			 LPTSTR deviceIdBuffer = NULL;
			 DWORD deviceIdBufferSize = 0;

			 while (!SetupDiGetDeviceInstanceId(
				 hDI,
				 &did,
				 deviceIdBuffer,
				 deviceIdBufferSize,
				 &deviceIdBufferSize))
			 {
				 if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				 {
					 if (deviceIdBuffer) delete(deviceIdBuffer);
					 deviceIdBuffer = new wchar_t[deviceIdBufferSize * 2];
				 }
				 else
				 {
					 hasError = true;
					 break;
				 }
			 }

			 if (hasError)
			 {
				 continue;
			 }
			 BluetoothDevs.AddTail(nameBuffer);
			 m_ListBoxBluetooth.AddString(nameBuffer);

			/* std::string name = util::to_narrow(nameBuffer);
			 std::string address = util::to_narrow(addressBuffer);
			 std::string deviceId = util::to_narrow(deviceIdBuffer);
			 std::cout << "Found " << name << " (" << deviceId << ")" << std::endl; */
		 }









	 }

	
}


void CMFCAppSerialTerminalDlg::LoadListBoxCOMPort() {
	CString str = _T("");
	CStringList ports;
	
	while (m_ListBoxComPorts.GetCount() > 0)
	{	
		m_ListBoxComPorts.DeleteString(0);
	}
	

	for (int i = 1; i <= 128; i++)
	{
		CString strPort;
		strPort.Format(_T("COM%d"), i);

		DWORD dwSize = 0;
		LPCOMMCONFIG lpCC = (LPCOMMCONFIG) new BYTE[1];
		BOOL ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
		delete[] lpCC;

		lpCC = (LPCOMMCONFIG) new BYTE[dwSize];
		ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
		if (ret)
		{
			ports.AddTail(strPort);
			m_ListBoxComPorts.AddString(strPort);
		}

		delete[] lpCC;
	}
}

void CMFCAppSerialTerminalDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	CString str = L"";
	int iLineCount = m_SendEditControl.GetLineCount();
	m_SendEditControl.GetWindowTextW(sendBytes);
	//receivedBytes = sendBytes;
	CString ErrorMsg;
	
	switch (ComPort.SendFrame(sendBytes, ErrorMsg)) {
	case 0:
		m_EditPrintouts.Append(m_strItemSelected + L" Frame sent.\r\n");
		break;
	default:
		m_EditPrintouts.Append(m_strItemSelected + L" Unknown problem. " + ErrorMsg + "\r\n");

	}

	HBITMAP hBitmapStart = (HBITMAP)m_bitmapStart.GetSafeHandle();
	m_buttonStart.SetBitmap(hBitmapStart);

	UpdateData(FALSE);
	

}


void CMFCAppSerialTerminalDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	receivedBytes = L"";
	sendBytes = L"";	
	UpdateData(FALSE);
}

void CMFCAppSerialTerminalDlg::OnBnClickedButton1Listbluetooth()
{
	// TODO: Add your control notification handler code here
	this->LoadListBoxBluetooth();
	m_strItemSelected = "";
	UpdateData(FALSE);
}


void CMFCAppSerialTerminalDlg::OnLbnSelchangeList1Comport()
{
	// TODO: Add your control notification handler code here
	m_ListBoxComPorts.GetText(m_ListBoxComPorts.GetCurSel(), m_strItemSelected);
	m_EditPrintouts.Append(m_strItemSelected + L" chosen.\r\n");
	UpdateData(FALSE);
	
}


void CMFCAppSerialTerminalDlg::OnBnClickedButton4Listcomports()
{
	// TODO: Add your control notification handler code here
	this->LoadListBoxCOMPort();
	m_strItemSelected = "";
	UpdateData(FALSE);
}


void CMFCAppSerialTerminalDlg::OnBnClickedButtonConnectSerial()
{
	// TODO: Add your control notification handler code here	
	m_EditPrintouts.Append(m_strItemSelected + L" trying to connect.\r\n");	
	CString ErrorMsg;
	CWinThread * result = FALSE;
	CMFCAppSerialTerminalDlg * ptr = this;
	switch (ComPort.ConnectToPort(m_strItemSelected, ErrorMsg)) {

	case 0:	
		m_EditPrintouts.Append(m_strItemSelected + L" connected.\r\n");
		DataTransferRxThrd.DlgInstancePtr = this;
		DataTransferRxThrd.HwndInstance = GetSafeHwnd();
		DataTransferPtrRxThrd = &DataTransferRxThrd;
		result = AfxBeginThread(MyThreadProc,(LPVOID) DataTransferPtrRxThrd);
		if (nullptr == result) // <<== START THE THREAD receiving frames from the serial port
		{
			m_EditPrintouts.Append(m_strItemSelected + L" The start of the receiving thread failed. " + "\r\n");
			xRxThreadAct = FALSE;
		}
		else
		{
			xRxThreadAct = TRUE;
			m_EditPrintouts.Append(m_strItemSelected + L" The receiving thread started. " + "\r\n");
		}
		break;
	case 1:
		m_EditPrintouts.Append(m_strItemSelected + L" already connected. " + ErrorMsg + "\r\n");
		break;
	case 2:
		m_EditPrintouts.Append(m_strItemSelected + L" not connected. " + ErrorMsg + "\r\n");
		break;
	default:
		m_EditPrintouts.Append(m_strItemSelected + L" unknown problem. " + ErrorMsg + "\r\n");

	}
	
	UpdateData(FALSE);
}


void CMFCAppSerialTerminalDlg::OnEnChangeEditPrintouts()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}






void CMFCAppSerialTerminalDlg::OnBnClickedButtonBitmapstart()
{
	// TODO: Add your control notification handler code here
	HBITMAP hBitmapStop = (HBITMAP)m_bitmapStop.GetSafeHandle();
	m_buttonStart.SetBitmap(hBitmapStop);


}

void CMFCAppSerialTerminalDlg::AddView(VIEW_TYPE viewType)
{
	// ID of the new view
	int idNewView = m_listViews.GetCount();

	// View size
	CRect clientRect;
	m_tabCtrl.GetClientRect(&clientRect);
	clientRect.DeflateRect(10, 30);

	// Creation 'on the fly' of the new view
	CMyView* m_pNewView;
	CString tabCaption;

	//m_pNewView = nullptr;

	switch (viewType) {

	case VIEW_2D:
		// The operator 'new' has not asociated delete.
		// The view will be deleted automatically by the framework
		// on the WM_DESTROY handle of the parent (the tab control)
		m_pNewView = new CMyView();
		tabCaption.Format(L"View %d (2D)", idNewView);
		break;

	case VIEW_OPENGL:
		// The operator 'new' has not asociated delete.
		// The view will be deleted automatically by the framework
		// on the WM_DESTROY handle of the parent (the tab control)
		m_pNewView = new COpenGLView();
		tabCaption.Format(L"View %d (OpenGL)", idNewView);
		break;

	default:
		m_pNewView = new CMyView();

	};

	
		// The new tab for the view on the tab control
		m_tabCtrl.InsertItem(idNewView, tabCaption);
		m_pNewView->m_idView = idNewView;
	
	// Creation of the view window
	if (!m_pNewView->Create(NULL, NULL, WS_VISIBLE | WS_CHILD, clientRect,
		&m_tabCtrl, ID_VIEW_BASE + idNewView))
	{
		TRACE("Failed view creation\n");
	}

	// Using a list is easy to handle all the views created
	m_listViews.AddTail(m_pNewView);

	// Select the new created tab/view
	m_tabCtrl.SetCurSel(idNewView);
	SelectTab(idNewView);
}

void CMFCAppSerialTerminalDlg::SelectTab(int nTab)
{
	CMyView* pViewSelected = NULL;
	POSITION pos = m_listViews.GetHeadPosition();

	// Hide all views under the tabControl
	while (pos != NULL) {
		CMyView* pView = (CMyView*)m_listViews.GetNext(pos);
		pView->ShowWindow(SW_HIDE);
		if (pView->m_idView == nTab) pViewSelected = pView;
	};

	// Show the view asociated with the tab selected
	if (pViewSelected != NULL)
		pViewSelected->ShowWindow(SW_SHOW);
}


void CMFCAppSerialTerminalDlg::OnBnClickedButton2dview()
{
	// TODO: Add your control notification handler code here
	AddView(VIEW_2D);

}


void CMFCAppSerialTerminalDlg::OnBnClickedButtonCreateDynamicView()
{
	// TODO: Add your control notification handler code here
	AddView(VIEW_OPENGL);
}


void CMFCAppSerialTerminalDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;	
	int selectedTab = m_tabCtrl.GetCurSel();
	CString str;
	str.Format(L"%d", selectedTab);
	MessageBox(NULL, (LPCWSTR)str, MB_OK);	
	SelectTab(selectedTab);

}


void CMFCAppSerialTerminalDlg::OnBnClickedButtonDisconnectSerialPort()
{
	
	// TODO: Add your control notification handler code here	
	m_EditPrintouts.Append(m_strItemSelected + L" trying to disconnect.\r\n");

	if (DataTransferPtrRxThrd != nullptr)
	{
		DataTransferPtrRxThrd->StopThread = TRUE;
		CString ErrorMsg;
		CWinThread * result = FALSE;
		CMFCAppSerialTerminalDlg * ptr = this;
		while (!DataTransferPtrRxThrd->ThreadStopped)
		{
			m_EditPrintouts.Append(m_strItemSelected + L" Disconnected.\r\n");
			UpdateData(FALSE);
		}


		switch (ComPort.DisconnectPort(ErrorMsg))
		{

		case 0:
			m_EditPrintouts.Append(m_strItemSelected + L" Disconnected.\r\n");
			break;
		case 1:
			m_EditPrintouts.Append(m_strItemSelected + L" Disconnecting COM port failed. " + ErrorMsg + "\r\n");
			break;
		default:
			m_EditPrintouts.Append(m_strItemSelected + L" unknown problem. " + ErrorMsg + "\r\n");

		}
	}

	UpdateData(FALSE);


}




void CMFCAppSerialTerminalDlg::OnBnClickedButton1Createtable()
{
	//m_ListControlA.OnSelchange

	// TODO: Add your control notification handler code here

	//m_ListControlA.SetExtendedStyle(LVS_REPORT);
	
	COLORREF crBkColor = ::GetSysColor(COLOR_ACTIVEBORDER);//????????????

	m_ListControlA.SetBkColor(crBkColor);

	m_ListControlA.InsertColumn(0, L"Emp ID", LVCFMT_LEFT, -1, 0);
	m_ListControlA.InsertColumn(1, L"Name", LVCFMT_LEFT, -1, 1);
	m_ListControlA.InsertColumn(2, L"Age", LVCFMT_LEFT, -1, 1);
	m_ListControlA.SetColumnWidth(0, 120);
	m_ListControlA.SetColumnWidth(1, 200);
	m_ListControlA.SetColumnWidth(2, 200);

	

}

/*
void CMFCAppSerialTerminalDlg::OnLvnItemchangedList2Listcontrola(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
*/
/*
void CMFCAppSerialTerminalDlg::OnBnClickedButton1Createmainframe()
{
	// TODO: Add your control notification handler code here
	CMainFrame* pFrame = new CMainFrame;

	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// The one and only window has been initialized,<BR>	// so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
}
*/

void CMFCAppSerialTerminalDlg::OnPokusHokus()
{
	// TODO: Add your command handler code here

	MessageBox(NULL, L"pokus", MB_OK);

}
