#pragma once


// CTreeCtrlX

class CTreeCtrlX : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeCtrlX)

public:
	CTreeCtrlX();
	virtual ~CTreeCtrlX();
	

protected:
	DECLARE_MESSAGE_MAP()
	CImageList*	m_pDragImage;
	BOOL		m_bLDragging = FALSE;
	HTREEITEM	m_hitemDrag, m_hitemDrop;
public:
	afx_msg void OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


