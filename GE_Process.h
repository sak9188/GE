#pragma once

#include <mutex>
#include <vector>

#include "GE.h"

class GE_Process
{
public:
	~GE_Process();

	void Start(int argc, char *argv[]);
	void CloseConsole();
	std::string MakeProcessKey(const std::string &type, GE::Uint16 uid);

public:
	std::string processType;
	GE::Uint16 processID;
	// ConnectParam DefualConnectParam;
	std::vector<std::string> argv;
	bool showPrintLine;

private:
	void Init();

	void SysCheck();

	GE_SINGLETON(GE_Process)
};

