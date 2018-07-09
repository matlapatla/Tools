#pragma once
#include "CElement.h"

class CBulb :
	public CElement
{
	DECLARE_SERIAL(CBulb)
public:
	CBulb();
	CBulb(CPoint startPoint);
	~CBulb();

	INT DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint = { 0,0 }, INT iXstep = 50, INT iYstep = 50, CRect* pRect = nullptr, HWND hObjectHandle = NULL, CMainFrame* MFrame = nullptr);
	void SetStatus(INT newStatus);
	virtual void Serialize(CArchive& ar) override; // Serialize object

protected:
	enum bulbStatus_t { unknownBulb, on, off, flashing };

	bulbStatus_t m_bulbStatus;
	CString m_sIconFileNameOpen;
	CString m_sIconFileNameClosed;
	CString m_sIconFileNameUnknown;
	HBITMAP m_hBmpOn;
	HBITMAP m_hBmpOff;
	HBITMAP m_hBmpUnknown;
};

