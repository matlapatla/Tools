// ImageView.cpp : implementation file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "ImageView.h"
#include "MemDC.h"
#include "ImageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageView

IMPLEMENT_DYNAMIC(CImageView, CScrollView)

CImageView::CImageView()
   : m_fZoom(1.0),
     m_fZoomStep(0.1),
     m_fMinZoom(0.2),
     m_fMaxZoom(5.0)
{
   SetBackSolidBrush(::GetSysColor(COLOR_APPWORKSPACE));

}

CImageView::~CImageView()
{

}

BOOL CImageView::SetBackPatternBrush(UINT nBitmapResID)
{
   if(NULL != m_brushBack.GetSafeHandle())
      m_brushBack.DeleteObject();
   if(NULL != m_bmpBack.GetSafeHandle())
      m_bmpBack.DeleteObject();
   
   BOOL bRet = m_bmpBack.LoadBitmap(nBitmapResID);
   if(bRet)
      bRet = m_brushBack.CreatePatternBrush(&m_bmpBack);

   if(NULL != m_hWnd)
      Invalidate();
   
   return bRet;
}

BOOL CImageView::SetBackSolidBrush(COLORREF crColor)
{
   if(NULL != m_brushBack.GetSafeHandle())
      m_brushBack.DeleteObject();
   if(NULL != m_bmpBack.GetSafeHandle())
      m_bmpBack.DeleteObject();

   BOOL bRet = m_brushBack.CreateSolidBrush(crColor);

   if(NULL != m_hWnd)
      Invalidate();
   
   return bRet;
}

void CImageView::SetHandCursor(UINT nCursorResID)
{
   CWinApp* pApp = AfxGetApp();
   m_hCursorHand = pApp->LoadCursor(nCursorResID);
}

void CImageView::SetHandDragCursor(UINT nCursorResID)
{
   CWinApp* pApp = AfxGetApp();
   m_hCursorHandDrag = pApp->LoadCursor(nCursorResID);
}

void CImageView::_SetScrollSizes()
{
	CImageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

   CSize sizeView(100, 100);
   if(pDoc->IsValidImage())
   {
      CSize sizeImage = pDoc->GetImageSize();
      sizeView.cx = (int)(sizeImage.cx * m_fZoom);
      sizeView.cy = (int)(sizeImage.cy * m_fZoom);
   }

   SetScrollSizes(MM_TEXT, sizeView);
}

void CImageView::ZoomIn()
{
   m_fZoom += m_fZoomStep;
   if(m_fZoom > m_fMaxZoom)
   {
      m_fZoom = m_fMaxZoom;
   }

   _SetScrollSizes();
   Invalidate(TRUE);
}
void CImageView::ZoomOut()
{
   m_fZoom -= m_fZoomStep;
   if(m_fZoom < m_fMinZoom)
   {
      m_fZoom = m_fMinZoom;
   }

   _SetScrollSizes();
   Invalidate();
}

void CImageView::ZoomToOriginalSize()
{
	m_fZoom = 1.0;

   _SetScrollSizes();
   SetScrollPos(SB_HORZ, 0, FALSE);
   SetScrollPos(SB_VERT, 0, FALSE);
   Invalidate();
}

void CImageView::ZoomToWindowWidth()
{
   CImageDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   CSize size = pDoc->GetImageSize();
   CRect rcClient(0, 0, 0, 0);
   GetClientRect(rcClient);

   const int bx = size.cx;        // source bitmap width
   const int cx = rcClient.right; // view client width
   if(bx > 10 && cx > 10)
   {
      m_fZoom = (double)cx / bx;
      _SetScrollSizes();
      Invalidate();
   }
}
void CImageView::ZoomToWindow()
{
   CImageDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   CSize size = pDoc->GetImageSize();
   CRect rcClient(0, 0, 0, 0);
   GetClientRect(rcClient);

   const int bx = size.cx;             // source bitmap width
   const int by = size.cy;             // source bitmap height
   const int cx = rcClient.Width();    // view client width
   const int cy = rcClient.Height();   // view client height
   const double fx = (double)cx / bx;  // horizontal sizes ratio
   const double fy = (double)cy / by;  // vertical sizes ratio

   if(bx > 10 && by > 10 && cx > 10 && cy > 10)
   {
      if(fx < fy)
      {
         m_fZoom = fx;
      }
      else 
      {
         m_fZoom = fy;
      }
      _SetScrollSizes();
      Invalidate();
   }
}

