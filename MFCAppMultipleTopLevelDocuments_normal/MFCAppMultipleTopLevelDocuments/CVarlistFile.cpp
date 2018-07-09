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
INT CVarlistFile::OpenAndReadVarlistFile(TCHAR* pszFileName)
{
	if (!CPhysicalFile.Open(pszFileName, 
		CFile::modeRead, &fileException))
	{
		TRACE(_T("Can't open file %s, error = %u\n"),
			pszFileName, fileException.m_cause);
		AfxMessageBox(L"The Varlist file was not opened.");
		return -1;
	}
	while (CPhysicalFile.ReadString(COneLine))
	{		
		Lines.push_back(COneLine);
	}
	CPhysicalFile.Close();

	return 0;
}

INT CVarlistFile::GetListOfLines(std::list<CString> & ListOfLines)

{
	ListOfLines = Lines;
	return 0;
}