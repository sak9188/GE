#include "GE_Process.h"

bool JudgeSystem(void)
{
	int a = 1;

	//�����С���򷵻�1������Ǵ���򷵻�0
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
