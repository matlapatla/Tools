
// MFCAppMultipleTopLevelDocumentsView.cpp : implementation of the CMFCAppMultipleTopLevelDocumentsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCAppMultipleTopLevelDocuments.h"
#endif

#include "MFCAppMultipleTopLevelDocumentsDoc.h"
#include "MFCAppMultipleTopLevelDocumentsView.h"
#include "ConnectingToPlcDlg.h";

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppMultipleTopLevelDocumentsView

//IMPLEMENT_DYNCREATE(CMFCAppMultipleTopLevelDocumentsView, CView)
IMPLEMENT_DYNCREATE(CMFCAppMultipleTopLevelDocumentsView, CScrollView)

//BEGIN_MESSAGE_MAP(CMFCAppMultipleTopLevelDocumentsView, CView)
BEGIN_MESSAGE_MAP(CMFCAppMultipleTopLevelDocumentsView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCAppMultipleTopLevelDocumentsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
//	ON_WM_RBUTTONUP()
//	ON_BN_CLICKED(IDOK, &CMFCAppMultipleTopLevelDocumentsView::OnBnClickedOk)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOVE()
ON_WM_MOUSEMOVE()
//ON_WM_PAINT()
ON_BN_CLICKED(IDC_MFCBUTTON1, &CMFCAppMultipleTopLevelDocumentsView::OnBnClickedMfcbutton1)
//ON_BN_CLICKED(IDOK, &CMFCAppMultipleTopLevelDocumentsView::OnBnClickedOk)
ON_COMMAND(ID_ADDSWITCH, &CMFCAppMultipleTopLevelDocumentsView::OnAddswitch)
ON_COMMAND(ID_ELEMENT_DELETE, &CMFCAppMultipleTopLevelDocumentsView::OnElementDelete)
ON_COMMAND(ID_ELEMENT_SWITCHOFF, &CMFCAppMultipleTopLevelDocumentsView::OnElementSwitchoff)
ON_COMMAND(ID_ELEMENT_SWITCHON, &CMFCAppMultipleTopLevelDocumentsView::OnElementSwitchon)
ON_COMMAND(ID_ADDBULB, &CMFCAppMultipleTopLevelDocumentsView::OnAddbulb)
ON_COMMAND(ID_LOAD_ELEMENTS, &CMFCAppMultipleTopLevelDocumentsView::OnLoadElements)
ON_COMMAND(ID_FILE_STORE_ELEMENTS, &CMFCAppMultipleTopLevelDocumentsView::OnFileStoreElements)

//ON_COMMAND(ID_PLC_DEFINEPLC, &CMFCAppMultipleTopLevelDocumentsView::OnPlcDefineplc)

ON_COMMAND(ID_ADDPLC, &CMFCAppMultipleTopLevelDocumentsView::OnMenuAddPlc)
//ON_COMMAND(ID_ELEMENTPLC_DEFINEPLC, &CMFCAppMultipleTopLevelDocumentsView::OnElementPlcDefinePlc)
ON_COMMAND(ID_ELEMENTPLC_DEFINEPLC, &CMFCAppMultipleTopLevelDocumentsView::OnElementplcDefineplc)
ON_COMMAND(ID_ELEMENTPLC_CONNECTPLC, &CMFCAppMultipleTopLevelDocumentsView::OnElementplcConnectplc)
ON_COMMAND(ID_ELEMENTPLC_DISCONNECTPLC1, &CMFCAppMultipleTopLevelDocumentsView::OnElementplcDisconnectplc1)
ON_COMMAND(ID_ELEMENTPLC_DELETEPLC, &CMFCAppMultipleTopLevelDocumentsView::OnElementplcDeleteplc)
ON_COMMAND(ID_ELEMENTPLC_STARTPLCLIFEGUARD, &CMFCAppMultipleTopLevelDocumentsView::OnElementplcStartplclifeguard)
ON_MESSAGE(WM_REFRESHPICTURE, &CMFCAppMultipleTopLevelDocumentsView::RefreshMainWindow)
//ON_WM_ACTIVATE()
ON_COMMAND(ID_ELEMENTPLC_STOPPLCLIFEGUARD, &CMFCAppMultipleTopLevelDocumentsView::OnElementplcStopplclifeguard)
ON_COMMAND(ID_ELEMENTPLC_READITEM, &CMFCAppMultipleTopLevelDocumentsView::OnElementplcReaditem)
ON_COMMAND(ID_NOELEMENT_ADDVOLTMETER, &CMFCAppMultipleTopLevelDocumentsView::OnAddvoltmeter)
ON_COMMAND(ID_ELEMENT_DEFINEELEMENT, &CMFCAppMultipleTopLevelDocumentsView::OnElementDefineelement)

ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CMFCAppMultipleTopLevelDocumentsView construction/destruction

CMFCAppMultipleTopLevelDocumentsView::CMFCAppMultipleTopLevelDocumentsView() 
	: m_FirstPoint(0)
	, m_LastPoint(0)
	, m_PenWidth(0)
	, height(0)
	, width(0)
{
	// TODO: add construction code here
	m_iGridStepX = 50;
	m_iGridStepY = 50;
	SetScrollSizes(MM_TEXT, DocSize, CSize{ 500,500 }, CSize{ 20,20 });


}

CMFCAppMultipleTopLevelDocumentsView::~CMFCAppMultipleTopLevelDocumentsView()
{
}

BOOL CMFCAppMultipleTopLevelDocumentsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCAppMultipleTopLevelDocumentsView drawing

void CMFCAppMultipleTopLevelDocumentsView::OnDraw(CDC* pDC)
{
	CMFCAppMultipleTopLevelDocumentsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	HWND hObjectHandle;
	hObjectHandle = GetSafeHwnd();
	CRect * pRect = new CRect{ 0,0, DocSize.cx, DocSize.cy };
	MainGrid.Draw(pDC, this, 50, 50, pRect);
	
	//pDoc->TestSwitch.Draw(pDC, this, { 300, 300 }, 50, 50, pRect);
	//if (pCSwitchRaw != nullptr) pCSwitchRaw->Draw(pDC, this, {0,0} , 50, 50, pRect);
	/*if (NULL != m_brushBack.GetSafeHandle())
		m_brushBack.DeleteObject();
	if (NULL != m_bmpBack.GetSafeHandle())
		m_bmpBack.DeleteObject();

	BOOL bRet = m_bmpBack.LoadBitmap(IDB_BITMAP_TRAM);
	if (bRet)
		bRet = m_brushBack.CreatePatternBrush(&m_bmpBack);
	CClientDC aDC{ this };
	((CScrollView*)this)->OnPrepareDC(&aDC);
	//CRect rcClient(0, 0, 200, 354);
	RECT rcClient{ 0, 0, 200, 354 };
	//GetClientRect(rcClient);
	aDC.LPtoDP(&rcClient);
	pDC->SelectObject(&m_brushBack);
	//pDC->PatBlt(0, 0, 200, 354, PATCOPY);
	pDC->PatBlt(0, 0, rcClient.right, rcClient.bottom, PATCOPY);
	*/
	pDoc->DrawElements(pDC, this, { 0,0 }, 50, 50, pRect, hObjectHandle);
	/*
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 255));
	CPoint ptScroll = this->GetScrollPosition();
	pDC->TextOut(ptScroll.x + 10, ptScroll.y + 10, CString(_T("Tango Ostrava.")));
	*/
	
	//DrawText(); PolyBezier(); Arc();

	/*
	//MainGrid.Draw(pDC, this);
	CPoint * startPos;
	CBrush OrigBrush;
	CBrush * pTempBrush = nullptr;
	
	startPos = new CPoint;
	*startPos = pDC->MoveTo(50, 50);
	pDC->LineTo(100, 100);

	CPen aPen;
	aPen.CreatePen(PS_DASH,2, RGB(200, 0, 200));
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	pDC->MoveTo(*startPos);
	pDC->LineTo(30, 60);
	CBrush brush1(HS_VERTICAL, RGB(200,0,0));
	pTempBrush = (CBrush*)pDC->SelectObject(&brush1);
	OrigBrush.FromHandle((HBRUSH)pTempBrush);
	pDC->Ellipse(200, 200, 400, 400);
	pTempBrush = (CBrush*)pDC->SelectObject(pTempBrush);
	pDC->Ellipse(400, 400, 600, 600);
	pDC->SelectObject(pOldPen);
	pDC->LineTo(130, 160);
	CClientDC aDC{ this };
	aDC.SetROP2(R2_NOTXORPEN);

	pDC->MoveTo(m_FirstPoint);
	pDC->LineTo(m_LastPoint);

	CString szFilename("C:\\switchOpen.bmp");
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL, szFilename,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	CBitmap bmp;
	bmp.Attach(hBmp);

	CClientDC dc(this);
	CDC bmDC;
	bmDC.CreateCompatibleDC(&dc);
	CBitmap *pOldbmp = bmDC.SelectObject(&bmp);

	BITMAP  bi;
	bmp.GetBitmap(&bi);
	
	//dc.StretchBlt(0, 0, theApp.PicWidth, theApp.PicHeight, &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	
	OnPrepareDC(&aDC);
	RECT point{100, 100, 150, 150};
	aDC.LPtoDP(&point);
	dc.StretchBlt(point.left, point.top, (point.right-point.left), (point.bottom-point.top), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	point={ 150, 100, 200, 150 };
	aDC.LPtoDP(&point);
	dc.StretchBlt(point.left, point.top, (point.right - point.left), (point.bottom - point.top), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	bmp.Detach();
	szFilename=("C:\\switchClosed.bmp");
	hBmp = (HBITMAP)::LoadImage(NULL, szFilename,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	bmp.Attach(hBmp);
	bmDC.SelectObject(&bmp);
	point = { 200, 100, 250, 150 };
	aDC.LPtoDP(&point);
	bmp.GetBitmap(&bi);
	dc.StretchBlt(point.left, point.top, (point.right - point.left), (point.bottom - point.top), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);

	//dc.StretchBlt(100, 100, 50, 50, &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	//dc.BitBlt(0, 0, bi.bmWidth, bi.bmHeight, &bmDC, 0, 0, SRCCOPY);
	

	bmDC.SelectObject(pOldbmp);

	
	*/

}


// CMFCAppMultipleTopLevelDocumentsView printing


void CMFCAppMultipleTopLevelDocumentsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCAppMultipleTopLevelDocumentsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCAppMultipleTopLevelDocumentsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCAppMultipleTopLevelDocumentsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

//void CMFCAppMultipleTopLevelDocumentsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
//{
//	ClientToScreen(&point);
//	OnContextMenu(this, point);
//}

void CMFCAppMultipleTopLevelDocumentsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
    
	CMenu menu;
	INT submenu;
	VERIFY(menu.LoadMenu(IDR_CONTEXT_MENU)); // Load the context menu

	
	

	//CMenu* pContext{ menu.GetSubMenu(m_pSelected ? 0 : 1) };
	CString typeOfelement;
	if (m_pSelected == nullptr)
	{		
		submenu = 0;
	} 
	else
	{
		m_pSelected->getTypeOfElement(typeOfelement);
		if (typeOfelement == "CPlc")
		{
			submenu = 1;
			
			std::shared_ptr<CElement> m_pPlcSelected(m_pSelected);
		}
		else
		{
			submenu = 2;
		}
	}
	
	CMenu* pContext = menu.GetSubMenu(submenu);
	ASSERT(pContext != nullptr); // Ensure it's there
	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x + 10 , point.y + 10, this);