void CImageView::ZoomToRectangle(const CRect& rect)
{
   // NOTE: Override this method in order to change the default.

   CImageDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   CSize size = pDoc->GetImageSize();
   CRect rcClient(0, 0, 0, 0);
   GetClientRect(rcClient);

   CPoint ptOld = GetScrollPosition();

   const int bx = size.cx;             // original bitmap width
   const int by = size.cy;             // original bitmap height 
   const int cx = rcClient.Width();    // view client width
   const int cy = rcClient.Height();   // view client height
   const int sx = rect.Width();        // view client height
   const int xPos = ptOld.x;           // scroll horizontal position
   const int yPos = ptOld.y;           // scroll vertical position
   const int vx = (int)(bx * m_fZoom); // virtual view width 
   const int vy = (int)(by * m_fZoom); // virtual view height

   double fx = (double) cx / sx;
   m_fZoom *= fx;

   CPoint ptNew(0, 0);
   if(vx > cx)
   {
      ptNew.x = (int)((xPos + rect.left) * fx);
      
   }
   else
   {
      ptNew.x = (int)((rect.left - (cx - vx) / 2) * fx);

   }
   
   if(vy > cy)
   {
      ptNew.y = (int)((yPos + rect.top) * fx);
   }
   else
   {
      ptNew.y = (int)((rect.top - (cy - vy) / 2) * fx);
   }
   _SetScrollSizes();
   ScrollToPosition(ptNew);
   
   Invalidate();
}

void CImageView::_HandDrag(CPoint point)
{

   ::SetCursor(m_hCursorHandDrag);

   DWORD dwStyle = GetStyle();

   if((WS_HSCROLL & dwStyle) || (WS_VSCROLL & dwStyle))
   {
      const int dmin = 2;
      CPoint ptScrollPos = GetScrollPosition();
      CSize ptDocSize = GetTotalSize();
      if(WS_HSCROLL & dwStyle)
      {
         const int dx = point.x - m_ptCurrDrag.x;
         if((dx > dmin) || (dx < dmin))
         {
            const int x = max(0, (min((ptScrollPos.x - point.x + m_ptCurrDrag.x), ptDocSize.cx)));
            SetScrollPos(SB_HORZ, x, FALSE);
            Invalidate(FALSE);
         }
      }
      if(WS_VSCROLL & dwStyle)
      {
         const int dy = point.y - m_ptCurrDrag.y;
         if((dy > dmin) || (dy < -dmin))
         {
            const int y = max(0, (min((ptScrollPos.y - point.y + m_ptCurrDrag.y), ptDocSize.cy)));
            SetScrollPos(SB_VERT, y, FALSE);
            Invalidate(FALSE);
         }
      }
   }
   m_ptCurrDrag = point;
}

void CImageView::_SelectRectangle(CPoint point)
{
   CClientDC dc(this);
   const int nSavedDC = dc.SaveDC();

   dc.SetROP2(R2_NOT);
   dc.SelectStockObject(NULL_BRUSH);

   // remove old selection
   CRect rcOld(m_ptStartDrag, m_ptCurrDrag);
   rcOld.NormalizeRect();
   dc.Rectangle(rcOld);

   // draw new selection
   CRect rcNew(m_ptStartDrag, point);
   rcNew.NormalizeRect();
   dc.Rectangle(rcNew);

   dc.RestoreDC(nSavedDC);
   m_ptCurrDrag = point;
}

BEGIN_MESSAGE_MAP(CImageView, CScrollView)
	//{{AFX_MSG_MAP(CImageView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
   ON_WM_MOUSEWHEEL()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_RBUTTONDOWN()
   ON_WM_RBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageView drawing

