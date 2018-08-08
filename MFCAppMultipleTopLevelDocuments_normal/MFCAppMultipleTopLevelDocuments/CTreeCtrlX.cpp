// CTreeCtrlX.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "CTreeCtrlX.h"


// CTreeCtrlX

IMPLEMENT_DYNAMIC(CTreeCtrlX, CTreeCtrl)

CTreeCtrlX::CTreeCtrlX()
{	
		CTreeCtrl::CTreeCtrl();
		m_bLDragging = FALSE;	
}

CTreeCtrlX::~CTreeCtrlX()
{
}


BEGIN_MESSAGE_MAP(CTreeCtrlX, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CTreeCtrlX::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CTreeCtrlX message handlers




void CTreeCtrlX::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	*pResult = 0;

	m_hitemDrag = pNMTreeView->itemNew.hItem;
	
	CString text = this->GetItemText(m_hitemDrag);
	m_hitemDrop = NULL;

	//char szText[] = "Hello, world123456";

	UINT registeredClipboardFormat = RegisterClipboardFormatA("VARLISTLINE"); //0 means failed
	COleDataSource*	pSource = new COleDataSource();
	CSharedFile	sf(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
	int tmp = text.GetLength();
	TRACE("Drag and Drop String length = '%d'\r\n", tmp);
	sf.Write(text, (2*text.GetLength()));
	HGLOBAL hMem = sf.Detach();
	if (!hMem) return;
	pSource->CacheGlobalData(registeredClipboardFormat, hMem);
	DROPEFFECT de = pSource->DoDragDrop();
	if (de == DROPEFFECT_MOVE)
	{    
		// Delete the string from the document.
		int i=0;
		i++;
	} 
}


void CTreeCtrlX::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	HTREEITEM	hitem;
	UINT		flags;

	if (m_bLDragging)
	{
		POINT pt = point;
		ClientToScreen(&pt);
		CImageList::DragMove(pt);
		if ((hitem = HitTest(point, &flags)) != NULL)
		{
			CImageList::DragShowNolock(FALSE);
			SelectDropTarget(hitem);
			m_hitemDrop = hitem;
			CImageList::DragShowNolock(TRUE);
		}
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}


void CTreeCtrlX::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CTreeCtrl::OnLButtonUp(nFlags, point);

	if (m_bLDragging)
	{
		m_bLDragging = FALSE;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();

		delete m_pDragImage;
		/*
		// Remove drop target highlighting
		SelectDropTarget(NULL);

		if (m_hitemDrag == m_hitemDrop)
			return;

		// If Drag item is an ancestor of Drop item then return
		HTREEITEM htiParent = m_hitemDrop;
		while ((htiParent = GetParentItem(htiParent)) != NULL)
		{
			if (htiParent == m_hitemDrag) return;
		}

		Expand(m_hitemDrop, TVE_EXPAND);

		//HTREEITEM htiNew = CopyBranch(m_hitemDrag, m_hitemDrop, TVI_LAST);
		//DeleteItem(m_hitemDrag);
		//SelectItem(htiNew);
		*/
	}
}

void CTreeCtrlX::OnDragLeave()
{

	if (m_bLDragging)
	{
		m_bLDragging = FALSE;
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();

		delete m_pDragImage;
	}

}


void CTreeCtrlX::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CTreeCtrl::OnLButtonDown(nFlags, point);
}
