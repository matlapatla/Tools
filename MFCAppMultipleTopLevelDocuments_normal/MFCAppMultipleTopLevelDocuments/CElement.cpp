// CElement.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "CElement.h"


// CElement
IMPLEMENT_SERIAL(CElement, CObject, 1001)


CElement::CElement()
{
	m_StartPoint = { 0,0 };
	xDlgRunning = false;
	sLowestValue = L"-100";
	sHighestValue = L"100";
	sValue = L"0";
}

CElement::~CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, int penWidth) :
	m_StartPoint{ start }, m_PenWidth{ penWidth }, m_Color{ color } 
{
	xDlgRunning = false;

}

// CElement member functions

/*
void CElement::AssertValid() const
{
	CObject::AssertValid();

	// TODO: Add your specialized code here and/or call the base class
}
*/
void CElement::Serialize(CArchive& ar)
{
	CObject::Serialize(ar); // Call the base class function
	if (ar.IsStoring())
	{ // Writing to the file
		ar << m_StartPoint // Element position
			<< m_PenWidth // The pen width
			<< m_Color // The element color
			<< m_EnclosingRect // The enclosing rectangle			
			<< ulAbsAddress
			<< sVarType
			<< sElementName
			<< sPlcName
			<< sLowestValue
			<< sHighestValue;
	}
	else
	{ // Reading from the file
		ar >> m_StartPoint // Element position
			>> m_PenWidth // The pen width
			>> m_Color // The element color
			>> m_EnclosingRect // The enclosing rectangle
	    	>> ulAbsAddress
	    	>> sVarType
			>> sElementName
			>> sPlcName
			>> sLowestValue
			>> sHighestValue;

		syscomData.sName = sElementName;
		syscomData.ulAbsAddress = ulAbsAddress;
		syscomData.sDataTyp = sVarType;
		this->SelectronVarType2VarLength(sVarType, &syscomData.iVarLengthBits, &syscomData.iVarLengthBytes, &syscomData.dtDataType, &syscomData.uiDataType);


	}
}


void CElement::getTypeOfElement(CString & elemType)
{
	elemType = m_TypeOfElement;
}

void CElement::setElementName(CString n)
{
	sElementName = n;
	syscomData.sName = sElementName;
}

void CElement::getElementName(CString &n)
{
	n = sElementName;
}


void CElement::setPlcName(CString n)
{
	sPlcName = n;
}

void CElement::getPlcName(CString& n)
{
	n = sPlcName;
}


void CElement::setElementAddress(CString n)
{
	unsigned __int64 ui64;
	
	_stscanf_s((LPCTSTR)n, _T("%I64u"), &ui64);
	ulAbsAddress = ui64;
	syscomData.ulAbsAddress = ulAbsAddress;
	
}

void CElement::getElementAddress(CString &n)
{
	n.Format(_T("%u"), ulAbsAddress);
}



void CElement::setVarType(CString n)
{
	
	if (0 == this->SelectronVarType2VarLength(n, &syscomData.iVarLengthBits, &syscomData.iVarLengthBytes, &syscomData.dtDataType, &syscomData.uiDataType))
	{ 
		sVarType = n; 
		syscomData.sDataTyp = sVarType;
		this->SelectronVarType2VarLength(sVarType,& syscomData.iVarLengthBits,& syscomData.iVarLengthBytes, &syscomData.dtDataType, &syscomData.uiDataType);

	}
}

void CElement::getVarType(CString &n)
{
	
		n = sVarType;
}

void CElement::setDlgRunning(BOOL x)
{
	xDlgRunning = x;
}

void CElement::getDlgRunning(BOOL &x)
{
	x = xDlgRunning;
}


void CElement::setValue(CString n)
{
	sValue = n;
}

void CElement::getValue(CString &n)
{
	n = sValue;
}

HWND CElement::getMainWindowHnd()
{
	return (this->mainWindowHwnd);
}

CWnd *CElement::getMainWindowCwnd()
{
	return mainWindowCwnd;
}

void CElement::setLowestValue(CString n)
{
	sLowestValue = n;
}

void CElement::setHighestValue(CString n)
{
	sHighestValue = n;
}


void CElement::getLowestValue(CString& n)
{
	n = sLowestValue;
}

void CElement::getHighestValue(CString& n)
{
	n = sHighestValue;
}



void CElement::drawMagentaBorders(CDC* pDC, INT iXstep, INT iYstep)