void CImageView::OnDraw(CDC* pDCView)
{
   ASSERT(MM_TEXT == pDCView->GetMapMode());
   ASSERT(CPoint(0, 0) == pDCView->GetViewportOrg());

   CRect rcClient(0, 0, 0, 0);
   GetClientRect(rcClient);
   const int cx = rcClient.right;  // view client area width
   const int cy = rcClient.bottom; // view client area height

   CMemDC dcDraw(pDCView, cx, cy);
   DrawBackgound(&dcDraw);
   DrawImage(&dcDraw, pDCView);
   DrawOverlay(&dcDraw, pDCView);
   
   CRect rcClip(0, 0, 0, 0);
   pDCView->GetClipBox(rcClip);
   pDCView->BitBlt(rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), 
      &dcDraw, 
      rcClip.left, rcClip.top, 
      SRCCOPY);
}

void CImageView::DrawBackgound(CMemDC* pDCDraw)
{
   ASSERT_VALID(pDCDraw);
   ASSERT(NULL != m_brushBack.GetSafeHandle());

   CRect rcClient(0, 0, 0, 0);
   GetClientRect(rcClient);
   pDCDraw->SelectObject(&m_brushBack);
   pDCDraw->PatBlt(0, 0, rcClient.right, rcClient.bottom, PATCOPY);
}

void CImageView::DrawImage(CMemDC* pDCDraw, CDC* pDCView)
{
   ASSERT_VALID(pDCDraw);
   CImageDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);
   if(!pDoc->IsValidImage())
      return;

   CSize size = pDoc->GetImageSize();
   CPoint point = GetScrollPosition();

   CRect rcClient(0, 0, 0, 0);
   GetClientRect(rcClient);

   const int cx = rcClient.right;      // view client area width
   const int cy = rcClient.bottom;     // view client area height
   const int bx = size.cx;             // source bitmap width
   const int by = size.cy;             // source bitmap height
   const int vx = (int)(bx * m_fZoom); // virtual document width
   const int vy = (int)(by * m_fZoom); // virtual document height
   const int xPos = point.x;           // horizontal scroll position
   const int yPos = point.y;           // vertical scroll position

   // source and destination cordinates and sizes
   int xSrc, ySrc, nSrcWidth, nSrcHeight, xDst, yDst, nDstWidth, nDstHeight;
   

   if(vx > cx)
   {
      xSrc = (int)(xPos / m_fZoom);
      nSrcWidth = bx - xSrc;
      xDst = 0;
      nDstWidth = vx - xPos;
   }
   else 
   {
      xSrc = 0;
      nSrcWidth = bx;
      xDst = cx / 2 - vx / 2;
      nDstWidth = vx;
   }

   if(vy > cy)
   {
      ySrc = (int)(yPos / m_fZoom);
      nSrcHeight = by - ySrc;
      yDst = 0;
      nDstHeight = vy - yPos;
   }
   else 
   {
      ySrc = 0;
      nSrcHeight = by;
      yDst = cy / 2 - vy / 2;
      nDstHeight = vy;
   }

   CBitmap& bmpImage = pDoc->GetImage();
   CMemDC dcSource(pDCView, &bmpImage);
   pDCDraw->SetStretchBltMode(HALFTONE);
   pDCDraw->StretchBlt(xDst, yDst, nDstWidth, nDstHeight, &dcSource, xSrc, ySrc, nSrcWidth, nSrcHeight, SRCCOPY); 
}

/////////////////////////////////////////////////////////////////////////////
// CImageView diagnostics

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageDoc* CImageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageDoc)));
	return (CImageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageView message handlers

BOOL CImageView::OnEraseBkgnd(CDC* pDC) 
{
	// just prevent default processing
   // the background will be filled in OnDraw 
   return FALSE;
}

void CImageView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
   m_fZoom = 1.0;
   _SetScrollSizes();

	
}

