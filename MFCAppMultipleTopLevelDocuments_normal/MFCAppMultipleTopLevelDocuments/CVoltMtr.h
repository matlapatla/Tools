#pragma once
#include "CElement.h"

#define _USE_MATH_DEFINES // for C++  
#include <cmath>  
#include <math.h>  

#define WM_REFRESHPICTURE (WM_USER + 100)
class CVoltMtr :
	public CElement
{
	DECLARE_SERIAL(CVoltMtr)
public:
	CVoltMtr();
	CVoltMtr(CPoint startPoint);
	~CVoltMtr();

	INT DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint = { 0,0 }, INT iXstep = 50, INT iYstep = 50, CRect* pRect = nullptr, HWND hObjectHandle = NULL, CMainFrame* MFrame = nullptr);
	void SetStatus(INT newStatus);
	virtual void Serialize(CArchive& ar) override; // Serialize object

	
	enum vltmtrStatus_t { unknownVltMtr, notConnectedVltMtr, connectedVltMtr };
	vltmtrStatus_t m_vltmtrStatus;

protected:
	CString m_sIconFileNameConnected;
	CString m_sIconFileNameNotConnected;
	CString m_sIconFileNameUnknown;
	HBITMAP m_hBmpCon;
	HBITMAP m_hBmpNotCon;
	HBITMAP m_hBmpUnknown;
};

