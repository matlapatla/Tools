#pragma once



// MFCClassChildOFCFormView

class MFCClassChildOFCFormView : public CWinApp
{
	DECLARE_DYNCREATE(MFCClassChildOFCFormView)

protected:
	MFCClassChildOFCFormView();           // protected constructor used by dynamic creation
	virtual ~MFCClassChildOFCFormView();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