#endif
}


// CMFCAppMultipleTopLevelDocumentsView diagnostics

#ifdef _DEBUG
void CMFCAppMultipleTopLevelDocumentsView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCAppMultipleTopLevelDocumentsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCAppMultipleTopLevelDocumentsDoc* CMFCAppMultipleTopLevelDocumentsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCAppMultipleTopLevelDocumentsDoc)));
	return (CMFCAppMultipleTopLevelDocumentsDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCAppMultipleTopLevelDocumentsView message handlers



void CMFCAppMultipleTopLevelDocumentsView::OnInitialUpdate() {
	//CView::OnInitialUpdate();
	CScrollView::OnInitialUpdate();
	//CMFCAppMultipleTopLevelDocumentsDoc* pDoc = GetDocument();
	pDoc = GetDocument();
	//GetSystemMetrics
	// Set mapping mode and document size

	this->SetScrollSizes(MM_TEXT, DocSize, CSize{ 500,500 }, CSize{ 20,20 });
	/*
	p_Dlg = new CDialog;   // a CDialog derived class
	p_Dlg->Create(IDD_DIALOG1, this);
	p_Dlg->ShowWindow(SW_SHOW);
	*/
}
/*
void CMFCAppMultipleTopLevelDocumentsView::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	MessageBox(NULL,  L"Ahoj", MB_OK);
}
*/


void CMFCAppMultipleTopLevelDocumentsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
	/*CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&point); // Convert point to logical coordinates
	m_FirstPoint = point;
	SetCapture();*/
}


void CMFCAppMultipleTopLevelDocumentsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (this == GetCapture())
	{
		ReleaseCapture();
	}

	CView::OnLButtonUp(nFlags, point);
	//MessageBox(NULL, L"Ahoj", MB_OK);
	m_LastPoint = point;
	CRect rectangle;
	rectangle = { m_FirstPoint, m_LastPoint };
	rectangle.NormalizeRect();
	rectangle.InflateRect(2,2);
	InvalidateRect(nullptr);
	UpdateWindow();
}


void CMFCAppMultipleTopLevelDocumentsView::OnMove(int x, int y)
{
	CView::OnMove(x, y);

	// TODO: Add your message handler code here
}


void CMFCAppMultipleTopLevelDocumentsView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_point = point;
	CView::OnMouseMove(nFlags, point);
	CClientDC aDC{ this };
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&point); // Convert point to logical coordinates
	if (nFlags & MK_LBUTTON)
	{
		m_LastPoint = point;
		CRect rectangle;
		rectangle = { m_FirstPoint, m_LastPoint };
		rectangle.NormalizeRect();
		rectangle.InflateRect(2, 2);
		//InvalidateRect(&rectangle);
		InvalidateRect(nullptr);
		UpdateWindow();
	}
	else
	{
		// We are not creating an element, so select an element
		m_pSelected = GetDocument()->FindElement(point);
	}
}



