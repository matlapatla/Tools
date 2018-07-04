#pragma once
#include "afxwin.h"

//LPOVERLAPPED LPoverLapped;

class SerialPort
{
	// variables used with the com port
	BOOL     m_bPortReady;
	HANDLE   m_hCom;
	CString  m_sComPort;
	DCB      m_dcb;
	COMMTIMEOUTS m_CommTimeouts;
	BOOL     bWriteRC;
	BOOL     bReadRC;
	DWORD iBytesWritten;	
	char       sBuffer[128];
	BOOL xConnected = FALSE;
	DWORD dwCommEvent;
	


public:
	SerialPort();
	~SerialPort();
	INT ConnectToPort(CString, CString &);
	INT SendFrame(CString, CString &);
	INT ReceiveFrame(CString &, CString &, DWORD &);
	INT DisconnectPort(CString &);
	
	
};

