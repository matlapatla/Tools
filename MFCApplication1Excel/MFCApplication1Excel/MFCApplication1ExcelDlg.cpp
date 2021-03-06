
// MFCApplication1ExcelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "MFCApplication1Excel.h"
#include "MFCApplication1ExcelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFCApplication1ExcelDlg dialog



CMFCApplication1ExcelDlg::CMFCApplication1ExcelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MFCAPPLICATION1EXCEL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1ExcelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK, m_bFillWithStrings);
}

BEGIN_MESSAGE_MAP(CMFCApplication1ExcelDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDRUN, &CMFCApplication1ExcelDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_GETVALUES, &CMFCApplication1ExcelDlg::OnBnClickedGetvalues)
END_MESSAGE_MAP()


// CMFCApplication1ExcelDlg message handlers

BOOL CMFCApplication1ExcelDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1ExcelDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1ExcelDlg::OnPaint()
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
HCURSOR CMFCApplication1ExcelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CMFCApplication1ExcelDlg::OnBnClickedRun()
{
	// TODO: Add your control notification handler code here
	/*
	CApplication app;  // app is the Excel _Application object

					   // Start Excel and get Application object.

	if (!app.CreateDispatch(L"Excel.Application"))
	{
		AfxMessageBox(L"Cannot start Excel and get Application object.");
		return;
	}
	else
	{
		//Make the application visible and give the user control of
		//Microsoft Excel.
		app.put_Visible(TRUE);
		app.put_UserControl(TRUE);
	}
*/
	CWorkbooks oBooks;
	CWorksheets oSheets;
	CWorksheet oSheet;
	CRange oRange;
	
	COleVariant covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);

	// If you have not created Excel, create a new instance.
	if (oExcel.m_lpDispatch == NULL) {
		oExcel.CreateDispatch(L"Excel.Application");
	}
	// Show Excel to the user.
	oExcel.put_Visible(TRUE);
	oExcel.put_UserControl(TRUE);

	// Add a new workbook and get the first worksheet in that book.
	oBooks = oExcel.get_Workbooks();
	oBook = oBooks.Add(covOptional);
	oSheets = oBook.get_Worksheets();
	oSheet = oSheets.get_Item(COleVariant((short)1));

	// Get a range of data.
	oRange = oSheet.get_Range(COleVariant(L"A1"), covOptional);
	oRange = oRange.get_Resize(COleVariant((short)5), COleVariant((short)5));

	COleSafeArray saRet;
	DWORD numElements[2];
	numElements[0] = 5;
	numElements[1] = 5;

	long index[2];
	// Create a BSTR or double safe array.
	if (m_bFillWithStrings.GetCheck())
		saRet.Create(VT_BSTR, 2, numElements);
	else
		saRet.Create(VT_R8, 2, numElements);

	// Fill the array with data.
	for (int iRow = 1; iRow <= 5; iRow++) {
		for (int iCol = 1; iCol <= 5; iCol++) {
			index[0] = iRow - 1;
			index[1] = iCol - 1;
			if (m_bFillWithStrings.GetCheck()) {
				CString szTemp;
				szTemp.Format(L"%d|%d", iRow, iCol);
				BSTR bstr = szTemp.AllocSysString();
				saRet.PutElement(index, bstr);
				SysFreeString(bstr);
			}
			else {
				double d = iRow * iCol;
				saRet.PutElement(index, &d);
			}
		}
	}
	// Send the array to Excel.
	oRange.put_Value(covOptional, COleVariant(saRet));





}


void CMFCApplication1ExcelDlg::OnBnClickedGetvalues()
{
	// TODO: Add your control notification handler code here
	CWorksheets oSheets;
	CWorksheet oSheet;
	CRange oRange;
	
	COleVariant covOptional(DISP_E_PARAMNOTFOUND, VT_ERROR);

	// Make sure that Excel has been started.
	if (oExcel.m_lpDispatch == NULL) {
		AfxMessageBox(L"Excel has not been started.  Press button1 to start Excel.");
		return;
	}
	// Get the first worksheet.
	oSheets = oBook.get_Worksheets();
	oSheet = oSheets.get_Item(COleVariant((short)1));
	// Set the range of data to retrieve
	oRange = oSheet.get_Range(COleVariant(L"A1"), COleVariant(L"E5"));

	// Get the data.
	COleSafeArray saRet(oRange.get_Value(covOptional));

	long iRows;
	long iCols;
	saRet.GetUBound(1, &iRows);
	saRet.GetUBound(2, &iCols);

	CString valueString = L"Array Data:\r\n";
	long index[2];
	// Loop through the data and report the contents.
	for (int rowCounter = 1; rowCounter <= iRows; rowCounter++) {
		for (int colCounter = 1; colCounter <= iCols; colCounter++) {
			index[0] = rowCounter;
			index[1] = colCounter;
			COleVariant vData;
			saRet.GetElement(index, vData);
			CString szdata(vData);
			valueString += szdata;
			valueString += "\t";
		}
		valueString += "\r\n";
	}
	AfxMessageBox(valueString, MB_SETFOREGROUND, NULL);
}