void CMFCAppMultipleTopLevelDocumentsView::OnBnClickedMfcbutton1()
{
	// TODO: Add your control notification handler code here
	MessageBox(NULL, L"AhojAhoj", MB_OK);
}






void CMFCAppMultipleTopLevelDocumentsView::OnAddswitch()
{
	// TODO: Add your command handler code here
	
	CPoint point;

	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&m_point); // Convert point to logical coordinates

	point.x = m_point.x - (m_point.x % m_iGridStepX);
	point.y = m_point.y - (m_point.y % m_iGridStepY);

	//std::shared_ptr<CElement> pCSwitch{ new CSwitch(point) };
	//GetDocument()->AddElement(pCSwitch);
	GetDocument()->AddElementSwitch(point);
	InvalidateRect(nullptr);
	UpdateWindow();
}

void CMFCAppMultipleTopLevelDocumentsView::OnAddbulb()
{
	// TODO: Add your command handler code here
	CPoint point;

	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&m_point); // Convert point to logical coordinates

	point.x = m_point.x - (m_point.x % m_iGridStepX);
	point.y = m_point.y - (m_point.y % m_iGridStepY);

	GetDocument()->AddElementBulb(point);
	InvalidateRect(nullptr);
	UpdateWindow();
}

void CMFCAppMultipleTopLevelDocumentsView::OnMenuAddPlc()
{
	// TODO: Add your command handler code here
	CPoint point;

	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&m_point); // Convert point to logical coordinates

	point.x = m_point.x - (m_point.x % m_iGridStepX);
	point.y = m_point.y - (m_point.y % m_iGridStepY);

	HWND hObjectHandle;
	hObjectHandle = GetSafeHwnd();
	GetDocument()->AddElementPlc(point);
	InvalidateRect(nullptr);
	UpdateWindow();
}

void CMFCAppMultipleTopLevelDocumentsView::OnElementDelete()
{
	// TODO: Add your command handler code here
	CPoint point;

	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&m_point); // Convert point to logical coordinates

	point.x = m_point.x - (m_point.x % m_iGridStepX);
	point.y = m_point.y - (m_point.y % m_iGridStepY);

	GetDocument()->DeleteElement(point);
	InvalidateRect(nullptr);
	UpdateWindow();

}


void CMFCAppMultipleTopLevelDocumentsView::OnElementSwitchoff()
{
	// TODO: Add your command handler code here
	CPoint point;

	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&m_point); // Convert point to logical coordinates

	point.x = m_point.x - (m_point.x % m_iGridStepX);
	point.y = m_point.y - (m_point.y % m_iGridStepY);
	GetDocument()->OnElementSwitch(point, 1);
	InvalidateRect(nullptr);
	UpdateWindow();
}


void CMFCAppMultipleTopLevelDocumentsView::OnElementSwitchon()
{
	// TODO: Add your command handler code here
	CPoint point;

	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&m_point); // Convert point to logical coordinates

	point.x = m_point.x - (m_point.x % m_iGridStepX);
	point.y = m_point.y - (m_point.y % m_iGridStepY);
	GetDocument()->OnElementSwitch(point, 2);
	InvalidateRect(nullptr);
	UpdateWindow();
}





