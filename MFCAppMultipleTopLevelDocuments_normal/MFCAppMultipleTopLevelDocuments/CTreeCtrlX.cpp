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

	char szText[] = "Hello, world123456";

	
	HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, lstrlenA (szText) + 1);
	LPSTR pData = (LPSTR) ::GlobalLock(hData);
	::lstrcpyA(pData, szText);
	GlobalUnlock(hData);
	COleDataSource ods;
	ods.CacheGlobalData(CF_TEXT, hData);
	DROPEFFECT de = DROPEFFECT_NONE;
	de = ods.DoDragDrop(DROPEFFECT_COPY| DROPEFFECT_MOVE| DROPEFFECT_LINK| DROPEFFECT_SCROLL);
	if (de == DROPEFFECT_MOVE)
	{    
		// Delete the string from the document.
		int i=0;
		i++;
	} 

	/*

	uSTGMEDIUM * StgMediumPtr;
	//StgMediumPtr->tymed = TYMED_HGLOBAL;
	//StgMediumPtr->hGlobal = ;
	UINT registeredClipboardFormat = RegisterClipboardFormatA("VARLISTTEXT"); //0 means failed
	//OleDataSource.CacheData(registerClipboardFormat, StgMediumPtr);
	CString * dataToDrag;
	//dataToDrag = &text;
	const TCHAR* x = (LPCTSTR) text;
	::lstrcpy(x, text);
	//HGLOBAL  hGlobal = GlobalAlloc(GHND, dataToDrag->GetAllocLength());
	HGLOBAL  hGlobal = GlobalAlloc(GHND, 1024);
	//dataToDrag = (CString *)GlobalLock(hGlobal);
	x = (LPCTSTR)GlobalLock(hGlobal);
	//dataToDrag = &text;
    x = (LPCTSTR)text;
	GlobalUnlock(hGlobal);
	//OleDataSource.CacheGlobalData(registeredClipboardFormat, hGlobal);
	OleDataSource.CacheGlobalData(CF_TEXT, hGlobal);
	OleDataSource.DoDragDrop(DROPEFFECT_COPY);
	//OleDataSource.InternalRelease();
	//GlobalFree(hGlobal);

	*/
	/*
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	m_hitemDrag = pNMTreeView->itemNew.hItem;
	m_hitemDrop = NULL;

	m_pDragImage = CreateDragImage(m_hitemDrag);  // get the image list for dragging
												  // CreateDragImage() returns NULL if no image list
												  // associated with the tree view control
	if (!m_pDragImage)
		return;

	m_bLDragging = TRUE;
	m_pDragImage->BeginDrag(0, CPoint(-15, -15));
	POINT pt = pNMTreeView->ptDrag;
	ClientToScreen(&pt);
	m_pDragImage->DragEnter(NULL, pt);
	SetCapture();


	UNREFERENCED_PARAMETER(pResult);

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	COleDataSource* pDataSrc = new COleDataSource();
	if (NULL != pDataSrc)
	{
		//pDataSrc->Initialize(pNMLV, this);
		//pDataSrc->DelayRenderData((CLIPFORMAT)RegisterClipboardFormat(_T("TIGroupFiles")));
		pDataSrc->DoDragDrop();
		pDataSrc->InternalRelease();
	}
	*/
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
