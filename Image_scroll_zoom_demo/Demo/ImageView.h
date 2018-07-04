// ImageView.h : header file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CImageView view

class CMemDC;
class CImageDoc;
class CImageView : public CScrollView
{
   DECLARE_DYNAMIC(CImageView)

// Construction
protected:
	CImageView();
   virtual ~CImageView() = 0;

// Operations
public:
   CImageDoc* GetDocument();
   BOOL SetBackPatternBrush(UINT nBitmapResID);
   BOOL SetBackSolidBrush(COLORREF crColor);
   void SetHandCursor(UINT nCursorResID);
   void SetHandDragCursor(UINT nCursorResID);

   void ZoomIn();
   void ZoomOut();
   void ZoomToOriginalSize();
   void ZoomToWindowWidth();
   void ZoomToWindow();
   
// Overrides
protected:
   virtual void ZoomToRectangle(const CRect& rect);
   virtual void DrawBackgound(CMemDC* pDCDraw);
   virtual void DrawImage(CMemDC* pDCDraw, CDC* pDCView);
   virtual void DrawOverlay(CMemDC* pDCDraw, CDC* pDCView) = 0;

// Attributes
private:
   double m_fZoom;
   const double m_fZoomStep;
   const double m_fMaxZoom;
   const double m_fMinZoom;
   HCURSOR m_hCursorHand;
   HCURSOR m_hCursorHandDrag;
   CPoint m_ptStartDrag;
   CPoint m_ptCurrDrag;
   CBitmap m_bmpBack;
   CBrush m_brushBack;

// Implementation
private:
   void _SetScrollSizes();
   void _HandDrag(CPoint point);
   void _SelectRectangle(CPoint point);
   
   


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDCView); 
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);
	//}}AFX_VIRTUAL

// Implementation
protected:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in ImageView.cpp
inline CImageDoc* CImageView::GetDocument()
   { return (CImageDoc*)m_pDocument; }
#endif