BOOL CImageView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll) 
{
	int xOrig, x;
	int yOrig, y;

	// don't scroll if there is no valid scroll range (ie. no scroll bar)
	CScrollBar* pBar;
	DWORD dwStyle = GetStyle();
	pBar = GetScrollBarCtrl(SB_VERT);
	if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
		(pBar == NULL && !(dwStyle & WS_VSCROLL)))
	{
		// vertical scroll bar not enabled
		sizeScroll.cy = 0;
	}
	pBar = GetScrollBarCtrl(SB_HORZ);
	if ((pBar != NULL && !pBar->IsWindowEnabled()) ||
		(pBar == NULL && !(dwStyle & WS_HSCROLL)))
	{
		// horizontal scroll bar not enabled
		sizeScroll.cx = 0;
	}

	// adjust current x position
	xOrig = x = GetScrollPos(SB_HORZ);
	int xMax = GetScrollLimit(SB_HORZ);
	x += sizeScroll.cx;
	if (x < 0)
		x = 0;
	else if (x > xMax)
		x = xMax;

	// adjust current y position
	yOrig = y = GetScrollPos(SB_VERT);
	int yMax = GetScrollLimit(SB_VERT);
	y += sizeScroll.cy;
	if (y < 0)
		y = 0;
	else if (y > yMax)
		y = yMax;

	// did anything change?
	if (x == xOrig && y == yOrig)
		return FALSE;

	if (bDoScroll)
	{
		// do scroll and update scroll positions
		/// ScrollWindow(-(x-xOrig), -(y-yOrig)); // <-- removed
      Invalidate(); // <-- added // Invalidates whole client area
		if (x != xOrig)
			SetScrollPos(SB_HORZ, x);
		if (y != yOrig)
			SetScrollPos(SB_VERT, y);
	}
	return TRUE;
}

void CImageView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	CScrollView::OnPrepareDC(pDC, pInfo);
   pDC->SetMapMode(MM_TEXT);          // force map mode to MM_TEXT
   pDC->SetViewportOrg(CPoint(0, 0)); // force viewport origin to zero
}

BOOL CImageView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
   if(MK_CONTROL & nFlags)
   {
      if(zDelta > 0)
      {
         ZoomIn();
      }
      else
      {
         ZoomOut();
      }
      Invalidate();
      return FALSE;
   }
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
   ::SetCursor(m_hCursorHand);
   m_ptStartDrag = point;
   m_ptCurrDrag = point;
   CRect rcClient;
   GetClientRect(rcClient);
   ClientToScreen(rcClient);
   ::ClipCursor(rcClient);

   CScrollView::OnLButtonDown(nFlags, point);
}

void CImageView::OnLButtonUp(UINT nFlags, CPoint point)
{
   ::ClipCursor(NULL);
   CScrollView::OnLButtonUp(nFlags, point);
}

void CImageView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_ptStartDrag = point;
   m_ptCurrDrag = point;
   CRect rcClient;
   GetClientRect(rcClient);
   ClientToScreen(rcClient);
   ::ClipCursor(rcClient);

   CScrollView::OnRButtonDown(nFlags, point);
}

void CImageView::OnRButtonUp(UINT nFlags, CPoint point)
{
   ::ClipCursor(NULL);

   CClientDC dc(this);
   const int nSavedDC = dc.SaveDC();
   
   dc.SetROP2(R2_NOT);
   dc.SelectStockObject(NULL_BRUSH);
   
   CRect rcOld(m_ptStartDrag, m_ptCurrDrag);
   rcOld.NormalizeRect();
   dc.Rectangle(rcOld);

   CRect rcNew(m_ptStartDrag, point);
   rcNew.NormalizeRect();
   if(rcNew.Width() > 1, rcNew.Height() > 1)
   {
      ZoomToRectangle(rcNew);
   }
   
   dc.RestoreDC(nSavedDC);

   CScrollView::OnRButtonUp(nFlags, point);
}

void CImageView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(MK_LBUTTON & nFlags)
   {
      _HandDrag(point);
   }
   else if(MK_RBUTTON & nFlags)
   {
      _SelectRectangle(point);
   }

   CScrollView::OnMouseMove(nFlags, point);
}

void CImageView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
   ZoomToOriginalSize();
   CScrollView::OnLButtonDblClk(nFlags, point);
}
