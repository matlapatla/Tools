#include "stdafx.h"
#include "CGrid.h"


CGrid::CGrid()
{
}


CGrid::~CGrid()
{
}



void CGrid:: Draw(CDC* pDC, CWnd* pView, INT iXstep, INT iYstep, CRect* pRect)
{
	m_MySize = pDC->GetWindowExt();

	if (pRect == nullptr)
		pView->GetWindowRect(m_MyRect);
	else
		m_MyRect = *pRect; //the screen width and height
	
	m_Color = RGB(0, 0, 100);
	m_PenWidth = 1;
	CPen aPen;
	aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	m_StartPoint = { 0, 0 };
	m_iXstep = iXstep;
	m_iYstep = iYstep;
	//write vertical grid lines
	int y = 0;
	for (int x = m_StartPoint.x; x < m_MyRect.right; x += m_iXstep) 
	{
		pDC->MoveTo(x, y);
		pDC->LineTo(x, m_MyRect.bottom);
	}
	//write horizontal grid lines
	int x = 0;
	for (int y = m_StartPoint.y; y < m_MyRect.bottom; y += m_iYstep)
	{
		pDC->MoveTo(x, y);
		pDC->LineTo(m_MyRect.right, y);
	}
	pDC->SelectObject(&pOldPen);

	if (NULL != m_brushBack.GetSafeHandle())
		m_brushBack.DeleteObject();
	if (NULL != m_bmpBack.GetSafeHandle())
		m_bmpBack.DeleteObject();

	BOOL bRet = m_bmpBack.LoadBitmap(IDB_BITMAP_TRAM);
	if (bRet)
		bRet = m_brushBack.CreatePatternBrush(&m_bmpBack);
	CClientDC aDC{ pView };
	((CScrollView*)pView)->OnPrepareDC(&aDC);
	//CRect rcClient(0, 0, 200, 354);
	RECT rcClient{ 0, 0, 200, 354 };
	//GetClientRect(rcClient);
	aDC.LPtoDP(&rcClient);
	pDC->SelectObject(&m_brushBack);
	//pDC->PatBlt(0, 0, 200, 354, PATCOPY);
	pDC->PatBlt(0, 0, rcClient.right, rcClient.bottom, PATCOPY);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 255));
	CPoint ptScroll =((CScrollView*) pView)->GetScrollPosition();
	pDC->TextOut(ptScroll.x + 10, ptScroll.y + 10, CString(_T("Tango Ostrava")));


}
