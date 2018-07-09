#pragma once
#include <list>
// CVarlistFile command target

class CVarlistFile : public CObject
{
public:
	CVarlistFile();
	virtual ~CVarlistFile();
	INT OpenAndReadVarlistFile(TCHAR*);
	INT GetListOfLines(std::list<CString> & ListOfLines);

protected:
	//CFile CphysicalFile;
	CStdioFile CPhysicalFile;
	CString COneLine;
	CFileException fileException;
	std::list<CString> Lines;
};


