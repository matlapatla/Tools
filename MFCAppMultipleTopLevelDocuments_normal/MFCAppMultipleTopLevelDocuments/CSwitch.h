#pragma once
#include "CElement.h"


enum switchStatus_t { unknown, open, closed  };
class CSwitch :
	public CElement
{
	DECLARE_SERIAL(CSwitch)
public:
	CSwitch();
	CSwitch(CPoint startPoint);
	~CSwitch();

	//enum switchStatus_t { open, closed, unknown } ;
	INT Draw(CDC* pDC, CWnd* pView, CPoint startPoint = {0,0}, INT iXstep = 50, INT iYstep = 50, CRect* pRect = nullptr);
	INT DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint = { 0,0 }, INT iXstep = 50, INT iYstep = 50, CRect* pRect = nullptr, HWND hObjectHandle = NULL);
	void SetStatus(INT newStatus);
	virtual void Serialize(CArchive& ar) override; // Serialize object
protected:
	switchStatus_t m_swichStatus;
	CString m_sIconFileNameOpen;
	CString m_sIconFileNameClosed;
	CString m_sIconFileNameUnknown;
	HBITMAP m_hBmpOpen;
	HBITMAP m_hBmpClosed;
	HBITMAP m_hBmpUnknown;
};

