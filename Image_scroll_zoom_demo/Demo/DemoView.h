// DemoView.h : interface of the CDemoView class
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

#include "ImageView.h"

class CDemoView : public CImageView
{
protected: // create from serialization only
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

// Attributes
private:
	CBitmap m_bmpDigger0;
   CBitmap m_bmpDigger1;
   CBitmap m_bmpDigger2;
   CBitmap m_bmpDigger3;
   CBitmap m_bmpDigger4;
   CBitmap m_bmpDigger5;
   CBitmap m_bmpDigger6;
   CBitmap m_bmpDigger7;
   CBitmap m_bmpDigger8;
   CBitmap m_bmpDigger9;

   CBitmap* m_pbmpDigger;
   CRect m_rcDigger;
   int m_nDigger;

   BOOL m_bShowDigger;
   BOOL m_bShowText;
   BOOL m_bAnimateDigger;

// Operations
public:
   CDemoDoc* GetDocument();

// Overrides
protected:
   virtual void DrawOverlay(CMemDC* pDCDraw, CDC* pDCView);
   

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoView)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnImageFitWidth();
   afx_msg void OnImageFitWindow();
   afx_msg void OnImageOriginalSize();
   afx_msg void OnImageZoomIn();
   afx_msg void OnImageZoomOut();
   afx_msg void OnOverlayShowdigger();
   afx_msg void OnOverlayShowtext();
   afx_msg void OnOverlayAnimatedigger();
   afx_msg void OnUpdateOverlayAnimatedigger(CCmdUI *pCmdUI);
   afx_msg void OnUpdateOverlayShowdigger(CCmdUI *pCmdUI);
   afx_msg void OnUpdateOverlayShowtext(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in DemoView.cpp
inline CDemoDoc* CDemoView::GetDocument()
   { return (CDemoDoc*)m_pDocument; }
#endif
