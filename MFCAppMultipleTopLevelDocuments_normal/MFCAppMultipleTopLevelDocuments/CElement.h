#pragma once
#include <algorithm>

#include <list>
#include <memory> // for std::shared_ptr


// CElement command target
static const UINT VERSION_NUMBER{ 1001 }; // Version number for serialization

class CElement;

typedef enum data_type
{
	BIT1 = 0, //BIT
	BIT8 = 1, //BYTE
	BIT16 = 2, //WORD
	BIT32 = 3, //DWORD
	BIT64 = 4,
	svtBOOL,  //svt stands for Selectron VarType 
	svtBYTE,
	svtWORD,
	svtDWORD,
	svtSINT,
	svtINT,
	svtDINT,
	svtUSINT,
	svtUINT,
	svtUDINT,
	svtREAL,
	svtLREAL,
	svtTIME,
	svtDATE_AND_TIME,
	svtUNKNOWN
} Data_Types;

struct syscomItem : public CObject
{
	INT adress; //prijde smazat
	data_type dataTyp;//prijde smazat
	CHAR * name;//prijde smazat
	union value_t {
		bool boolValue; //1 byte
		char byteValue; //1 byte ????
		char charValue; //1 byte ?????
		unsigned char unsignedCharValue; //1byte
		signed char signedCharValue; //1byte

		short shortValue; //2bytes
		unsigned short unsignedShortValue;

		float floatValue; //4bytes
		int intValue;   //4 bytes
		unsigned int unsignedIntValue;
		long longValue;
		unsigned long unsignedLongValue;

		double doubleValue; //8bytes
		long double longDoubleValue;
		long long longLongValue;

	} value;

	std::shared_ptr<CElement> m_pElement;
	CString sName;
	CString sDataTyp;
	DWORD iVarLengthBits;
	DWORD iVarLengthBytes;
	Data_Types dtDataType;
	Data_Types uiDataType;
	ULONG ulAbsAddress;

};


class CElement : public CObject
{
	DECLARE_SERIAL(CElement)
	
protected:
	CString dummy{""};
	CPoint m_StartPoint = {0,0}; // Element position
	int m_PenWidth; // Pen width
	COLORREF m_Color; // Color of an element
	CRect m_EnclosingRect; // Rectangle enclosing an element
	CRect m_MyRect;
	CSize m_MySize;
	CString m_TypeOfElement;

	INT iItemListIndex;
	ULONG ulAbsAddress;
	CString sVarType;
	CString sValue;
	CString sLowestValue;
	CString sHighestValue;
	std::shared_ptr<CElement> m_pPlc;
	CString sElementName;
	CString sPlcName;
	
	BOOL xDlgRunning;

public:
	virtual void getTypeOfElement(CString & elemType);
	virtual ~CElement();
	//virtual void AssertValid() const;

	virtual void Draw(CDC* pDC) {} // Virtual draw operation
	virtual INT DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect, HWND hObjectHandle) { return 0; }
	virtual void SetStatus(INT newStatus) {};
	// Get the element enclosing rectangle
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
	virtual void Serialize(CArchive& ar) override; // Serialize object
	virtual void setName(CString n) {};
	virtual void setAccessPath(CString path) {};
	virtual void setConfigString(CString string) {};
	virtual CString getName(void) { return dummy; };
	virtual CString getAccessPath(void) { return dummy; };
	virtual CString getConfigString(void) { return dummy; };

	void setElementName(CString n);
	void setPlcName(CString n);
    void setElementAddress(CString n);
	void setVarType(CString n);
	void setValue(CString n);

	void getElementName(CString &n);
	void getPlcName(CString &n);
	void getElementAddress(CString &n);
	void getVarType(CString &n);
	void getValue(CString &n);
	HWND getMainWindowHnd();
	CWnd* getMainWindowCwnd();

	void setDlgRunning(BOOL x);
	void getDlgRunning(BOOL &x);

	void drawMagentaBorders(CDC* pDC, INT iXstep, INT iYstep);
	void setmSketch(std::list<std::shared_ptr<CElement>> & msketch);
	syscomItem syscomData;

	int SelectronVarType2VarLength(CString sVarType, DWORD * iVarLengthBits, DWORD * iVarLengthBytes, Data_Types *dataType, Data_Types *uiDataType);

	//virtual void updateValue; tady se bude updatovat hodnota 

	void setLowestValue(CString n);
	void setHighestValue(CString n);
	void getLowestValue(CString &n);
	void getHighestValue(CString &n);

protected:
	// Constructors protected so they cannot be called outside the class
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);

	std::list<std::shared_ptr<CElement>> m_Sketch;
	std::list<std::shared_ptr<CElement>> * p_Sketch;

	HWND mainWindowHwnd;
	CWnd* mainWindowCwnd;
	

};


