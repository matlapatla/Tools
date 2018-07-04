#include "stdafx.h"
#include "SerialPort.h"


SerialPort::SerialPort()
{
}


SerialPort::~SerialPort()
{
	CloseHandle(m_hCom);
}

INT SerialPort::DisconnectPort(CString & ErrorMsg)
{
	if (CloseHandle(m_hCom) != S_OK)
	{
		ErrorMsg = L"CloseHandle failed";
		INT ierror = AtlHresultFromLastError();
		return ierror;
	}
	xConnected = FALSE;
	return 0;
}


INT SerialPort::ConnectToPort(CString ComPort, CString & ErrorMsg)
{
	if (xConnected)
	{
		ErrorMsg = L"The Com port already connected.";
		return 1;
	}
	//m_sComPort = "\\\\.\\COM11";
	m_sComPort = L"\\\\.\\";
	m_sComPort.Append(ComPort);
	m_hCom = CreateFile(LPCTSTR (m_sComPort),
		GENERIC_READ | GENERIC_WRITE,
		0, // exclusive access
		NULL, // no security
		OPEN_EXISTING,
		0, // no overlapped I/O
		NULL); // null template 

	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		ErrorMsg = L"CreateFile failed, handle = INVALID_HANDLE_VALUE";
		return 2;
	}
	xConnected = TRUE;

	m_bPortReady = SetupComm(m_hCom, 128, 128); // set buffer sizes
	if (m_bPortReady == 0)
	{
		ErrorMsg = L"SetupComm(m_hCom, 128, 128); // set buffer sizes failed";
		return 3;
	}																						
    //Port settings are specified in a Data Communication Block(DCB).The easiest way to initialize a DCB is to call GetCommState to fill in its default values, override the values that you want to change and then call SetCommState to set the values.
    m_bPortReady = GetCommState(m_hCom, &m_dcb);
	m_dcb.BaudRate = 9600;
	//m_dcb.BaudRate = 38400;
	//m_dcb.BaudRate = 19200;
	m_dcb.ByteSize = 8;
	m_dcb.Parity = NOPARITY;
	//m_dcb.Parity = EVENPARITY;
	m_dcb.StopBits = ONESTOPBIT;
	m_dcb.fAbortOnError = TRUE;

	m_bPortReady = SetCommState(m_hCom, &m_dcb);
	if (m_bPortReady == 0)
	{
		ErrorMsg = L"SetCommState(m_hCom, &m_dcb); // set com setting failed";
		return 4;
	}

	//Communication timeouts are optional but can be set similarly to DCB values :

	m_bPortReady = GetCommTimeouts(m_hCom, &m_CommTimeouts);
	
	m_CommTimeouts.ReadIntervalTimeout = 50;
	m_CommTimeouts.ReadTotalTimeoutConstant = 50;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 10;
	m_CommTimeouts.WriteTotalTimeoutConstant = 50;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 10;
	/*
	m_CommTimeouts.ReadIntervalTimeout = MAXDWORD;
	m_CommTimeouts.ReadTotalTimeoutConstant = 0;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 0;
	m_CommTimeouts.WriteTotalTimeoutConstant = 0;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 0;
	*/
	m_bPortReady = SetCommTimeouts(m_hCom, &m_CommTimeouts);
	if (m_bPortReady == 0)
	{
		ErrorMsg = L"SetCommTimeouts(m_hCom, &m_CommTimeouts); // set com timeouts failed";
		return 5;
	}
	dwCommEvent = EV_RXCHAR;
	m_bPortReady = SetCommMask(m_hCom, EV_RXCHAR);
	if (m_bPortReady == 0)
	{
		ErrorMsg = L"SetCommMask(m_hCom, EV_RXCHAR) failed.";
		return 6;
	}

	//If all of these API's were successful then the port is ready for use.
	
	return 0;
}

INT SerialPort::SendFrame(CString Frame, CString & ErrorMsg)
{   //SENDING COMMANDS TO THE ADR2000
	//To send commands to the ADR2000 the WriteFile call is used.For example, the following call sends an RE(read event counter) command to the ADR2000;
	//The \r escape embeds a carriage return character at the end of the transmitted string.The ADR2000 uses this to recognize a command.


	//bWriteRC = WriteFile(m_hCom, "RE\r", 3, &iBytesWritten, NULL);
	char   sBuffer[1024];
	char * lpBuf = sBuffer;
	DWORD noOfBytesToSend = 0;
	for (DWORD i = 0; i < (DWORD) Frame.GetLength(); i++) {
		if (Frame.GetAt(i) != '\0')
		{		
			sBuffer[i] = (char)Frame.GetAt(i);								
			noOfBytesToSend++;
		}
	}
	//bWriteRC = WriteFile(m_hCom, Frame, noOfBytesToSend, &iBytesWritten, NULL);
	bWriteRC = WriteFile(m_hCom, lpBuf, noOfBytesToSend, &iBytesWritten, NULL);
	if (!bWriteRC) {
		ErrorMsg = L"WriteFile(m_hCom, Frame, nNumbersOfBytesToWrite, &iBytesWritten, NULL) failed.";
		return 1;
	}
	return 0;	
}

INT SerialPort::ReceiveFrame(CString & Frame, CString & ErrorMsg, DWORD & dwBytesRead)
{
	//RECEIVING DATA FROM THE ADR2000
	//If a command sent to the ADR2000 is a responsive command, that is, one that results in data being sent back to the host, the data is retrieved using the ReadFile call.
	//When you are through using the file handle simply close the file.

	//bReadRC = ReadFile(m_hCom, &sBuffer, 6, &iBytesRead, NULL);
	char  rBuffer[1024];
	char * lpBuf = rBuffer;
	DWORD BytesRead;
	CString tmpFrame;
	DWORD   dwErrors;
	COMSTAT comStat;
	BOOL xReadFile;
	//DWORD dwCommEvent;
	dwCommEvent = EV_RXCHAR;
	//while (TRUE)
	{	
		dwBytesRead = 0;
		//if (WaitCommEvent(m_hCom, &dwCommEvent, NULL))
		//{
		if (!ClearCommError(m_hCom, &dwErrors, &comStat))
		{
			// Report error in ClearCommError.
			ErrorMsg = L"ClearCommError(hComm, &dwErrors, &comStat) failed.  //Report error in ClearCommError.";
			return 1;
		} 
		else 
		{   if (comStat.cbInQue)
			// comStat.cbInQue bytes have been received, but not read
			do
			{				
				xReadFile = ReadFile(m_hCom, lpBuf, 1, &BytesRead, NULL);				
				if (xReadFile)
				{
					if (BytesRead > 0)
					{
						dwBytesRead = BytesRead;
						tmpFrame = tmpFrame + rBuffer[0];
						Frame = tmpFrame;
						ErrorMsg = L"ReadFile(m_hCom, &sBuffer, 6, &iBytesRead, NULL) iBytesRead  = " + BytesRead;
						//for (DWORD i = 0; i < BytesRead; i++) 
						//{
						//if (i < BytesRead) {
						//tmpFrame.SetAt((int)i, rBuffer[i]);
						//	tmpFrame = tmpFrame + rBuffer[i];
					}
					//else {
					//tmpFrame.SetAt((int)i, '\0');
					//tmpFrame = tmpFrame + '\0';
				} 
				else
				{
					ErrorMsg = L"ReadFile(m_hCom, &sBuffer, 6, &iBytesRead, NULL) failed. // An error occurred in the ReadFile call.";
					return 2;
				} 
			} while (BytesRead > 0);

		}	
	}
	return 0;
}