void CMFCAppMultipleTopLevelDocumentsView::OnLoadElements()
{
	// TODO: Add your command handler code here
	CString fileName;
	UINT nIDSTitle;
	DWORD lFlags;
	BOOL bOpenFileDialog = true;

	AfxGetApp()->DoPromptFileName(fileName, AFX_IDS_APP_TITLE,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL);
	
	CFile theFile;
	theFile.Open(fileName, CFile::modeRead | CFile::shareExclusive);
	CArchive archive(&theFile, CArchive::load);
	size_t elementCount{}; // Count of number of elements
	archive >> elementCount; // retrieve the element count
	CElement* pElement;
	for (size_t i{}; i < elementCount; ++i)
	{
		archive >> pElement;
		pDoc->m_Sketch.push_back(std::shared_ptr<CElement>(pElement));
		pElement->setmSketch(pDoc->m_Sketch);
	}

	archive.Close();
	theFile.Close();
	InvalidateRect(nullptr);
	UpdateWindow();
}


void CMFCAppMultipleTopLevelDocumentsView::OnFileStoreElements()
{
	// TODO: Add your command handler code here
	CString fileName;
	UINT nIDSTitle;
	DWORD lFlags;
	BOOL bOpenFileDialog = true;

	AfxGetApp()->DoPromptFileName(fileName, AFX_IDS_APP_TITLE,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, FALSE, NULL);

	CFile theFile;
	theFile.Open(fileName, CFile::modeWrite | CFile::shareExclusive);
	CArchive archive(&theFile, CArchive::store);

	archive << pDoc->m_Sketch.size();
	for (const auto& pElement : pDoc->m_Sketch)
		archive << pElement.get();

	archive.Close();
	theFile.Close();
	InvalidateRect(nullptr);
	UpdateWindow();
}






void CMFCAppMultipleTopLevelDocumentsView::OnElementplcDefineplc()
{
	// TODO: Add your command handler code here
	CPlcDialog *aDlg;
	aDlg = new CPlcDialog(m_pSelected);
	aDlg->Create(IDD_DIALOG_PLC, this);
	aDlg->ShowWindow(SW_SHOW);

}



void CMFCAppMultipleTopLevelDocumentsView::OnElementplcConnectplc()
{
	// TODO: Add your command handler code here
	CString typeOfelement;
	m_pSelected->getTypeOfElement(typeOfelement);
	if (typeOfelement == "CPlc")
	{

		CPlc * pPlc = dynamic_cast<CPlc*>(m_pSelected.get());
		//progressBarStruct * pProgressBarPars;
		//pProgressBarPars = &progressBarPars;
		//pProgressBarPars->pParentInst = this;
		//pProgressBarPars->hWndParent = GetSafeHwnd();
		ConnectingToPlcDlg *aDlg;
		aDlg = new ConnectingToPlcDlg();
		aDlg->Create(IDD_DIALOGCONNECTINGPLC, 0);
		aDlg->ShowWindow(SW_SHOW);
		aDlg->SetWindowTextW(L"Connecting PLC, be patient, please. It may take up to 10 sec.");

		//aDlg->m_progCtrl.SetRange(0, 10000);
		//aDlg->runProgBar();
		pPlc->connect();
		aDlg->EndDialog(0);
	

	}
	InvalidateRect(nullptr);
	UpdateWindow();
}



void CMFCAppMultipleTopLevelDocumentsView::OnElementplcDisconnectplc1()
{
	// TODO: Add your command handler code here
	CString typeOfelement;
	m_pSelected->getTypeOfElement(typeOfelement);
	if (typeOfelement == "CPlc")
	{

		CPlc * pPlc = dynamic_cast<CPlc*>(m_pSelected.get());
		
		if (pPlc != nullptr)
		{
			pPlc->disconnect();

		}

	}
	InvalidateRect(nullptr);
	UpdateWindow();
}


void CMFCAppMultipleTopLevelDocumentsView::OnElementplcDeleteplc()
{
	// TODO: Add your command handler code here
	CPlc * pPlc = dynamic_cast<CPlc*>(m_pSelected.get());
	if (pPlc != nullptr)
	{
		if (pPlc->getState() == 0)
		{
			this->OnElementDelete();
		}
		else
		{
			AfxMessageBox(L"Unable to delete PLC. Not in correct state.");
		}
	}
}


