// CVarlistFile.cpp : implementation file
//

#include "stdafx.h"
#include "MFCAppMultipleTopLevelDocuments.h"
#include "CVarlistFile.h"


// CVarlistFile

CVarlistFile::CVarlistFile()
{
}

CVarlistFile::~CVarlistFile()
{
}


// CVarlistFile member functions
INT CVarlistFile::OpenVarlistFile(TCHAR* pszFileName)
{
	if (!CphysicalFile.Open(pszFileName, 
		CFile::modeRead, &fileException))
	{
		TRACE(_T("Can't open file %s, error = %u\n"),
			pszFileName, fileException.m_cause);
		AfxMessageBox(L"The Varlist file was not opened.");
	}
	return 0;
}

