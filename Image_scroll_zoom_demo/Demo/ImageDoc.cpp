// ImageDoc.cpp : implementation file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#include "stdafx.h"
#include "Demo.h"
#include "ImageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageDoc

IMPLEMENT_DYNAMIC(CImageDoc, CDocument)

CImageDoc::CImageDoc()
{
}

BOOL CImageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

   if(NULL != m_bmpImage.GetSafeHandle())
      m_bmpImage.DeleteObject();
   
	return TRUE;
}

CImageDoc::~CImageDoc()
{
}

BOOL CImageDoc::LoadFromFile(LPCTSTR pszFileName)
{
   if(NULL != m_bmpImage.GetSafeHandle())
      m_bmpImage.DeleteObject();
   
   HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, pszFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
   if(NULL == hBitmap)
   {
      CString strMessage;
      strMessage.Format(_T("LoadImage failed\nError: %u"), ::GetLastError());
      AfxMessageBox(strMessage);
   }
   else
   {
      m_bmpImage.Attach(hBitmap);
   }
   return NULL != hBitmap;
}

CSize CImageDoc::GetImageSize()
{
   CSize size(0, 0);
   if(IsValidImage())
   {
      BITMAP bmp = {0};
      m_bmpImage.GetBitmap(&bmp);
      size.cx = bmp.bmWidth;
      size.cy = bmp.bmHeight;
   }
   return size;
}


BOOL CImageDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return LoadFromFile(lpszPathName);
}


BEGIN_MESSAGE_MAP(CImageDoc, CDocument)
	//{{AFX_MSG_MAP(CImageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDoc diagnostics

#ifdef _DEBUG
void CImageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CImageDoc commands


