#include "GE_Process.h"
GE_SET_SINGLETON(GE_Process)

bool JudgeSystem(void)
{
	int a = 1;

	//如果是小端则返回1，如果是大端则返回0
	return *(char *)&a == 1 ? true : false;
}

void GE_Process::Init()
{
	if (!JudgeSystem())
	{
		abort();
	}
}


GE_Process::~GE_Process()
{
}
