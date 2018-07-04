// DemoView.cpp : implementation of the CDemoView class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "DemoView.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CImageView)

BEGIN_MESSAGE_MAP(CDemoView, CImageView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
   ON_COMMAND(ID_IMAGE_FITWIDTH, OnImageFitWidth)
   ON_COMMAND(ID_IMAGE_FITWINDOW, OnImageFitWindow)
   ON_COMMAND(ID_IMAGE_ORIGINALSIZE, OnImageOriginalSize)
   ON_COMMAND(ID_IMAGE_ZOOMIN, OnImageZoomIn)
   ON_COMMAND(ID_IMAGE_ZOOMOUT, OnImageZoomOut)
   ON_COMMAND(ID_OVERLAY_SHOWDIGGER, OnOverlayShowdigger)
   ON_COMMAND(ID_OVERLAY_SHOWTEXT, OnOverlayShowtext)
   ON_COMMAND(ID_OVERLAY_ANIMATEDIGGER, OnOverlayAnimatedigger)
   ON_UPDATE_COMMAND_UI(ID_OVERLAY_ANIMATEDIGGER, OnUpdateOverlayAnimatedigger)
   ON_UPDATE_COMMAND_UI(ID_OVERLAY_SHOWDIGGER, OnUpdateOverlayShowdigger)
   ON_UPDATE_COMMAND_UI(ID_OVERLAY_SHOWTEXT, OnUpdateOverlayShowtext)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction
   BOOL m_bShowDigger;
   BOOL m_bShowText;
   BOOL m_bAnimateDigger;

CDemoView::CDemoView() 
   : m_nDigger(0),
     m_bShowDigger(TRUE),
     m_bShowText(TRUE),
     m_bAnimateDigger(TRUE)
{
   SetBackPatternBrush(IDB_BACKGROUND);
   SetHandCursor(IDC_CURSOR_HAND);
   SetHandDragCursor(IDC_CURSOR_HANDDRAG);

   VERIFY(m_bmpDigger0.LoadBitmap(IDB_BITMAP0));
   VERIFY(m_bmpDigger1.LoadBitmap(IDB_BITMAP1));
   VERIFY(m_bmpDigger2.LoadBitmap(IDB_BITMAP2));
   VERIFY(m_bmpDigger3.LoadBitmap(IDB_BITMAP3));
   VERIFY(m_bmpDigger4.LoadBitmap(IDB_BITMAP4));
   VERIFY(m_bmpDigger5.LoadBitmap(IDB_BITMAP5));
   VERIFY(m_bmpDigger6.LoadBitmap(IDB_BITMAP6));
   VERIFY(m_bmpDigger7.LoadBitmap(IDB_BITMAP7));
   VERIFY(m_bmpDigger8.LoadBitmap(IDB_BITMAP8));
   VERIFY(m_bmpDigger9.LoadBitmap(IDB_BITMAP9));

   m_pbmpDigger = &m_bmpDigger0;
   BITMAP bmp = {0};
   m_pbmpDigger->GetBitmap(&bmp);
   m_rcDigger.SetRect(10, 10, bmp.bmWidth + 10, bmp.bmHeight + 10);
}

CDemoView::~CDemoView()
{
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CImageView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
   CImageView::OnDraw(pDC);
}

void CDemoView::DrawOverlay(CMemDC* pDCDraw, CDC* pDCView)
{
   // draw demo digger
   if(m_bShowDigger)
   {
      CMemDC dcSource(pDCView, m_pbmpDigger);
      pDCDraw->BitBlt(m_rcDigger.left, m_rcDigger.top, m_rcDigger.Width(), m_rcDigger.Height(), 
         &dcSource, 0, 0, SRCCOPY);
   }

   // draw demo text
   if(m_bShowText)
   {
      CRect rcClient(0, 0, 0, 0);
      GetClientRect(rcClient);
      
      pDCDraw->SetBkMode(TRANSPARENT);
      const int x = rcClient.left + 10;
      const int y = rcClient.bottom - 25;
      CString strText = _T("FOR YOUR HEALTH, DIG EVERYDAY!");

      pDCDraw->SetTextColor(RGB(0, 0, 0));
      pDCDraw->TextOut(x + 1, y + 1, strText);

      pDCDraw->SetTextColor(RGB(255, 255, 255));
      pDCDraw->TextOut(x, y, strText);
   }

}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CImageView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CImageView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

void CDemoView::OnInitialUpdate() 
{
	CImageView::OnInitialUpdate();
	
	SetTimer(0, 200, NULL);
	
}

void CDemoView::OnTimer(UINT nIDEvent) 
{
   if(! m_bAnimateDigger || ! m_bShowDigger)
      return;

   ++m_nDigger;
   
	switch(m_nDigger)
   {
   case 0:
      m_pbmpDigger = &m_bmpDigger0;
      break;
   case 1:
      m_pbmpDigger = &m_bmpDigger1;
      break;
   case 2:
      m_pbmpDigger = &m_bmpDigger2;
      break;
   case 3:
      m_pbmpDigger = &m_bmpDigger3;
      break;
   case 4:
      m_pbmpDigger = &m_bmpDigger4;
      break;
   case 5:
      m_pbmpDigger = &m_bmpDigger5;
      break;
   case 6:
      m_pbmpDigger = &m_bmpDigger6;
      break;
   case 7:
      m_pbmpDigger = &m_bmpDigger7;
      break;
   case 8:
      m_pbmpDigger = &m_bmpDigger8;
      break;
   case 9:
      m_pbmpDigger = &m_bmpDigger9;
      break;
   default:
      m_nDigger = 0;
      m_pbmpDigger = &m_bmpDigger0;
      break;
   }
   InvalidateRect(m_rcDigger);
	
	CImageView::OnTimer(nIDEvent);
}

void CDemoView::OnImageFitWidth()
{
   ZoomToWindowWidth();
}

void CDemoView::OnImageFitWindow()
{
   ZoomToWindow();
}

void CDemoView::OnImageOriginalSize()
{
   ZoomToOriginalSize();
}

void CDemoView::OnImageZoomIn()
{
   ZoomIn();
}

void CDemoView::OnImageZoomOut()
{
   ZoomOut();
}


void CDemoView::OnOverlayShowdigger()
{
   m_bShowDigger = !m_bShowDigger;
   InvalidateRect(m_rcDigger);
}

void CDemoView::OnOverlayShowtext()
{
   m_bShowText = !m_bShowText;
   Invalidate();
}

void CDemoView::OnOverlayAnimatedigger()
{
   m_bAnimateDigger = !m_bAnimateDigger;
}

void CDemoView::OnUpdateOverlayShowdigger(CCmdUI *pCmdUI)
{
   pCmdUI->SetCheck(m_bShowDigger);
}

void CDemoView::OnUpdateOverlayShowtext(CCmdUI *pCmdUI)
{
   pCmdUI->SetCheck(m_bShowText);
}

void CDemoView::OnUpdateOverlayAnimatedigger(CCmdUI *pCmdUI)
{
   pCmdUI->SetCheck(m_bAnimateDigger);
}
