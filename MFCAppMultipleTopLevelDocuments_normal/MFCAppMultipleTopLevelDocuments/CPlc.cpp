#include "stdafx.h"
#include "CPlc.h"
#include "Resource.h"


IMPLEMENT_SERIAL(CPlc, CElement, 1001)
//#define WM_REFRESHPICTURE (WM_USER + 100)

CPlc::CPlc()
{

	m_plcStatus = unknownPlc;
	m_sIconFileNameConnected = L"C:\\plcCon.bmp";
	m_sIconFileNameNotConnected = L"C:\\plcNotCon.bmp";
	m_sIconFileNameUnknown = L"C:\\plcUnk.bmp";
	m_sIconFileNameLifeGuardNOK = L"C:\\plcLGNok.bmp";
	m_sIconFileNameLifeGuardOK = L"C:\\plcLGOk.bmp";

	m_hBmpCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpNotCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameNotConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);


	m_hBmpLifeGuardNOK = (HBITMAP)::LoadImage(NULL, m_sIconFileNameLifeGuardNOK,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hBmpLifeGuardOK = (HBITMAP)::LoadImage(NULL, m_sIconFileNameLifeGuardOK,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	connected = false;
	m_TypeOfElement = L"CPlc";

	 sName = "my_server";
	 sAccessPath = "LAN,192.168.0.253:1065";
	 sConfigString = "MEDIANAME=LAN IP_HOST=192.168.0.9 TO_INHIBIT=1 TO_ACK=0";
	 sUser = "user_0";
	 sPass = "sele0";
	 
	 
}

CPlc::CPlc(CPoint startPoint, CMainFrame* pFrame)
	: m_sIconFileNameUnknown(_T(""))
{
	m_plcStatus = unknownPlc;
	m_sIconFileNameConnected = L"C:\\plcCon.bmp";
	m_sIconFileNameNotConnected = L"C:\\plcNotCon.bmp";
	m_sIconFileNameUnknown = L"C:\\plcUnk.bmp";
	m_sIconFileNameLifeGuardNOK = L"C:\\plcLGNok.bmp";
	m_sIconFileNameLifeGuardOK = L"C:\\plcLGOk.bmp";

	m_hBmpCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpNotCon = (HBITMAP)::LoadImage(NULL, m_sIconFileNameNotConnected,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hBmpUnknown = (HBITMAP)::LoadImage(NULL, m_sIconFileNameUnknown,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hBmpLifeGuardNOK = (HBITMAP)::LoadImage(NULL, m_sIconFileNameLifeGuardNOK,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hBmpLifeGuardOK = (HBITMAP)::LoadImage(NULL, m_sIconFileNameLifeGuardOK,
		IMAGE_BITMAP, 0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	connected = false;
	m_TypeOfElement = L"CPlc";
	m_StartPoint = startPoint;

	sName = "my_server";
	sAccessPath = "LAN,192.168.0.253:1065";
	sConfigString = "MEDIANAME=LAN IP_HOST=192.168.0.9 TO_INHIBIT=1 TO_ACK=0";
	sUser = "user_0";
	sPass = "sele0";


	pMainFrame = pFrame;
}


CPlc::~CPlc()
{
	if (connected)
	{
		disconnect();
	}
}

int CPlc::connect(void)
{
	HRESULT hResult;
	server = MAS_CreateSysComServerEx((LPCTSTR)name, (LPCTSTR)accessPath, (LPCTSTR)configString);
	if (server == NULL)
	{
		m_plcStatus = notConnectedPlc;
		AfxMessageBox(L"MAS_CreateSysComServerEx failed.");
		return -1;
	}
	hResult = MAS_Login(server, (LPCTSTR)user, (LPCTSTR)pass, NULL, timeOut);
	if (hResult < 0)
	{
		m_plcStatus = notConnectedPlc;
		AfxMessageBox(L"MAS_Login failed.");
		return -1;
	}
	hResult = MAS_GetInfoProject(server, SRV_DST_RAM, &(infoProject),
		NULL, timeOut);
	if (hResult < 0)
	{
		m_plcStatus = notConnectedPlc;
		AfxMessageBox(L"MAS_GetInfoProject failed.");
		return -1;
	}
	CString Text = CString(infoProject.Text);
	m_plcStatus = connectedPlc;
	connected = true;
	AfxMessageBox(Text);
	//MessageBox
	
	return 0;
}

int CPlc::startLifeGuard(HWND hWdnView)
{
	if (connected)
	{
		lifeGuardStruct * pLifeGuardPars;
		pLifeGuardPars = &lifeGuardPars;
		CPlc * pPlc = dynamic_cast<CPlc*>(this);
		pLifeGuardPars->pCplc = pPlc;
		pLifeGuardPars->hWndParent = hWdnView;
		//pLifeGuardPars->parent =  (CMFCAppMultipleTopLevelDocumentsView*)GetParent();
		//pLifeGuardPars->parentowner = GetParentOwner();
		//pLifeGuardPars->ptr = (CMFCAppMultipleTopLevelDocumentsView*) this->GetParent();
		stopLifeGuardNow = false;
		AfxBeginThread(lifeGuard, pLifeGuardPars);
		
		return 0;
	}
	else
	{
		stopLifeGuardNow = true;
		AfxMessageBox(L"Not able to start LifeGuard - PLC not connected.");
		return 1;
	}

}

int CPlc::stopLifeGuard(HWND hWdnView, LPVOID ptrDLg)
{
	if (connected)
	{
		lifeGuardStruct * pLifeGuardPars;
		pLifeGuardPars = &lifeGuardPars;
		CPlc * pPlc = dynamic_cast<CPlc*>(this);
		pLifeGuardPars->pCplc = pPlc;
		pLifeGuardPars->hWndParent = hWdnView;	
		pLifeGuardPars->pDLg = ptrDLg;
		pPlc->m_plcStatus = pPlc->lifeGuardPlcDsbl;
		stopLifeGuardNow = true;

		return 0;
	}
	else
	{
		stopLifeGuardNow = true;
		AfxMessageBox(L"Not able to stop LifeGuard - PLC not connected.");
		return 1;
	}

}


UINT lifeGuard(LPVOID Param)
{
	UINT counterWAIT_TIMEOUT = 0;
	lifeGuardStruct * pPars = (lifeGuardStruct*) Param;
		CPlc * pPlc = (CPlc*)(pPars->pCplc);	

		if (pPlc->m_plcStatus == pPlc->connectedPlc)
		{
			pPlc->asnc.hEvent = MAS_CreateEvent();	 //Create a Event
			pPlc->asnc.lpBuffer = &(pPlc->timeOutLifeGuard);            //Set the TimeOut of the Lifeguarding
			pPlc->hResult = MAS_EnableLifeguarding(pPlc->server, true, &(pPlc->asnc));	//Start Lifeguarding 
			pPlc->m_plcStatus = pPlc->lifeGuardPlcOK;
			PostMessage(pPars->hWndParent, WM_REFRESHPICTURE, 0, 0);
	
			if (pPlc->hResult == S_OK)
			{

				while (!stopLifeGuardNow)
				{
					int WaitObject = WaitForSingleObject(pPlc->asnc.hEvent, 30000);  //Wait 30sec for a cable interruption 

					if (WaitObject != WAIT_TIMEOUT)
					{
						pPlc->m_plcStatus = pPlc->lifeGuardPlcNOK;
						PostMessage(pPars->hWndParent, WM_REFRESHPICTURE, 0, 0);

						return 1;
					}
					else
					{
						counterWAIT_TIMEOUT++;
					}
				}
				if (pPlc->m_plcStatus == pPlc->lifeGuardPlcDsbl)
				{
					pPlc->hResult = MAS_EnableLifeguarding(pPlc->server, false, &(pPlc->asnc));
				}				
				pPlc->m_plcStatus = pPlc->connectedPlc;
				
				PostMessage(pPars->hWndParent, WM_REFRESHPICTURE,(WPARAM) (pPars->pDLg), 0);
			}
			else
			{
				AfxMessageBox(L"AfxBeginThread Not passed.");
				return 2;
			}
		}
	return 0;
}




int CPlc::disconnect(void)
{
	HRESULT hResult;
	hResult = MAS_Logout(server, timeOut);
	if (hResult < 0)
	{
		AfxMessageBox(L"MAS_Logout failed.");
		return -1;
	}
	hResult = MAS_DestroySysComServer(server);
	if (hResult < 0)
	{
		AfxMessageBox(L"MAS_DestroySysComServer failed.");
		return -1;
	}
	m_plcStatus = notConnectedPlc;
	connected = false;
	AfxMessageBox(L"PLC disconnected.");
	
	return 0;
}

INT CPlc::DrawElement(CDC* pDC, CWnd* pView, CPoint startPoint, INT iXstep, INT iYstep, CRect* pRect, HWND hObjectHandle, CMainFrame* MFrame)
{
	mainWindowHwnd = hObjectHandle;
	mainWindowCwnd = pView;
	pMainFrame = MFrame;

	if (m_StartPoint.x == 0 && m_StartPoint.y == 0)
	{
		m_StartPoint = startPoint;
	}

	CBitmap bmp;
	switch (m_plcStatus) {
	case connectedPlc:
		bmp.Attach(m_hBmpCon);
		break;
	case notConnectedPlc:
		bmp.Attach(m_hBmpNotCon);
		break;
	case unknownPlc:
		bmp.Attach(m_hBmpUnknown);
		break;

	case lifeGuardPlcOK:
		bmp.Attach(m_hBmpLifeGuardOK);
		break;

	case lifeGuardPlcDsbl:
		bmp.Attach(m_hBmpLifeGuardOK);
		break;

	case lifeGuardPlcNOK:
		bmp.Attach(m_hBmpLifeGuardNOK);
		break;

	default:

		break;
	}

	CClientDC dc(pView);
	CClientDC aDC{ pView };
	CDC bmDC;
	bmDC.CreateCompatibleDC(&dc);
	CBitmap *pOldbmp = bmDC.SelectObject(&bmp);

	BITMAP  bi;
	bmp.GetBitmap(&bi);
	((CScrollView*)pView)->OnPrepareDC(&aDC);
	RECT point{ m_StartPoint.x , m_StartPoint.y, m_StartPoint.x + iXstep, m_StartPoint.y + iYstep };
	aDC.LPtoDP(&point);
	dc.StretchBlt(point.left, point.top, (point.right - point.left), (point.bottom - point.top), &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	bmp.Detach();

	m_EnclosingRect = CRect{
		(std::min)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::min)(m_StartPoint.y, m_StartPoint.y + iYstep),
		(std::max)(m_StartPoint.x, m_StartPoint.x + iXstep), (std::max)(m_StartPoint.y, m_StartPoint.y + iYstep) };

	return 0;

}

void CPlc::SetStatus(INT newStatus)
{
	switch (newStatus)
	{
	case 0:
		m_plcStatus = unknownPlc;
		break;
	case 1:
		m_plcStatus = notConnectedPlc;
		break;
	case 2:
		m_plcStatus = connectedPlc;
		break;
	default:
		m_plcStatus = unknownPlc;
		break;

	}
}

void CPlc::Serialize(CArchive& ar)
{
	CElement::Serialize(ar); // Call the base class function
	if (ar.IsStoring())
	{ // Writing to the file
		ar << m_sIconFileNameConnected
			<< m_sIconFileNameNotConnected
			<< m_sIconFileNameUnknown

			<< sName
			<< sAccessPath
			<< sConfigString
			<< sUser
			<< sPass;

	}
	else
	{ // Reading from the file
		ar >> m_sIconFileNameConnected
			>> m_sIconFileNameNotConnected
			>> m_sIconFileNameUnknown
			
			>> this->sName
			>> this->sAccessPath
			>> this->sConfigString
			>> sUser
			>> sPass;

		setName(sName);
		setAccessPath(sAccessPath);
		setConfigString(sConfigString);
			
	}
}

void CPlc::setName(CString n)
{
	sName = n;
	strcpy_s(name, CStringA(n).GetString());
}

void CPlc::setAccessPath(CString path)
{
	sAccessPath = path;
	strcpy_s(accessPath, CStringA(path).GetString());
}

void CPlc::setConfigString(CString string)
{
	sConfigString = string;
	strcpy_s(configString, CStringA(string).GetString());
}

void CPlc::setVarlistFilePath(CString path)
{
	VarlistFilePath = path;
	TCHAR buf[1024];
	_tcscpy_s(buf, path);
	Varlist.OpenAndReadVarlistFile(buf);
	pMainFrame->AddDockingWindow();
	
}

CString CPlc::getVarlistFilePath(void)
{
	return (VarlistFilePath);
}

CString CPlc:: getName()
{
   return 	sName;
}
CString CPlc::getAccessPath()
{
	return sAccessPath;
}
CString CPlc::getConfigString()
{
	return sConfigString;
}

INT CPlc::getState()
{
	if (m_plcStatus != connectedPlc)
	{
		return 0;
	}
	return -1;

}

int CPlc::callMASReadItem(CString varAbsAddr, CString SelectronVarType, CString& sData)

{
	try
	{
		int iTempVar;
		int iData[256];
		float fData;
		double dData;
		int * piData;
		float * pfData;
		double * pdData;

		//LPVOID pData;
		iData[0] = 0;
		fData = 0;
		dData = 0;
		piData = iData;
		pfData = &fData;
		pdData = &dData;
		DWORD dwDataLength;
		DWORD dwTimeout = 10000;
		//ULONG ulAbsAddress;

		BOOL babTempvar;
		CHAR cabTempvar;
		SHORT nabTempVar;
		INT iabTempVar;
		CHAR caiTempvar;
		SHORT naiTempVar;
		INT iaiTempVar;
		UCHAR cai1Tempvar;
		USHORT nai1TempVar;
		UINT iai1TempVar;
		FLOAT fTempvar;
		DOUBLE dTempvar;

		unsigned __int64 ui64;
		_stscanf_s((LPCTSTR)SelectronVarType, _T("%I64u"), &ui64);
		dwDataLength = ui64;
		_stscanf_s((LPCTSTR)varAbsAddr, _T("%I64u"), &ui64);
		
		oneItem.ulAbsAddress = ui64;
		oneItem.sDataTyp = SelectronVarType;
		if (0 == this->SelectronVarType2VarLength(SelectronVarType, &oneItem.iVarLengthBits, &oneItem.iVarLengthBytes, &oneItem.dtDataType, &oneItem.uiDataType))
		{
			if (oneItem.dtDataType == svtREAL)
			{
				HRESULT hResult = MAS_ReadItemAbsolut(server, oneItem.ulAbsAddress, pfData, oneItem.iVarLengthBytes, dwTimeout);
				fTempvar = static_cast<float>(*pfData);
				sData.Format(_T("%f"), fTempvar);
			}
			else if (oneItem.dtDataType == svtLREAL)
			{
				HRESULT hResult = MAS_ReadItemAbsolut(server, oneItem.ulAbsAddress, pdData, oneItem.iVarLengthBytes, dwTimeout);
				dTempvar = static_cast<double>(*pdData);
				sData.Format(_T("%f"), dTempvar);
			}
			else
			{
				HRESULT hResult = MAS_ReadItemAbsolut(server, oneItem.ulAbsAddress, piData, oneItem.iVarLengthBytes, dwTimeout);
				switch (oneItem.dtDataType)
				{
				case svtBOOL:
					//.ab.... stand for the ANY_BIT data types
					babTempvar = static_cast<bool> (*piData);
					sData.Format(_T("%d"), babTempvar);
					break;
				case svtBYTE:
					cabTempvar = static_cast<char> (*piData);
					sData.Format(_T("%d"), cabTempvar);
					break;
				case svtWORD:
					nabTempVar = static_cast<short> (*piData);
					sData.Format(_T("%d"), nabTempVar);
					break;
				case svtDWORD:
					iabTempVar = static_cast<int> (*piData);
					sData.Format(_T("%d"), iabTempVar);
					break;
					//.ai.... stand for the ANY_INT data types
				case svtSINT:
					caiTempvar = static_cast<char>(*piData);
					sData.Format(_T("%d"), caiTempvar);
					break;
				case svtINT:
					naiTempVar = static_cast<short> (*piData);
					sData.Format(_T("%d"), naiTempVar);
					break;
				case svtDINT:
					iaiTempVar = static_cast<INT> (*piData);
					sData.Format(_T("%d"), iaiTempVar);
					break;

				case svtUSINT:
					cai1Tempvar = static_cast<UCHAR>(*piData);
					sData.Format(_T("%d"), cai1Tempvar);
					break;
				case svtUINT:
					nai1TempVar = static_cast<USHORT> (*piData);
					sData.Format(_T("%d"), nai1TempVar);
					break;
				case svtUDINT:
					iai1TempVar = static_cast<UINT> (*piData);
					sData.Format(_T("%d"), iai1TempVar);
					break;
				case svtTIME:
					iai1TempVar = static_cast<UINT> (*piData);
					sData.Format(_T("%d"), iai1TempVar);
					break;
				case svtDATE_AND_TIME:
					iai1TempVar = static_cast<UINT> (*piData);
					sData.Format(_T("%d"), iai1TempVar);
					break;
					
				default:
					AfxMessageBox(L"Selectron data type conversion not known.");
					break;
				}
			}
		}
		else
		{
			oneItem.sDataTyp = L"unknown";
			AfxMessageBox(L"Selectron data type is unknown.");
		}
		
	}
	catch (CException* e)
	{
		
		MessageBoxW(NULL, L"Problem in the callMASReadItem.", NULL, MB_OK);
	}
	return 0;
}

int CPlc::callMASForceAddAbsolute(CString varAbsAddr, CString SelectronVarType, CString sData)

{

	float fData;
	float * pfData;
	double dData;
	double * pdData;
	int iData[256];
	int * piData;
	iData[0] = 0;
	fData = 0;
	dData = 0;

	DWORD dwDataLength;
	DWORD dwTimeout = 10000;
	unsigned __int64 ui64;
	_stscanf_s((LPCTSTR)SelectronVarType, _T("%I64u"), &ui64);
	dwDataLength = ui64;
	_stscanf_s((LPCTSTR)varAbsAddr, _T("%I64u"), &ui64);
	oneItem.ulAbsAddress = ui64;
	oneItem.sDataTyp = SelectronVarType;


	if (0 == this->SelectronVarType2VarLength(SelectronVarType, &oneItem.iVarLengthBits, &oneItem.iVarLengthBytes, &oneItem.dtDataType, &oneItem.uiDataType))
	{

		if (oneItem.dtDataType == svtREAL)
		{
			fData = _wtof(sData);
			//fData = wcstof(sData, );
			pfData = &fData;
			HRESULT hResult = MAS_ForceAddAbsolut(server, oneItem.ulAbsAddress, pfData, oneItem.iVarLengthBytes, dwTimeout);
		}
		else if (oneItem.dtDataType == svtLREAL)
		{
			dData = _wtof(sData);
			pdData = &dData;
			HRESULT hResult = MAS_ForceAddAbsolut(server, oneItem.ulAbsAddress, pdData, oneItem.iVarLengthBytes, dwTimeout);
		}
		else
		{
			iData[0] = _wtoi(sData);
			piData = iData;
			HRESULT hResult = MAS_ForceAddAbsolut(server, oneItem.ulAbsAddress, piData, oneItem.iVarLengthBytes, dwTimeout);

		}
	}

	return (0);
}

int CPlc::callMASForceRemoveAbsolut(CString varAbsAddr, CString SelectronVarType, CString sData)

{
	DWORD dwTimeout = 10000;

	if (0 == this->SelectronVarType2VarLength(SelectronVarType, &oneItem.iVarLengthBits, &oneItem.iVarLengthBytes, &oneItem.dtDataType, &oneItem.uiDataType))
	{
		
		HRESULT hResult = MAS_ForceRemoveAbsolut(server, oneItem.ulAbsAddress, oneItem.iVarLengthBytes, dwTimeout);		
	}
	return (0);	
}

int CPlc::callMASWriteItemAbsolute(CString varAbsAddr, CString SelectronVarType, CString sData)

{

	float fData;
	float * pfData;
	double dData;
	double * pdData;
	int iData[256];
	int * piData;
	iData[0] = 0;
	fData = 0;
	dData = 0;

	DWORD dwDataLength;
	DWORD dwTimeout = 10000;
	unsigned __int64 ui64;
	_stscanf_s((LPCTSTR)SelectronVarType, _T("%I64u"), &ui64);
	dwDataLength = ui64;
	_stscanf_s((LPCTSTR)varAbsAddr, _T("%I64u"), &ui64);
	oneItem.ulAbsAddress = ui64;
	oneItem.sDataTyp = SelectronVarType;


	if (0 == this->SelectronVarType2VarLength(SelectronVarType, &oneItem.iVarLengthBits, &oneItem.iVarLengthBytes, &oneItem.dtDataType, &oneItem.uiDataType))
	{

		if (oneItem.dtDataType == svtREAL)
		{
			fData = _wtof(sData);
			//fData = wcstof(sData, );
			pfData = &fData;
			HRESULT hResult = MAS_WriteItemAbsolut(server, oneItem.ulAbsAddress, pfData, oneItem.iVarLengthBytes, dwTimeout);
		}
		else if (oneItem.dtDataType == svtLREAL)
		{
			dData = _wtof(sData);
			pdData = &dData;
			HRESULT hResult = MAS_WriteItemAbsolut(server, oneItem.ulAbsAddress, pdData, oneItem.iVarLengthBytes, dwTimeout);
		}
		else
		{
			iData[0] = _wtoi(sData);
			piData = iData;
			HRESULT hResult = MAS_WriteItemAbsolut(server, oneItem.ulAbsAddress, piData, oneItem.iVarLengthBytes, dwTimeout);

		}
	}

	return (0);
}



int CPlc::GenerateMonitorList()
{
	
	// projdi vsechny definivane elementy v ...Doc.h m_Sketch  a zarad je do pole ItemList
	
	INT ii = 0;
	//for (const auto& pElement : m_Sketch)
	for (const auto& pElement : *p_Sketch)
	{
		CString sElementPlcName;
		pElement->getPlcName(sElementPlcName);
		if (sElementPlcName == sName)
		{
			//if (pElement->GetEnclosingRect().PtInRect(point))
			//	return pElement;
			ItemList[ii].m_pElement = pElement;
			ItemList[ii].sName = pElement->syscomData.sName;
			ItemList[ii].ulAbsAddress = pElement->syscomData.ulAbsAddress;
			ItemList[ii].dtDataType = pElement->syscomData.dtDataType;
			ItemList[ii].uiDataType = pElement->syscomData.uiDataType;
			ii++;
		}
	}
	
	itemCount = ii;
	return 0;
}

//HRESULT CPlc::Read_MonitorList(item ItemList[], int count)
HRESULT CPlc::Read_MonitorList()
{
	int iTempVar;
	CString sTempVar;

	BOOL babTempvar;
	CHAR cabTempvar;
	SHORT nabTempVar;
	INT iabTempVar;
	CHAR caiTempvar;
	SHORT naiTempVar;
	INT iaiTempVar;
	UCHAR cai1Tempvar;
	USHORT nai1TempVar;
	UINT iai1TempVar;
	FLOAT fTempvar;
	DOUBLE dTempvar;

	HRESULT	hResult;
	
	//Create a Srv_cmd_IO_ReadMonList_T struct
	//Srv_cmd_IO_ReadMonList_T        ReadMonList;
	//Set the size for the ReadMonList
	ReadMonList.len = sizeof(Srv_cmd_IO_ReadMonList_T);
	ReadMonList.ListNr = 0;
	ReadMonList.TacCount = 0;
	//Get the data from The PLC
	hResult = MAS_ReadMonitorList(server, &ReadMonList, NULL, timeOut);
	BYTE * pData = ReadMonList.Data;
	//Copy data to the items
	for (int i = 0; i< itemCount; i++)
	{
		//-----------------------------------------------
	  
		switch (ItemList[i].dtDataType)
		{
		case svtREAL:
		{
			memcpy(&(ItemList[i].value.floatValue), pData, sizeof(ItemList[i].value.floatValue));
			pData += sizeof(ItemList[i].value.floatValue);
			ItemList[i].m_pElement->syscomData.value.floatValue = ItemList[i].value.floatValue;
			fTempvar = static_cast<float> (ItemList[i].value.floatValue);
			sTempVar.Format(_T("%.2f"), fTempvar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtLREAL:
		{
			memcpy(&(ItemList[i].value.doubleValue), pData, sizeof(ItemList[i].value.doubleValue));
			pData += sizeof(ItemList[i].value.doubleValue);
			ItemList[i].m_pElement->syscomData.value.doubleValue = ItemList[i].value.doubleValue;
			dTempvar = static_cast<double> (ItemList[i].value.doubleValue);
			sTempVar.Format(_T("%.2f"), dTempvar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtBOOL:
		{
			memcpy(&(ItemList[i].value.boolValue), pData, sizeof(ItemList[i].value.boolValue));
			pData += sizeof(ItemList[i].value.boolValue);
			ItemList[i].m_pElement->syscomData.value.boolValue = ItemList[i].value.boolValue;
			babTempvar = static_cast<bool> (ItemList[i].value.boolValue);
			sTempVar.Format(_T("%d"), babTempvar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtBYTE:
		{
			memcpy(&(ItemList[i].value.byteValue), pData, sizeof(ItemList[i].value.byteValue));
			pData += sizeof(ItemList[i].value.byteValue);
			ItemList[i].m_pElement->syscomData.value.byteValue = ItemList[i].value.byteValue;
			cabTempvar = static_cast<char> (ItemList[i].value.byteValue);
			sTempVar.Format(_T("%d"), cabTempvar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtWORD:
		{
			memcpy(&(ItemList[i].value.shortValue), pData, sizeof(ItemList[i].value.shortValue));
			pData += sizeof(ItemList[i].value.shortValue);
			ItemList[i].m_pElement->syscomData.value.shortValue = ItemList[i].value.shortValue;
			nabTempVar = static_cast<short> (ItemList[i].value.shortValue);
			sTempVar.Format(_T("%d"), nabTempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}


		case svtDWORD:
		{
			memcpy(&(ItemList[i].value.intValue), pData, sizeof(ItemList[i].value.intValue));
			pData += sizeof(ItemList[i].value.intValue);
			ItemList[i].m_pElement->syscomData.value.intValue = ItemList[i].value.intValue;
			iabTempVar = static_cast<int> (ItemList[i].value.intValue);
			sTempVar.Format(_T("%d"), iabTempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtSINT:
		{
			memcpy(&(ItemList[i].value.charValue), pData, sizeof(ItemList[i].value.charValue));
			pData += sizeof(ItemList[i].value.charValue);
			ItemList[i].m_pElement->syscomData.value.charValue = ItemList[i].value.charValue;
			caiTempvar = static_cast<char> (ItemList[i].value.charValue);
			sTempVar.Format(_T("%d"), caiTempvar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtINT:
		{
			memcpy(&(ItemList[i].value.shortValue), pData, sizeof(ItemList[i].value.shortValue));
			pData += sizeof(ItemList[i].value.shortValue);
			ItemList[i].m_pElement->syscomData.value.shortValue = ItemList[i].value.shortValue;
			naiTempVar = static_cast<short> (ItemList[i].value.shortValue);
			sTempVar.Format(_T("%d"), naiTempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtDINT:
		{
			memcpy(&(ItemList[i].value.intValue), pData, sizeof(ItemList[i].value.intValue));
			pData += sizeof(ItemList[i].value.intValue);
			ItemList[i].m_pElement->syscomData.value.intValue = ItemList[i].value.intValue;
			iaiTempVar = static_cast<INT> (ItemList[i].value.intValue);
			sTempVar.Format(_T("%d"), iaiTempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtUSINT:
		{
			memcpy(&(ItemList[i].value.unsignedCharValue), pData, sizeof(ItemList[i].value.unsignedCharValue));
			pData += sizeof(ItemList[i].value.unsignedCharValue);
			ItemList[i].m_pElement->syscomData.value.unsignedCharValue = ItemList[i].value.unsignedCharValue;
			cai1Tempvar = static_cast<UCHAR> (ItemList[i].value.unsignedCharValue);
			sTempVar.Format(_T("%d"), cai1Tempvar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtUINT:
		{
			memcpy(&(ItemList[i].value.unsignedShortValue), pData, sizeof(ItemList[i].value.unsignedShortValue));
			pData += sizeof(ItemList[i].value.unsignedShortValue);
			ItemList[i].m_pElement->syscomData.value.unsignedShortValue = ItemList[i].value.unsignedShortValue;
			nai1TempVar = static_cast<USHORT> (ItemList[i].value.unsignedShortValue);
			sTempVar.Format(_T("%d"), nai1TempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtUDINT:
		{
			memcpy(&(ItemList[i].value.unsignedIntValue), pData, sizeof(ItemList[i].value.unsignedIntValue));
			pData += sizeof(ItemList[i].value.unsignedIntValue);
			ItemList[i].m_pElement->syscomData.value.unsignedIntValue = ItemList[i].value.unsignedIntValue;
			iai1TempVar = static_cast<UINT> (ItemList[i].value.unsignedIntValue);
			sTempVar.Format(_T("%d"), iai1TempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtTIME:
		{
			memcpy(&(ItemList[i].value.unsignedIntValue), pData, sizeof(ItemList[i].value.unsignedIntValue));
			pData += sizeof(ItemList[i].value.unsignedIntValue);
			ItemList[i].m_pElement->syscomData.value.unsignedIntValue = ItemList[i].value.unsignedIntValue;
			iai1TempVar = static_cast<UINT> (ItemList[i].value.unsignedIntValue);
			sTempVar.Format(_T("%d"), iai1TempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		case svtDATE_AND_TIME:
		{
			memcpy(&(ItemList[i].value.unsignedIntValue), pData, sizeof(ItemList[i].value.unsignedIntValue));
			pData += sizeof(ItemList[i].value.unsignedIntValue);
			ItemList[i].m_pElement->syscomData.value.unsignedIntValue = ItemList[i].value.unsignedIntValue;
			iai1TempVar = static_cast<UINT> (ItemList[i].value.unsignedIntValue);
			sTempVar.Format(_T("%d"), iai1TempVar);
			ItemList[i].m_pElement->setValue(sTempVar);
			break;
		}
		default:
			AfxMessageBox(L"Selectron data type conversion not known.");
			break;

		}

		/*
         

		//-----------------------------------------------
		switch (ItemList[i].uiDataType)
		{
			case BIT1:
			{
				memcpy(&(ItemList[i].value.boolValue), pData, sizeof(ItemList[i].value.boolValue));
				pData += sizeof(ItemList[i].value.boolValue);
				ItemList[i].m_pElement->syscomData.value.boolValue = ItemList[i].value.boolValue;
				iTempVar = static_cast<bool> (ItemList[i].value.boolValue);
				babTempvar = static_cast<bool> (iTempVar);
				sTempVar.Format(_T("%d"), babTempvar);
				ItemList[i].m_pElement->setValue(sTempVar);
				break;
			}
		  case BIT8:
			{
				memcpy(&(ItemList[i].value.byteValue), pData, sizeof(ItemList[i].value.byteValue));
				pData += sizeof(ItemList[i].value.byteValue);
				ItemList[i].m_pElement->syscomData.value.byteValue = ItemList[i].value.byteValue;
				iTempVar = static_cast<char> (ItemList[i].value.byteValue);				
				cabTempvar = static_cast<char> (iTempVar);
				sTempVar.Format(_T("%d"), cabTempvar);
				ItemList[i].m_pElement->setValue(sTempVar);
				break;
			}
		  case BIT16:
		  {
			  memcpy(&(ItemList[i].value.shortValue), pData, sizeof(ItemList[i].value.shortValue));
			  pData += sizeof(ItemList[i].value.shortValue);
			  ItemList[i].m_pElement->syscomData.value.shortValue = ItemList[i].value.shortValue;
			  iTempVar = static_cast<short> (ItemList[i].value.shortValue);
			  nabTempVar = static_cast<short> (iTempVar);
			  sTempVar.Format(_T("%d"), nabTempVar);
			  ItemList[i].m_pElement->setValue(sTempVar);
			  break;
		  }
		  case BIT32:
		  {
			  memcpy(&(ItemList[i].value.floatValue), pData, sizeof(ItemList[i].value.floatValue));
			  pData += sizeof(ItemList[i].value.floatValue);
			  ItemList[i].m_pElement->syscomData.value.floatValue = ItemList[i].value.floatValue;
			  iTempVar = static_cast<float> (ItemList[i].value.floatValue);
			  fTempvar = static_cast<float>(iTempVar);
			  sTempVar.Format(_T("%.2f"), fTempvar);
			  ItemList[i].m_pElement->setValue(sTempVar);
			  break;
		  }

		}
		
		CString a;
		TCHAR buf[32];
		_itow_s(iTempVar, buf, 10);
		MessageBoxW(NULL,(LPCWSTR) buf, NULL, MB_OK); */
		
	}
	//m_pElement->updateValue() tady se bude volat funkce v CElement class updatujici hodnotu Elementu
	return hResult;
}

//Set the Monitor list on the PLC
//HRESULT CPlc::Set_MonitorList(item ItemList[], int count)
HRESULT CPlc::Set_MonitorList()
{
	HRESULT	hResult;
	//Create a Srv_cmd_IO_DefMonList_T struct
	//Srv_cmd_IO_DefMonList_T         DefMonList;
	//Set the ListNr to 1, there is just 1 possible at the moment.
	DefMonList.ListNr = 0;
	//Set the TacCount to the count of variables to monitor
	DefMonList.TacCount = itemCount;
	//Do for every variable to monitor
	for (int i = 0; i<itemCount; i++)
	{
		DefMonList.TAC[i].Addr.ulAbsAddr = (ItemList[i].ulAbsAddress);
		//DefMonList.TAC[i].Addr.ulAbsAddr = static_cast<INT>(ItemList[i].ulAbsAddress);		//Set Adress oft the TAC
		DefMonList.TAC[i].uiDataType = ItemList[i].uiDataType;			//Set Data Type oft the TAC
		DefMonList.TAC[i].uiCount = 1;								//Set length of the variabel to 1 => no Array	
		DefMonList.TAC[i].uiAddrType = 0;								//Set AdressType to Absolut Adress
	}
	DefMonList.len = 4 + itemCount * sizeof(Srv_cmd_IO_TAC_T); //Calculate the len of the Monitor List in byte
														   //Define the MonitorList on the PLC
	hResult = MAS_DefineMonitorList(server, &DefMonList, NULL, timeOut);
	return hResult;
}




HRESULT CPlc::Get_MonitorListState()
{
	HRESULT	hResult;
	Srv_cmd_IO_MonListState_T MonListState;

	hResult = MAS_MonitorListState(server, &MonListState, NULL, timeOut);

	



	return hResult;
}

/*
int CPlc::SelectronVarType2VarLength(CString sVarType, DWORD * iVarLengthBits, DWORD * iVarLengthBytes, Data_Types *dtDataType, Data_Types *uiDataType)
{
	if (sVarType == _T("BOOL")) 
	{
		*iVarLengthBits = 1;
		*iVarLengthBytes = 1; 
		*dtDataType = svtBOOL;
		*uiDataType = BIT1;
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
*/