#include "stdafx.h"
#include "CSwitch.h"

IMPLEMENT_SERIAL(CSwitch, CElement, 1001)

CSwitch::CSwitch()
{
	m_swichStatus = unknown;
	m_sIconFileNameOpen = L"C:\\switchOpen.bmp";
	m_sIconFileNameClosed = L"C:\\switchClosed.bmp";
	m_sIconFileNameUnknown = L"C:\\switchUnknown.bmp";

	m_hBmpOpen = (HBITMAP)::LoadImage(NULL, m_sIconFileNameOpen,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpClosed = (HBITMAP)::LoadImage(NULL, m_sIconFileNameClosed,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	
	m_TypeOfElement = L"CSwitch";
}


CSwitch::CSwitch(CPoint startPoint)
	: m_sIconFileNameOpen(_T(""))
{
	m_swichStatus = unknown;
	m_sIconFileNameOpen = L"C:\\switchOpen.bmp";
	m_sIconFileNameClosed = L"C:\\switchClosed.bmp";
	m_sIconFileNameUnknown = L"C:\\switchUnknown.bmp";

	m_hBmpOpen = (HBITMAP)::LoadImage(NULL, m_sIconFileNameOpen,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpClosed = (HBITMAP)::LoadImage(NULL, m_sIconFileNameClosed,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_StartPoint = startPoint;
	m_TypeOfElement = L"CSwitch";
}


CSwitch::~CSwitch()
{
}


INT CSwitch::Draw(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect)
{
	
	if (m_StartPoint.x == 0 && m_StartPoint.y == 0)
	{
		m_StartPoint = startPoint;
	}


	CBitmap bmp;
	switch(m_swichStatus) {
		case open: 
			bmp.Attach(m_hBmpOpen);			
			break;
		case closed:
			bmp.Attach(m_hBmpClosed);			 
			break;
		case unknown:
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
	((CScrollView*) pView)->OnPrepareDC(&aDC);
	RECT point{ m_StartPoint.x , m_StartPoint.y, m_StartPoint.x + iXstep, m_StartPoint.y + iYstep };
	//aDC.LPtoDP(&point);
	pDC->StretchBlt(point.left + 1, point.top + 1, (point.right - point.left - 1), (point.bottom - point.top - 1), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	//dc.StretchBlt(point.left + 1, point.top + 1, (point.right - point.left - 1), (point.bottom - point.top - 1), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	bmp.Detach();

	m_EnclosingRect = CRect{
		(std::min)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::min)(m_StartPoint.y, m_StartPoint.y + iYstep),
		(std::max)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::max)(m_StartPoint.y, m_StartPoint.y + iYstep) };

	return 0;

}

INT CSwitch::DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect, HWND hObjectHandle, CMainFrame* MFrame)
{
	pMainFrame = MFrame;
	if (m_StartPoint.x == 0 && m_StartPoint.y == 0)
	{
		m_StartPoint = startPoint;
	}

	if (sValue == "0")
	{
		m_swichStatus = open; 
	}
	else
	{
		if (sValue == "1")
		{
			m_swichStatus = closed;
		}
		else
		{
			m_swichStatus = unknown;
		}
	}


	CBitmap bmp;
	switch (m_swichStatus) {
	case open:
		bmp.Attach(m_hBmpOpen);
		break;
	case closed:
		bmp.Attach(m_hBmpClosed);
		break;
	case unknown:
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
	//aDC.LPtoDP(&point);
	//aDC.DPtoLP(&point);
	pDC->StretchBlt(point.left + 1, point.top + 1, (point.right - point.left - 1), (point.bottom - point.top - 1), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	//dc.StretchBlt(point.left + 1, point.top + 1, (point.right - point.left - 1), (point.bottom - point.top - 1), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	bmp.Detach();

	bmDC.SelectObject(pOldbmp);
	bmDC.DeleteDC();

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	CPoint ptScroll = ((CScrollView*)pView)->GetScrollPosition();
	pDC->TextOut(m_StartPoint.x, m_StartPoint.y + 70, CString((CElement::sElementName + " = " + sValue)));



	if (xDlgRunning) this->drawMagentaBorders(pDC, iXstep, iYstep);
	
	m_EnclosingRect = CRect{
		(std::min)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::min)(m_StartPoint.y, m_StartPoint.y + iYstep),
		(std::max)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::max)(m_StartPoint.y, m_StartPoint.y + iYstep) };

	return 0;

}

void CSwitch::SetStatus(INT newStatus)
{
	switch (newStatus)
	{
	case 0:
		m_swichStatus = unknown;
		break;
	case 1:
		m_swichStatus = open;
		break;
	case 2:
		m_swichStatus = closed;
		break;
	default:
		m_swichStatus = unknown;
		break;

	}
}

void CSwitch::Serialize(CArchive& ar)
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
		ar 	>> m_sIconFileNameOpen
			>> m_sIconFileNameClosed
			>> m_sIconFileNameUnknown;			
	}
}
