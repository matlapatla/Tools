
// MFCApplicationMultipleDocsView.cpp : implementation of the CMFCApplicationMultipleDocsView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplicationMultipleDocs.h"
#endif

#include "MFCApplicationMultipleDocsDoc.h"
#include "MFCApplicationMultipleDocsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationMultipleDocsView

IMPLEMENT_DYNCREATE(CMFCApplicationMultipleDocsView, CView)

BEGIN_MESSAGE_MAP(CMFCApplicationMultipleDocsView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplicationMultipleDocsView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCApplicationMultipleDocsView construction/destruction

CMFCApplicationMultipleDocsView::CMFCApplicationMultipleDocsView()
{
	// TODO: add construction code here

}

CMFCApplicationMultipleDocsView::~CMFCApplicationMultipleDocsView()
{
}

BOOL CMFCApplicationMultipleDocsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationMultipleDocsView drawing

void CMFCApplicationMultipleDocsView::OnDraw(CDC* /*pDC*/)
{
	CMFCApplicationMultipleDocsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCApplicationMultipleDocsView printing


void CMFCApplicationMultipleDocsView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplicationMultipleDocsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationMultipleDocsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplicationMultipleDocsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCApplicationMultipleDocsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplicationMultipleDocsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplicationMultipleDocsView diagnostics

#ifdef _DEBUG
void CMFCApplicationMultipleDocsView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationMultipleDocsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationMultipleDocsDoc* CMFCApplicationMultipleDocsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationMultipleDocsDoc)));
	return (CMFCApplicationMultipleDocsDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationMultipleDocsView message handlers
