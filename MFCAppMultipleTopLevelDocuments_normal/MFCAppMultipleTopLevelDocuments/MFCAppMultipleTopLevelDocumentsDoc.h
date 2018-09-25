
// MFCAppMultipleTopLevelDocumentsDoc.h : interface of the CMFCAppMultipleTopLevelDocumentsDoc class
//


#pragma once
#include <memory> // for std::shared_ptr
#include "CElement.h"
#include "CSwitch.h"
#include "CBulb.h"
#include "CVoltMtr.h"
#include "CPlc.h"
#include <list>
//#include "MFCAppMultipleTopLevelDocumentsView.h"

#define WM_STARTDLGVARIABLECONTROL (WM_USER + 101)

class CMFCAppMultipleTopLevelDocumentsDoc : public CDocument
{

public:
	CPoint point{ 600,600 };
	CSwitch TestSwitch=point;
	

protected: // create from serialization only
	CMFCAppMultipleTopLevelDocumentsDoc();
	DECLARE_DYNCREATE(CMFCAppMultipleTopLevelDocumentsDoc)
	
// Attributes

	
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCAppMultipleTopLevelDocumentsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	struct pointers_t {
		std::shared_ptr<CElement> pElement;
		std::shared_ptr<CElement> pPlc;
	} pointers;

public:

// Generated message map functions
	std::list<std::shared_ptr<CElement>> m_Sketch;


protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnStartPokus();
	

//	CString PlcIpAddress;
private:
	CString PlcIpAddress;
public:
	afx_msg void OnUpdateStartPokus(CCmdUI *pCmdUI);
	int i = 0;
	afx_msg void OnFileZoufalost();
	afx_msg void OnUpdateFileZoufalost(CCmdUI *pCmdUI);
	std::shared_ptr<CElement> FindElement(const CPoint& point)const;
	void AddElement(std::shared_ptr<CElement>& pElement);
	void AddElementSwitch(const CPoint& point);
	void AddElementBulb(const CPoint& point);
	void AddElementVltMtr(const CPoint& point);
	void AddElementPlc(const CPoint& point, CMainFrame*);
	void DeleteElement(std::shared_ptr<CElement>& pElement);
	void DeleteElement(const CPoint& point);
	void DrawElements(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect, HWND, CMainFrame*);
	
	afx_msg void OnElementSwitch(const CPoint& point, INT newstatus);

	afx_msg void SwitchTheSwitch(const CPoint& point);
	
};
