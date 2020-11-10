#pragma once

#include <vector>

#include "GE.h"
#include "GE_Singleton.h"

class GE_Process
	: public GE_Singleton<GE_Process>
{
public:
	GE_Process();
	~GE_Process();

	void Start(int argc, char *argv[]);
	void KillSelf();
	void CloseConsole();
	std::string MakeProcessKey(const std::string &type, GE::Uint16 uid);

public:
	std::string processType;
	GE::Uint16 processID;

	// ConnectParam DefualConnectParam;
	std::vector<std::string> argv;
	bool showPrintLine;

	GE::Uint8 MachineID(void) { return machineID; }
	GE::Uint8 ProcessUID(void) { return processUID; }

private:
	void SysCheck();

	// 机器id
	GE::Uint8 machineID;
	// 进程的自增id
	GE::Uint8 processUID;
};

