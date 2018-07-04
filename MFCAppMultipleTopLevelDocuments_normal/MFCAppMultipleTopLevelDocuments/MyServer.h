#pragma once
#include "SysComServer.h"
#include "CElement.h"


class MyPlcServer : public CElement
{
	DECLARE_SERIAL(MyPlcServer)
public:
	MyPlcServer();
	MyPlcServer(CHAR* n = NULL, CHAR* aP = NULL, CHAR* cS = NULL);
	~MyPlcServer(void);
	int connect(void);
	int disconnect(void);
	/*
	void setName(char* n);
	void setAccessPath(char* path);
	void setConfigString(char* string);
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
	HANDLE server;
	CHAR name[64];
	CHAR accessPath[64];
	CHAR configString[64];
	Srv_Info_Proj_T infoProject;
	bool connected;
	INT timeOut = 10000;
	CHAR user[64] = "user_0";
	CHAR pass[64] = "sele0";
};

