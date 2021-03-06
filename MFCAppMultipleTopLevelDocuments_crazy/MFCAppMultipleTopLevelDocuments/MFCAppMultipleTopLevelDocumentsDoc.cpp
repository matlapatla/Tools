
// MFCAppMultipleTopLevelDocumentsDoc.cpp : implementation of the CMFCAppMultipleTopLevelDocumentsDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCAppMultipleTopLevelDocuments.h"
#endif

#include "MFCAppMultipleTopLevelDocumentsDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCAppMultipleTopLevelDocumentsDoc

IMPLEMENT_DYNCREATE(CMFCAppMultipleTopLevelDocumentsDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCAppMultipleTopLevelDocumentsDoc, CDocument)
	ON_COMMAND(ID_START_POKUS, &CMFCAppMultipleTopLevelDocumentsDoc::OnStartPokus)
	ON_UPDATE_COMMAND_UI(ID_START_POKUS, &CMFCAppMultipleTopLevelDocumentsDoc::OnUpdateStartPokus)
	
	ON_COMMAND(ID_FILE_ZOUFALOST, &CMFCAppMultipleTopLevelDocumentsDoc::OnFileZoufalost)
	ON_UPDATE_COMMAND_UI(ID_FILE_ZOUFALOST, &CMFCAppMultipleTopLevelDocumentsDoc::OnUpdateFileZoufalost)
END_MESSAGE_MAP()


// CMFCAppMultipleTopLevelDocumentsDoc construction/destruction


CMFCAppMultipleTopLevelDocumentsDoc::CMFCAppMultipleTopLevelDocumentsDoc()
	: PlcIpAddress(_T(""))
{
	PlcIpAddress = _T("");
	
}


CMFCAppMultipleTopLevelDocumentsDoc::~CMFCAppMultipleTopLevelDocumentsDoc()
{
}

BOOL CMFCAppMultipleTopLevelDocumentsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCAppMultipleTopLevelDocumentsDoc serialization

void CMFCAppMultipleTopLevelDocumentsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//ar << static_cast<int>(m_Element)
		ar << m_Sketch.size();
		for (const auto& pElement : m_Sketch)
			ar << pElement.get();

	}
	else
	{
		// TODO: add loading code here
		size_t elementCount{}; // Count of number of elements
		ar >> elementCount; // retrieve the element count
		CElement* pElement;
		for (size_t i{}; i < elementCount; ++i)
		{
			ar >> pElement;
			m_Sketch.push_back(std::shared_ptr<CElement>(pElement));
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCAppMultipleTopLevelDocumentsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCAppMultipleTopLevelDocumentsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCAppMultipleTopLevelDocumentsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCAppMultipleTopLevelDocumentsDoc diagnostics

#ifdef _DEBUG
void CMFCAppMultipleTopLevelDocumentsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCAppMultipleTopLevelDocumentsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCAppMultipleTopLevelDocumentsDoc commands


void CMFCAppMultipleTopLevelDocumentsDoc::OnStartPokus()
{
	// TODO: Add your command handler code here
	

	this->i++;

}


void CMFCAppMultipleTopLevelDocumentsDoc::OnUpdateStartPokus(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	int pomi;
	int bitemask = 1;
	pomi = ((CMFCAppMultipleTopLevelDocumentsDoc::i) & bitemask);
	pCmdUI->SetCheck(pomi);

}


void CMFCAppMultipleTopLevelDocumentsDoc::OnFileZoufalost()
{
	// TODO: Add your command handler code here
	this->i++;
}



void CMFCAppMultipleTopLevelDocumentsDoc::OnUpdateFileZoufalost(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	// TODO: Add your command update UI handler code here
	int pomi;
	int bitemask = 1;
	pomi = ((CMFCAppMultipleTopLevelDocumentsDoc::i) & bitemask);
	pCmdUI->SetCheck(pomi);
	if (pomi == 0) {
		pCmdUI->SetText(L"prdlajs");
	}
	else
	{
		pCmdUI->SetText(L"matlajs");
	}

}


std::shared_ptr<CElement> CMFCAppMultipleTopLevelDocumentsDoc::FindElement(const CPoint& point)const
{
	for (const auto& pElement : m_Sketch)
	{
		if (pElement->GetEnclosingRect().PtInRect(point))
			return pElement;
	}
	return nullptr;
}

void CMFCAppMultipleTopLevelDocumentsDoc::AddElement(std::shared_ptr<CElement>& pElement)
{
	m_Sketch.push_back(pElement);
	SetModifiedFlag();
}
void CMFCAppMultipleTopLevelDocumentsDoc::AddElementSwitch(const CPoint& point)
{
	std::shared_ptr<CElement> pCSwitch{ new CSwitch(point) };
	m_Sketch.push_back(pCSwitch);
	SetModifiedFlag();
}

void CMFCAppMultipleTopLevelDocumentsDoc::AddElementBulb(const CPoint& point)
{
	std::shared_ptr<CElement> pCSwitch{ new CBulb(point) };
	m_Sketch.push_back(pCSwitch);
	SetModifiedFlag();
}

void CMFCAppMultipleTopLevelDocumentsDoc::AddElementVltMtr(const CPoint& point)
{
	std::shared_ptr<CElement> pCSwitch{ new CVoltMtr(point) };
	m_Sketch.push_back(pCSwitch);
	SetModifiedFlag();
}

void CMFCAppMultipleTopLevelDocumentsDoc::AddElementPlc(const CPoint& point)
{
	std::shared_ptr<CElement> pCSwitch{ new CPlc(point) };
	m_Sketch.push_back(pCSwitch);
	pCSwitch->setmSketch(m_Sketch);
	SetModifiedFlag();
}

void CMFCAppMultipleTopLevelDocumentsDoc::DeleteElement(std::shared_ptr<CElement>& pElement)
{
	m_Sketch.remove(pElement);
	SetModifiedFlag();
}

void CMFCAppMultipleTopLevelDocumentsDoc::DeleteElement(const CPoint& point)
{
	std::shared_ptr<CElement> pElement = this->FindElement(point);
	if (pElement != nullptr)
	{
		m_Sketch.remove(pElement);
		pElement.~shared_ptr();
		//AfxMessageBox(L"Element deleted.");
	}
	SetModifiedFlag();
}

void CMFCAppMultipleTopLevelDocumentsDoc::DrawElements(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect, HWND hObjectHandle)
{
	for (const auto& pElement : m_Sketch)
	{		
		pElement->DrawElement(pDC, pView, startPoint, iXstep, iYstep, pRect, hObjectHandle);
	}
}




void CMFCAppMultipleTopLevelDocumentsDoc::OnElementSwitch(const CPoint& point, INT newstatus)
{
	std::shared_ptr<CElement> pElement = this->FindElement(point);
	pElement->SetStatus(newstatus);
	SetModifiedFlag();
}


