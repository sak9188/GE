#include "GUID64.h"

#include "DateTime.h"
#include "Process.h"

GE::GUID64::GUID64()
	: baseID(0)
{

}

GE::GUID64::~GUID64()
{

}

GE::Uint64 GE::GUID64::AllotGUID()
{
	// 8个字节的内存分布
	// 5个字节 用 40 bits 作为时间中的秒分布
	// 1 个字节 用 8 bits 作为工作机器与进程的 id (4 bits for machine, 4 bits for processes)
	//     最大可以支持 2^4 16台机器， 每台机器16个进程 (这个有点过于奢侈了，1个字节有点浪费)
	// 2 个字节 用 16 bits 来表示一秒内 最多有 65536 个 id
	// 相当于 1毫秒 以内 至多有65个 GUID 的生成

	if (baseID > maxID)
	{
		// 如果分配失败则返回0，但是正常情况下是不可能返回0的
		return 0;
	}

	GE::Uint64 guid_secs = GE::DateTime::Instance()->Seconds();
	// printf("guid_secs %d \n", guid_secs);
	// printf("MachineID %d \n", (GE_Process::Instance()->MachineID() << 4));
	// printf("ProcessUID %d \n", ((GE_Process::Instance()->ProcessUID() << 4) >> 4));
	GE::Uint8 guid_macid = (GE::Process::Instance()->MachineID() << 4) + ((GE::Process::Instance()->ProcessUID() << 4) >> 4);
	guid_secs = (((guid_secs << 8) + guid_macid) << 16) + baseID++;
	return guid_secs;
}

void GE::GUID64::ResetBaseID()
{
	baseID = 0;
}
