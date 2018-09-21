#pragma once
#include "CElement.h"

#define IDB_BITMAP_TRAM 346



class CGrid :
	public CElement
{
public:
	CGrid();
	~CGrid();
	void Draw(CDC* pDC, CWnd* pView, INT iXstep = 50, INT iYstep =50, CRect* pRect = nullptr);
	
protected:
	int m_iXstep = 50;
	int m_iYstep = 50;
	CBitmap m_bmpBack;
	CBrush m_brushBack;
	BOOL bRet;

};

