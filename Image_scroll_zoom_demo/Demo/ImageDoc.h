// ImageDoc.h : header file
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CImageDoc document

class CImageDoc : public CDocument
{
   DECLARE_DYNAMIC(CImageDoc)

// Attributes
protected:
   CBitmap m_bmpImage;

// Construction
protected:
	CImageDoc();
   virtual ~CImageDoc() = 0;
	
// Operations
public:

   CBitmap& GetImage() {return m_bmpImage;}
   BOOL IsValidImage() const {return NULL != m_bmpImage.GetSafeHandle();}
   CSize GetImageSize();


// Overrides
public:
   virtual BOOL LoadFromFile(LPCTSTR pszFile);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDoc)
	public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

