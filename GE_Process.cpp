#include "GE_Process.h"

bool JudgeSystem(void)
{
	int a = 1;

	//�����С���򷵻�1������Ǵ���򷵻�0
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