void CMFCAppMultipleTopLevelDocumentsView::OnElementplcStartplclifeguard()
{
	// TODO: Add your command handler code here
	CString typeOfelement;
	m_pSelected->getTypeOfElement(typeOfelement);
	if (typeOfelement == "CPlc")
	{

		CPlc * pPlc = dynamic_cast<CPlc*>(m_pSelected.get());
		HWND hObjectHandle;
		hObjectHandle = GetSafeHwnd();
		pPlc->startLifeGuard(hObjectHandle);


	}
	InvalidateRect(nullptr);
	UpdateWindow();

}

LRESULT  CMFCAppMultipleTopLevelDocumentsView::RefreshMainWindow(WPARAM wParam, LPARAM lParam)
{
	if (wParam != 0)

	{
		ProgressBarDlg * ptrDlg = (ProgressBarDlg*)wParam;
		ptrDlg->EndDialog(0);
	}

	InvalidateRect(nullptr);
	UpdateWindow();
	return 0;
}





void CMFCAppMultipleTopLevelDocumentsView::OnElementplcStopplclifeguard()
{
	// TODO: Add your command handler code here
	CString typeOfelement;
	m_pSelected->getTypeOfElement(typeOfelement);
	if (typeOfelement == "CPlc")
	{

		CPlc * pPlc = dynamic_cast<CPlc*>(m_pSelected.get());
		HWND hObjectHandle;
		hObjectHandle = GetSafeHwnd();

		ProgressBarDlg * ptrDlg = new ProgressBarDlg();
		ptrDlg->Create(IDD_DIALOG_PROGRESSBAR, 0);
		ptrDlg->SetWindowTextW(L"LifeGuard stop pending...");
		ptrDlg->ShowWindow(SW_SHOW);
		ptrDlg->runProgBar(L"");
		pPlc->stopLifeGuard(hObjectHandle, ptrDlg);

		

	}
	InvalidateRect(nullptr);
	UpdateWindow();
}


void CMFCAppMultipleTopLevelDocumentsView::OnElementplcReaditem()
{
	// TODO: Add your command handler code here
	
	CPlcMASReadItemDlg *aDlg;
	aDlg = new CPlcMASReadItemDlg();
	aDlg->Create(IDD_DIALOGMASREADITEM, this);
	aDlg->ShowWindow(SW_SHOW);
	aDlg->setpPlc(m_pSelected);
	//m_pSelected
      
}




void CMFCAppMultipleTopLevelDocumentsView::OnAddvoltmeter()
{
	// TODO: Add your command handler code here
	CPoint point;

	CClientDC aDC{ this }; // Create a device context
	OnPrepareDC(&aDC); // Get origin adjusted
	aDC.DPtoLP(&m_point); // Convert point to logical coordinates

	point.x = m_point.x - (m_point.x % m_iGridStepX);
	point.y = m_point.y - (m_point.y % m_iGridStepY);

	GetDocument()->AddElementVltMtr(point);
	InvalidateRect(nullptr);
	UpdateWindow();
}


void CMFCAppMultipleTopLevelDocumentsView::OnElementDefineelement()
{
	// TODO: Add your command handler code here
	CElementDialog *aDlg;
	aDlg = new CElementDialog(m_pSelected);
	aDlg->Create(IDD_DIALOG_ELEMENT, this);
	aDlg->ShowWindow(SW_SHOW);
	InvalidateRect(nullptr);
	UpdateWindow();
}


//void CMFCAppMultipleTopLevelDocumentsView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: Add your message handler code here
//					   // Do not call CScrollView::OnPaint() for painting messages
//
//	dc.SetBkMode(TRANSPARENT);
//	dc.SetTextColor(RGB(255, 0, 255));
//	CPoint ptScroll = GetScrollPosition();
//	dc.TextOut(20, 20, CString(_T("pokus")));
//	//DrawText(); PolyBezier(); Arc();
//}


void CMFCAppMultipleTopLevelDocumentsView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMFCAppMultipleTopLevelDocumentsView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMFCAppMultipleTopLevelDocumentsView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// This feature requires Windows Vista or greater.
	// The symbol _WIN32_WINNT must be >= 0x0600.
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);
	CScrollView::OnMouseHWheel(nFlags, zDelta, pt);
}


BOOL CMFCAppMultipleTopLevelDocumentsView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(FALSE);
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}
