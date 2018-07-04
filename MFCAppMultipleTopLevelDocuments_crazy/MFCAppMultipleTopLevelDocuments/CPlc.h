#pragma once
#include "CElement.h"
#include "SysComServer.h"




#define WM_REFRESHPICTURE (WM_USER + 100)
#define MAXITEMLIST 148

//controlling function header
static UINT lifeGuard(LPVOID Param);
static BOOL stopLifeGuardNow;
static struct lifeGuardStruct {
	LPVOID  pCplc = nullptr;
	HWND hWndParent;
	LPVOID pDLg = nullptr;
} lifeGuardPars;
/* 
typedef enum data_type
{
	BIT1 = 0,
	BIT8 = 1,
	BIT16 = 2,
	BIT32 = 3,
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
	svtUNKNOWN
} Data_Types;

struct item
{
	INT adress;
	data_type dataTyp;
	CHAR * name;
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

	CString sDataTyp;
	DWORD iVarLengthBits;
	DWORD iVarLengthBytes;
	Data_Types dtDataType;
	ULONG ulAbsAddress;

};

*/

class CPlc :
	public CElement
{
	DECLARE_SERIAL(CPlc)
public:
	CPlc();
	CPlc(CPoint startPoint);
	~CPlc();

	int connect(void);
	int disconnect(void);
	int startLifeGuard(HWND);
	int stopLifeGuard(HWND, LPVOID);
	//int lifeGuard(LPVOID Param);
	int callMASReadItem(CString, CString, CString &);
	int callMASForceAddAbsolute(CString, CString, CString);
	int callMASForceRemoveAbsolut(CString, CString, CString);
	int callMASWriteItemAbsolute(CString, CString, CString);
	HRESULT Set_MonitorList( );
	HRESULT Read_MonitorList( );
	HRESULT Get_MonitorListState();
	int CPlc::GenerateMonitorList();

	INT DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint = { 0,0 }, INT iXstep = 50, INT iYstep = 50, CRect* pRect = nullptr, HWND hObjectHandle = NULL);
	void SetStatus(INT newStatus);
	virtual void Serialize(CArchive& ar) override; // Serialize object


	
	virtual void setName(CString n);
	virtual void setAccessPath(CString path);
	virtual void setConfigString(CString string);
	virtual CString getName(void);
	virtual CString getAccessPath(void);
	virtual CString getConfigString(void);
	INT getState();
	/*
	void setTimeOut(int time);
	Srv_Info_Proj_T getInfoProject(void);
	bool getConnected(void);
	CHAR* getAccessPath(void);
	CHAR* getConfigString(void);
	CHAR* getName(void);
	HANDLE getServer(void);
	int getTimeOut(void);
	*/

private:
	
	CHAR name[64];
	
	CHAR accessPath[64];
	
	CHAR configString[64];
	
	Srv_Info_Proj_T infoProject;
	bool connected;
	INT timeOut = 10000;
	CHAR user[64] = "user_0";	
	CHAR pass[64] = "sele0";
	CString sName;
	CString sAccessPath;
	CString sConfigString;
	CString sUser;
	CString sPass;
	CString Text;

	int itemCount = 0;
	syscomItem ItemList[MAXITEMLIST];
	syscomItem oneItem;

	Srv_cmd_IO_DefMonList_T         DefMonList;
	Srv_cmd_IO_ReadMonList_T        ReadMonList;
	
public:
	HANDLE server;
	HRESULT hResult;
	ASYNC_T asnc;
	INT timeOutLifeGuard = 5000;
	enum plcStatus_t { unknownPlc, notConnectedPlc, connectedPlc, lifeGuardPlcOK, lifeGuardPlcNOK, lifeGuardPlcDsbl };
	plcStatus_t m_plcStatus;

protected:	
	CString m_sIconFileNameConnected;
	CString m_sIconFileNameNotConnected;
	CString m_sIconFileNameUnknown;
	CString m_sIconFileNameLifeGuardNOK;
	CString m_sIconFileNameLifeGuardOK;
	HBITMAP m_hBmpCon;
	HBITMAP m_hBmpNotCon;
	HBITMAP m_hBmpUnknown;
	HBITMAP m_hBmpLifeGuardNOK;
	HBITMAP m_hBmpLifeGuardOK;

//public:
	//int SelectronVarType2VarLength(CString sVarType, DWORD * iVarLengthBits, DWORD * iVarLengthBytes, Data_Types *dataType, Data_Types *uiDataType);
};


