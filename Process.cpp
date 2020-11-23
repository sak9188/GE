#include "Process.h"

#include <boost\process\environment.hpp>
#include <boost\lexical_cast.hpp>

#include "PythonEngine.h"
#include "DateTime.h"
#include "GUID64.h"
#include "IO.h"

bool JudgeSystem(void)
{
	int a = 1;

	//如果是小端则返回1，如果是大端则返回0
	return *(char *)&a == 1 ? true : false;
}

GE::Process::Process()
	:processUID(1)
{
	SysCheck();

	// step1 构建IO
	IO::New();
	// step2 初始化Python
	PythonEngine::New();
	// step3 初始化时间
	DateTime::New();
	// step4 构建化全局ID分配器
	GUID64::New();
	// step6 网络打包类、全局消息打包器
}

GE::Process::~Process()
{
	// 回收垃圾
	GUID64::Delete();
	DateTime::Delete();
	PythonEngine::Delete();
	IO::Delete();
}

void GE::Process::Start(int argc, char * argv[])
{
	
	if (argc != 3)
	{
		printf("plz input the process type");
		KillSelf();
	}

	machineID = static_cast<GE::Uint8>(boost::lexical_cast<GE::Uint16>(argv[1])); //static_cast<GE::Uint8>(argv[1]);
	
	processType = argv[2];
	processID = boost::this_process::get_id();

	printf("machineID %d \n", machineID);
	printf("processType %s \n", processType.c_str());
	printf("processId %d \n", processID);

	// 0b 1011111 10101010 11000100 00011100 11000001 00000000 00000000
	// printf("processGUID_64 %I64u \n", GE_GUID64::Instance()->AllotGUID());
}

void GE::Process::KillSelf()
{
	delete this;
	exit(1);
}

void GE::Process::CloseConsole()
{
}

std::string GE::Process::MakeProcessKey(const std::string & type, GE::Uint16 uid)
{
	return std::string();
}

void GE::Process::SysCheck()
{
	if (!JudgeSystem())
	{
		KillSelf();
	}
}
