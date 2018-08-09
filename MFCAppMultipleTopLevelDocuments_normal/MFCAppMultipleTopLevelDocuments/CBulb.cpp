#include "stdafx.h"
#include "CBulb.h"

IMPLEMENT_SERIAL(CBulb, CElement, 1001)

CBulb::CBulb()
{
	m_bulbStatus = unknownBulb;
	m_sIconFileNameOpen = L"C:\\bulbOn.bmp";
	m_sIconFileNameClosed = L"C:\\bulbOff.bmp";
	m_sIconFileNameUnknown = L"C:\\bulbUnknown.bmp";

	m_hBmpOn = (HBITMAP)::LoadImage(NULL, m_sIconFileNameOpen,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpOff = (HBITMAP)::LoadImage(NULL, m_sIconFileNameClosed,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_TypeOfElement = L"CBulb";
}

CBulb::CBulb(CPoint startPoint)
	: m_sIconFileNameOpen(_T(""))
{
	m_bulbStatus = unknownBulb;
	m_sIconFileNameOpen = L"C:\\bulbOn.bmp";
	m_sIconFileNameClosed = L"C:\\bulbOff.bmp";
	m_sIconFileNameUnknown = L"C:\\bulbUnknown.bmp";

	m_hBmpOn = (HBITMAP)::LoadImage(NULL, m_sIconFileNameOpen,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpOff = (HBITMAP)::LoadImage(NULL, m_sIconFileNameClosed,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_StartPoint = startPoint;
	m_TypeOfElement = L"CBulb";
}


CBulb::~CBulb()
{
}

INT CBulb::DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect, HWND hObjectHandle, CMainFrame* MFrame)
{
	pMainFrame = MFrame;
	if (m_StartPoint.x == 0 && m_StartPoint.y == 0)
	{
		m_StartPoint = startPoint;
	}


	CBitmap bmp;
	if (sValue == "0")
	{
		m_bulbStatus = off;
	}
	else
	{
		if (sValue == "1")
		{
			m_bulbStatus = on;
		}
		else
		{
			m_bulbStatus = unknownBulb;
		}
	}

	switch (m_bulbStatus) {
	case on:
		bmp.Attach(m_hBmpOn);
		break;
	case off:
		bmp.Attach(m_hBmpOff);
		break;
	case unknownBulb:
		bmp.Attach(m_hBmpUnknown);
		break;
	default:

		break;
	}

	CClientDC dc(pView);
	CClientDC aDC{ pView };
	CDC bmDC;
	bmDC.CreateCompatibleDC(&dc);
	CBitmap *pOldbmp = bmDC.SelectObject(&bmp);

	BITMAP  bi;
	bmp.GetBitmap(&bi);
	((CScrollView*)pView)->OnPrepareDC(&aDC);
	RECT point{ m_StartPoint.x , m_StartPoint.y, m_StartPoint.x + iXstep, m_StartPoint.y + iYstep };
	aDC.LPtoDP(&point);
	dc.StretchBlt(point.left, point.top, (point.right - point.left), (point.bottom - point.top), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	bmp.Detach();

	bmDC.SelectObject(pOldbmp);
	bmDC.DeleteDC();

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	CPoint ptScroll = ((CScrollView*)pView)->GetScrollPosition();
	//pDC->TextOut(m_StartPoint.x, m_StartPoint.y + 70, CString(_T("Bulb = " + sValue)));
	pDC->TextOut(m_StartPoint.x, m_StartPoint.y + 70, CString((CElement::sElementName + " = " + sValue)));
	

	if (xDlgRunning) this->drawMagentaBorders(pDC, iXstep, iYstep);


	m_EnclosingRect = CRect{
		(std::min)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::min)(m_StartPoint.y, m_StartPoint.y + iYstep),
		(std::max)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::max)(m_StartPoint.y, m_StartPoint.y + iYstep) };

	return 0;

}

void CBulb::SetStatus(INT newStatus)
{
	switch (newStatus)
	{
	case 0:
		m_bulbStatus = unknownBulb;
		break;
	case 1:
		m_bulbStatus = off;
		break;
	case 2:
		m_bulbStatus = on;
		break;
	default:
		m_bulbStatus = unknownBulb;
		break;

	}
}

void CBulb::Serialize(CArchive& ar)
{
	CElement::Serialize(ar); // Call the base class function
	if (ar.IsStoring())
	{ // Writing to the file
		ar << m_sIconFileNameOpen
		   << m_sIconFileNameClosed
		   << m_sIconFileNameUnknown;

	}
	else
	{ // Reading from the file
		ar >> m_sIconFileNameOpen
		   >> m_sIconFileNameClosed
		   >> m_sIconFileNameUnknown;
	}
}

