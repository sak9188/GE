#include "GE_Process.h"

bool JudgeSystem(void)
{
	int a = 1;

	//如果是小端则返回1，如果是大端则返回0
	return *(char *)&a == 1 ? true : false;
}

GE_Process::GE_Process()
{
	if (!JudgeSystem())
	{
		abort();
	}
}

GE_Process::~GE_Process()
{
}

void GE_Process::Start(int argc, char * argv[])
{
}

void GE_Process::CloseConsole()
{
}

std::string GE_Process::MakeProcessKey(const std::string & type, GE::Uint16 uid)
{
	return std::string();
}

void GE_Process::SysCheck()
{
}
