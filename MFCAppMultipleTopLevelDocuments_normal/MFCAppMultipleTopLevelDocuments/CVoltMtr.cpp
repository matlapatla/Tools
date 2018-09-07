#include "stdafx.h"
#include "CVoltMtr.h"
#include "Resource.h"

IMPLEMENT_SERIAL(CVoltMtr, CElement, 1001)

CVoltMtr::CVoltMtr()
{
	m_vltmtrStatus = unknownVltMtr;
	m_sIconFileNameConnected = L"C:\\voltmetr.bmp";
	m_sIconFileNameNotConnected = L"C:\\voltmetr.bmp";
	m_sIconFileNameUnknown = L"C:\\voltmetr.bmp";

	m_hBmpCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpNotCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameNotConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	
}

CVoltMtr::CVoltMtr(CPoint startPoint)
{
	m_vltmtrStatus = unknownVltMtr;
	m_sIconFileNameConnected = L"C:\\voltmetr.bmp";
	m_sIconFileNameNotConnected = L"C:\\voltmetr.bmp";
	m_sIconFileNameUnknown = L"C:\\voltmetr.bmp";

	m_hBmpCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpNotCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameNotConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_TypeOfElement = L"CVltMtr";
	m_StartPoint = startPoint;

}



CVoltMtr::~CVoltMtr()
{
}

INT CVoltMtr::DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect, HWND hObjectHandle, CMainFrame* MFrame)
{
	pMainFrame = MFrame;
	if (m_StartPoint.x == 0 && m_StartPoint.y == 0)
	{
		m_StartPoint = startPoint;
	}

	CBitmap bmp;
	switch (m_vltmtrStatus) {
	case unknownVltMtr:
		bmp.Attach(m_hBmpCon);
		break;
	case notConnectedVltMtr:
		bmp.Attach(m_hBmpNotCon);
		break;
	case connectedVltMtr:
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
	((CScrollView*)pView)->OnPrepareDC(pDC);
	RECT point{ m_StartPoint.x , m_StartPoint.y, m_StartPoint.x + iXstep, m_StartPoint.y + iYstep };
	RECT point1{ m_StartPoint.x , m_StartPoint.y, m_StartPoint.x + iXstep, m_StartPoint.y + iYstep };
	aDC.LPtoDP(&point);
	//pDC->LPtoDP(&point1);
	dc.StretchBlt(point.left+1, point.top+1, (point.right - point.left - 1), (point.bottom - point.top - 1), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	//dc.StretchBlt(point.left, point.top, (point.right - point.left), (point.bottom - point.top), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, PATCOPY);
	bmp.Detach();
	bmDC.SelectObject(pOldbmp);
	bmDC.DeleteDC();


	m_Color = RGB(200, 0, 100);
	m_PenWidth = 3;
	CPen aPen;
	aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	//pDC->MoveTo(m_StartPoint.x + 25, m_StartPoint.y + 25);
	//pDC->DPtoLP(&point1);
	pDC->MoveTo(point1.left + 25, point1.top + 25);

	//signed __int64 i64sValue;
	//signed __int64 i64sLowestValue;
	//signed __int64 i64sHighestValue;
	DOUBLE fValue;
	DOUBLE fLowestValue;
	DOUBLE fHighestValue;
	DOUBLE fDelta;
	DOUBLE fNormConst;
	DOUBLE fNormValue;
	
	fValue = _wtof(sValue);
	fLowestValue = _wtof(sLowestValue);
	fHighestValue = _wtof(sHighestValue);
	//i64sValue  = _wtoi(sValue);
	//i64sLowestValue = _wtoi(sLowestValue);
	//i64sHighestValue = _wtoi(sHighestValue);
	/*
	_stscanf_s((LPCTSTR)sValue, _T("%I64"), &i64sValue);
	_stscanf_s((LPCTSTR)sLowestValue, _T("%I64"), &i64sLowestValue);
	_stscanf_s((LPCTSTR)sHighestValue, _T("%I64"), &i64sHighestValue);
	*/

	fDelta = fValue - fLowestValue;
	//fDelta = static_cast<FLOAT>(i64sValue - i64sLowestValue);
	fNormConst = (fHighestValue - fLowestValue) / M_PI;
	//fNormConst = (static_cast<FLOAT>(i64sHighestValue - i64sLowestValue)) / M_PI;
	fNormValue = fDelta / fNormConst;
	DOUBLE fy = 25 - (25 * (sin(fNormValue))); //offset of the centre
	DOUBLE fx = 25 - (25 * (cos(fNormValue))); //offset of the centre

	//pDC->LineTo(m_StartPoint.x + 25, m_StartPoint.y);
	//pDC->LineTo(m_StartPoint.x + static_cast<INT>(fx), m_StartPoint.y + static_cast<INT>(fy));
	pDC->LineTo(point1.left + static_cast<INT>(fx), point1.top + static_cast<INT>(fy));
	pDC->SelectObject(&pOldPen);
	
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	CPoint ptScroll = ((CScrollView*)pView)->GetScrollPosition();
	pDC->TextOut(point1.left, point1.top + 70, CString((CElement::sElementName + " = " + sValue)));

	
	if (xDlgRunning) this->drawMagentaBorders(pDC, iXstep, iYstep);


	m_EnclosingRect = CRect{
		(std::min)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::min)(m_StartPoint.y, m_StartPoint.y + iYstep),
		(std::max)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::max)(m_StartPoint.y, m_StartPoint.y + iYstep) };

	//PostMessage(hObjectHandle, WM_REFRESHPICTURE, 0, 0);
	//pDC->MoveTo(point.left + 25, point.top + 50);
	//pDC->LineTo(point.left + 25, point.top);

	
	
	return 0;

}


void CVoltMtr::SetStatus(INT newStatus)
{
	switch (newStatus)
	{
	case 0:
		m_vltmtrStatus = unknownVltMtr;
		break;
	case 1:
		m_vltmtrStatus = notConnectedVltMtr;
		break;
	case 2:
		m_vltmtrStatus = connectedVltMtr;
		break;
	default:
		m_vltmtrStatus = unknownVltMtr;
		break;

	}
}

void CVoltMtr::Serialize(CArchive& ar)
{
	CElement::Serialize(ar); // Call the base class function
	if (ar.IsStoring())
	{ // Writing to the file
		ar << m_sIconFileNameConnected
			<< m_sIconFileNameNotConnected
			<< m_sIconFileNameUnknown;

			
	}
	else
	{ // Reading from the file
		ar >> m_sIconFileNameConnected
			>> m_sIconFileNameNotConnected
			>> m_sIconFileNameUnknown;

			

	}
}