{
	pDC->SetBkMode(TRANSPARENT);
	m_Color = RGB(200, 0, 100);
	m_PenWidth = 3;
	CPen aPen;
	aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	pDC->MoveTo(m_StartPoint.x, m_StartPoint.y);
	pDC->LineTo(m_StartPoint.x, m_StartPoint.y + iYstep);
	pDC->LineTo(m_StartPoint.x + iXstep, m_StartPoint.y + iYstep);
	pDC->LineTo(m_StartPoint.x + iXstep, m_StartPoint.y);
	pDC->LineTo(m_StartPoint.x, m_StartPoint.y);
	pDC->SelectObject(&pOldPen);
}

int CElement::SelectronVarType2VarLength(CString sVarType, DWORD * iVarLengthBits, DWORD * iVarLengthBytes, Data_Types *dtDataType, Data_Types *uiDataType)
{
	if (sVarType == _T("BOOL"))
	{
		//*iVarLengthBits = 1;
		*iVarLengthBits = 8;
		*iVarLengthBytes = 1;
		*dtDataType = svtBOOL;
		//*uiDataType = BIT1;
		*uiDataType = BIT8;
		return 0;
	}
	if (sVarType == _T("BYTE"))
	{
		*iVarLengthBits = 8;
		*iVarLengthBytes = 1;
		*dtDataType = svtBYTE;
		*uiDataType = BIT8;
		return 0;
	}
	if (sVarType == _T("WORD"))
	{
		*iVarLengthBits = 16;
		*iVarLengthBytes = 2;
		*dtDataType = svtWORD;
		*uiDataType = BIT16;
		return 0;
	}
	if (sVarType == _T("DWORD"))
	{
		*iVarLengthBits = 32;
		*iVarLengthBytes = 4;
		*dtDataType = svtDWORD;
		*uiDataType = BIT32;
		return 0;
	}
	if (sVarType == _T("SINT"))
	{
		*iVarLengthBits = 8;
		*iVarLengthBytes = 1;
		*dtDataType = svtSINT;
		*uiDataType = BIT8;
		return 0;
	}
	if (sVarType == _T("INT"))
	{
		*iVarLengthBits = 16;
		*iVarLengthBytes = 2;
		*dtDataType = svtINT;
		*uiDataType = BIT16;
		return 0;
	}
	if (sVarType == _T("DINT"))
	{
		*iVarLengthBits = 32;
		*iVarLengthBytes = 4;
		*dtDataType = svtDINT;
		*uiDataType = BIT32;
		return 0;
	}
	if (sVarType == _T("USINT"))
	{
		*iVarLengthBits = 8;
		*iVarLengthBytes = 1;
		*dtDataType = svtUSINT;
		*uiDataType = BIT8;
		return 0;
	}
	if (sVarType == _T("UINT"))
	{
		*iVarLengthBits = 16;
		*iVarLengthBytes = 2;
		*dtDataType = svtUINT;
		*uiDataType = BIT16;
		return 0;
	}
	if (sVarType == _T("UDINT"))
	{
		*iVarLengthBits = 32;
		*iVarLengthBytes = 4;
		*dtDataType = svtUDINT;
		*uiDataType = BIT32;
		return 0;
	}
	if (sVarType == _T("REAL"))
	{
		*iVarLengthBits = 32;
		*iVarLengthBytes = 4;
		*dtDataType = svtREAL;
		*uiDataType = BIT32;
		return 0;
	}
	if (sVarType == _T("LREAL"))
	{
		*iVarLengthBits = 64;
		*iVarLengthBytes = 8;
		*dtDataType = svtLREAL;
		*uiDataType = BIT64;
		return 0;
	}

	if (sVarType == _T("TIME"))
	{
		*iVarLengthBits = 32;
		*iVarLengthBytes = 4;
		*dtDataType = svtTIME;
		*uiDataType = BIT32;
		return 0;
	}

	if (sVarType == _T("DATE_AND_TIME"))
	{
		*iVarLengthBits = 32;
		*iVarLengthBytes = 4;
		*dtDataType = svtDATE_AND_TIME;
		*uiDataType = BIT32;
		return 0;
	}


	*iVarLengthBits = 0;
	*iVarLengthBytes = 0;
	*dtDataType = svtUNKNOWN;
	return 1;
}


void CElement::setmSketch(std::list<std::shared_ptr<CElement>> & msketch)
{
	//m_Sketch.assign(msketch.begin(), msketch.end());
	//m_Sketch = msketch;
	//p_Sketch.reset();
	p_Sketch = &msketch;
}