#include "GE_Process.h"

#include <boost\process\environment.hpp>

#include "GE_Python.h"
#include "GE_DateTime.h"
#include "GE_GUID64.h"

bool JudgeSystem(void)
{
	int a = 1;

	//�����С���򷵻�1������Ǵ���򷵻�0
	return *(char *)&a == 1 ? true : false;
}

GE_Process::GE_Process()
{
	SysCheck();

	// ��ʼ��Python
	GE_Python::New();
	// ��ʼ��ʱ��
	GE_DateTime::New();
	// step4 ����IO
	// GEIO::New();
	// step5 ������ȫ��ID������
	GE_GUID64::New();
	// step6�������ࡢȫ����Ϣ�����
}

GE_Process::~GE_Process()
{
	// ��������
	GE_GUID64::Delete();
	GE_DateTime::Delete();
	GE_Python::Delete();
}

void GE_Process::Start(int argc, char * argv[])
{
	
	if (argc != 2)
	{
		printf("plz input the process type");
		KillSelf();
	}

	processType = argv[1];
	processID = boost::this_process::get_id();

	printf("processType %s \n", processType.c_str());
	printf("processId %d \n", processID);
}

void GE_Process::KillSelf()
{
	delete this;
	exit(1);
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
	if (!JudgeSystem())
	{
		KillSelf();
	}
}
