#include "stdafx.h"
#include "MyServer.h"

//IMPLEMENT_SERIAL(MyPlcServer, CElement, 1001)

MyPlcServer::MyPlcServer()
{

}

MyPlcServer::MyPlcServer(CHAR* n , CHAR* aP , CHAR* cS )
{
	strcpy_s(name, 64, n);
	strcpy_s(accessPath, 64, aP);
	strcpy_s(configString, 64, cS);
}


MyPlcServer::~MyPlcServer()
{
	if (connected)
	{
		disconnect();
	}
}

int MyPlcServer::connect(void)
{
	HRESULT hResult;
	server = MAS_CreateSysComServerEx((LPCTSTR)name, (LPCTSTR)accessPath, (LPCTSTR)configString);
	if (server == NULL)
	{
		return -1;
	}
	hResult = MAS_Login(server, (LPCTSTR)user, (LPCTSTR)pass, NULL, timeOut);
	if (hResult < 0)
	{
		return -1;
	}
	hResult = MAS_GetInfoProject(server, SRV_DST_RAM, &(infoProject),
		NULL, timeOut);
	if (hResult < 0)
	{
		return -1;
	}
	CString Text = CString(infoProject.Text);
	AfxMessageBox(Text);

	connected = true;
	return 0;
}

int MyPlcServer::disconnect(void)
{
	HRESULT hResult;
	hResult = MAS_Logout(server, timeOut);
	if (hResult < 0)
	{
		return -1;
	}
	hResult = MAS_DestroySysComServer(server);
	if (hResult < 0)
	{
		return -1;
	}
	connected = false;
	return 0;
}