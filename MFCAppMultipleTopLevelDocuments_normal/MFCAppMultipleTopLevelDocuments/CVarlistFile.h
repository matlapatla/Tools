#pragma once

// CVarlistFile command target

class CVarlistFile : public CObject
{
public:
	CVarlistFile();
	virtual ~CVarlistFile();
	INT OpenVarlistFile(TCHAR*);

protected:
	CFile CphysicalFile;
	CString ConeLine;
	CFileException fileException;
};


