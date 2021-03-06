#pragma once
#include "ViewTree.h"

// CVarlistView
class CVarlistViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CVarlistView : public CDockablePane
{
	//DECLARE_DYNAMIC(CVarlistView, CDockablePane)
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CVarlistView)

private:
	 CTreeCtrl m_wndVarlistView;

public:
	CVarlistView();
	virtual ~CVarlistView();

	void AdjustLayout();
	void OnChangeVisualStyle();





protected:

//	CViewTree m_wndVarlistView;
	CImageList m_VarlistViewImages;
	CVarlistViewToolBar m_wndToolBar;
	UINT m_nCurrSort;

	void FillVarlistView();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	

};


