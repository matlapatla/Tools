// MemDC.h: interface for the CMemDC class.
//
// Author: Ovidiu Cucu
// Homepage: http://www.codexpert.ro/
// Weblog: http://codexpert.ro/blog/

#pragma once


class CMemDC : public CDC  
{
   DECLARE_DYNAMIC(CMemDC)

   int m_nSavedDC;
   CBitmap m_bitmap;
public:
	CMemDC(CDC* pDC, int nWidth, int nHeight);
   CMemDC(CDC* pDC, CBitmap* pBitmap);
	~CMemDC();
};

inline CMemDC::CMemDC(CDC* pDC, int nWidth, int nHeight)
{
   ASSERT_VALID(pDC);
   VERIFY(CreateCompatibleDC(pDC));

   m_nSavedDC = SaveDC();
   VERIFY(m_bitmap.CreateCompatibleBitmap(pDC, nWidth, nHeight));
   SelectObject(&m_bitmap);
}

inline CMemDC::CMemDC(CDC* pDC, CBitmap* pBitmap)
{
   ASSERT_VALID(pDC);
   ASSERT_VALID(pBitmap);

   VERIFY(CreateCompatibleDC(pDC));
   SelectObject(pBitmap);
}

inline CMemDC::~CMemDC()
{
   RestoreDC(m_nSavedDC);
   if(NULL != m_bitmap.GetSafeHandle())
   {
      m_bitmap.DeleteObject();
   }
}

