
// MFCAppMultipleTopLevelDocumentsView.h : interface of the CMFCAppMultipleTopLevelDocumentsView class
//

#pragma once
#include "atltypes.h"
#include "CElement.h"
#include "CGrid.h"
#include "CSwitch.h"
#include <memory> // for std::shared_ptr
#include "MFCAppMultipleTopLevelDocumentsDoc.h"

#include <stdio.h>
#include "CPlc.h"
//#include "MyMonitorList.h"
#include <iostream>
#include "PlcDialog.h"
#include "ProgressBarDlg.h"
#include "PlcMASReadItemDlg.h"
#include "ElementDialog.h"



//class CMFCAppMultipleTopLevelDocumentsView : public CView
class CMFCAppMultipleTopLevelDocumentsView : public CScrollView
{
protected: // create from serialization only
	CMFCAppMultipleTopLevelDocumentsView();
	DECLARE_DYNCREATE(CMFCAppMultipleTopLevelDocumentsView)
	CMFCAppMultipleTopLevelDocumentsDoc* pDoc;

	//Syscom SDK:
	CHAR name[64] = "my_server";
	
	CPlc *pServer = nullptr;

	//CBitmap m_bmpBack;
	//CBrush m_brushBack;


// Attributes
public:
	CMFCAppMultipleTopLevelDocumentsDoc* GetDocument() const;
	CDialog * p_Dlg;
	CGrid MainGrid;
	//CSwitch TestSwitch;
	std::shared_ptr<CElement> m_pSelected;
	//= std::make_shared<CElement>();
	//std::shared_ptr<CElement> m_pPlcSelected;
	CSwitch * pCSwitchRaw = nullptr;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	void OnInitialUpdate() override;


protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCAppMultipleTopLevelDocumentsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
protected:
	CPoint m_FirstPoint;
	CPoint m_point;
	INT m_iGridStepX;
	INT m_iGridStepY;
public:
	CPoint m_LastPoint;
//	std::shared_ptr<CElement> CElementPtr;
protected:
	std::shared_ptr<CElement> m_pTempElement;
	int m_PenWidth;
	CSize DocSize{3000, 3000};
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedMfcbutton1();
//	afx_msg void OnBnClickedOk();
	int height;
	int width;
	std::shared_ptr<CElement> pSelected;
	afx_msg void OnAddswitch();
	afx_msg void OnElementDelete();
	afx_msg void OnElementSwitchoff();
	afx_msg void OnElementSwitchon();
	afx_msg void OnAddbulb();
	
	afx_msg void OnLoadElements();
	afx_msg void OnFileStoreElements();
	
	//afx_msg void OnPlcDefineplc();
	
	afx_msg void OnMenuAddPlc();
	
	afx_msg void OnElementplcDefineplc();
	afx_msg void OnElementplcConnectplc();
	
	afx_msg void OnElementplcDisconnectplc1();
	afx_msg void OnElementplcDeleteplc();
	afx_msg void OnElementplcStartplclifeguard();
	afx_msg LRESULT RefreshMainWindow(WPARAM wParam, LPARAM lParam);
//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnElementplcStopplclifeguard();
	afx_msg void OnElementplcReaditem();
	
	afx_msg void OnAddvoltmeter();
	afx_msg void OnElementDefineelement();
//	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in MFCAppMultipleTopLevelDocumentsView.cpp
inline CMFCAppMultipleTopLevelDocumentsDoc* CMFCAppMultipleTopLevelDocumentsView::GetDocument() const
   { return reinterpret_cast<CMFCAppMultipleTopLevelDocumentsDoc*>(m_pDocument); }
#endif

