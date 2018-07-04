// DynViewsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DynViews.h"
#include "DynViewsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "OpenGLView.h"

// That define allows to asociate an ID for each view
// We only have to use:
// WM_USER + 0 for the first view
// WM_USER + 1 for the second view
// WM_USER + 2 for the third view
// ...
// WM_USER + n for the (n+1) view

#define ID_VIEW_BASE		WM_USER

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynViewsDlg dialog

CDynViewsDlg::CDynViewsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDynViewsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDynViewsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDynViewsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDynViewsDlg)
	DDX_Control(pDX, IDC_TABCTRL, m_tabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDynViewsDlg, CDialog)
	//{{AFX_MSG_MAP(CDynViewsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCTRL, OnSelchangeTabctrl)
	ON_BN_CLICKED(IDC_ADDVIEW, OnAddview)
	ON_BN_CLICKED(IDC_ADDOPENGLVIEW, OnAddopenglview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynViewsDlg message handlers

BOOL CDynViewsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDynViewsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDynViewsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDynViewsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
 * This method switchs the visibility of each
 * view, making visible only the selected view
 * asociated with the tab nTab
 *
 */
void CDynViewsDlg::SelectTab(int nTab)
{
	CMyView* pViewSelected = NULL;
	POSITION pos = m_listViews.GetHeadPosition();

	// Hide all views under the tabControl
	while(pos != NULL) {
		CMyView* pView = (CMyView*) m_listViews.GetNext(pos);
		pView->ShowWindow(SW_HIDE);
		if(pView->m_idView == nTab) pViewSelected = pView;
	};

	// Show the view asociated with the tab selected
	if(pViewSelected != NULL)
		pViewSelected->ShowWindow(SW_SHOW);
}

void CDynViewsDlg::OnSelchangeTabctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	SelectTab(m_tabCtrl.GetCurSel());

	*pResult = 0;
}

// Handle for button click "Add 2D View"
void CDynViewsDlg::OnAddview() 
{
	AddView(VIEW_2D);
}

// Handle for button click "Add 3D/OpenGL View"
void CDynViewsDlg::OnAddopenglview() 
{
	AddView(VIEW_OPENGL);
}

/*
 * AddView Method:
 *
 * 1. Creates a new tab for the view
 * 2. Creates a new view dynamically of the desired type
 * 3. Asociates the id of the view with the id of the tab
 * 4. Selects the new created view and tab
 */
void CDynViewsDlg::AddView(VIEW_TYPE viewType)
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
	
	switch(viewType) {

	case VIEW_2D:
		// The operator 'new' has not asociated delete.
		// The view will be deleted automatically by the framework
		// on the WM_DESTROY handle of the parent (the tab control)
		m_pNewView = new CMyView();
		tabCaption.Format("View %d (2D)", idNewView);
		break;

	case VIEW_OPENGL:
		// The operator 'new' has not asociated delete.
		// The view will be deleted automatically by the framework
		// on the WM_DESTROY handle of the parent (the tab control)
		m_pNewView = new COpenGLView();
		tabCaption.Format("View %d (OpenGL)", idNewView);
		break;

	};
		
	// The new tab for the view on the tab control
	m_tabCtrl.InsertItem(idNewView, tabCaption);
	m_pNewView->m_idView = idNewView;

	// Creation of the view window
	if(! m_pNewView->Create(NULL, NULL, WS_VISIBLE | WS_CHILD, clientRect,
							&m_tabCtrl, ID_VIEW_BASE + idNewView))
	{
		TRACE( "Failed view creation\n" );
	}

	// Using a list is easy to handle all the views created
	m_listViews.AddTail(m_pNewView);

	// Select the new created tab/view
	m_tabCtrl.SetCurSel(idNewView);
	SelectTab(idNewView);
}

