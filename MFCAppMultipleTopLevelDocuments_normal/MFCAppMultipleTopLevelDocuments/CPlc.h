#pragma once
#include "CElement.h"
#include "SysComServer.h"
#include "CVarlistFile.h"
#include <memory> // for std::shared_ptr




#define WM_REFRESHPICTURE (WM_USER + 100)
#define MAXITEMLIST 148

//controlling function header
static UINT lifeGuard(LPVOID Param);
static UINT ReadMonitorListPeriodicProc(LPVOID pParam);

static BOOL stopLifeGuardNow;
static struct lifeGuardStruct {
	LPVOID  pCplc = nullptr;
	HWND hWndParent;
	LPVOID pDLg = nullptr;
} lifeGuardPars;

static struct PlcBackgroundReadWriteStruct {

	CElement* pSelected;
	BOOL stopReadMonitorListPeriodic;
} PlcBackgroundReadWritePars;

class CPlc :
	public CElement
{
	DECLARE_SERIAL(CPlc)
public:
	CPlc();
	CPlc(CPoint startPoint, CMainFrame* pFrame);
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

	INT DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint = { 0,0 }, INT iXstep = 50, INT iYstep = 50, CRect* pRect = nullptr, HWND hObjectHandle = NULL, CMainFrame* MFrame = nullptr);
	void SetStatus(INT newStatus);
	virtual void Serialize(CArchive& ar) override; // Serialize object


	
	virtual void setName(CString n);
	virtual void setAccessPath(CString path);
	virtual void setConfigString(CString string);
    virtual void setVarlistFilePath(CString path);
	virtual CString getName(void);
	virtual CString getAccessPath(void);
	virtual CString getConfigString(void);
	virtual CString getVarlistFilePath(void);
	INT getState();
	void SearchInVarlist(CString m_CStringSearchedInVarlist);

	void setDialogMasReadItemValues(CString, CString, CString);
	void getDialogMasReadItemValues(CString &, CString &, CString &);

	void Read_MonitorListPeriodicStart(INT);
	void Read_MonitorListPeriodicStop();
	void InformPlc(BOOL);

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

	CString VarlistFilePath;
	//CVarlistFile Varlist;
	//std::shared_ptr<CVarlistFile> VarlistPtr;
	std::shared_ptr<CVarlistView> VarlistViewPtr;
	std::shared_ptr<CVarlistView> VarlistViewPtrFound;

	int itemCount = 0;
	syscomItem ItemList[MAXITEMLIST];
	syscomItem oneItem;

	Srv_cmd_IO_DefMonList_T         DefMonList;
	Srv_cmd_IO_ReadMonList_T        ReadMonList;

	struct DialogMasReadItemVars {
		CString VariableVarlistName;
		CString VariableVarlistAdrress;
		CString VariableVarlistType;
	} DialogMasReadItemVar;
	
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

	BOOL ReadMonitorListPeriodicRunning;

	

};


