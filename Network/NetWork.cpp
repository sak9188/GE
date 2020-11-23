#include "NetWork.h"


GE::Net::NetWork::NetWork(GE::Uint32 uMaxConnect, GE::Uint16 uThread)
	: connectMgr(uMaxConnect)
	, isRun(false)
	, isStop(false)
	, acceptor(NULL)
	, asyncSendWho(false)
	, asyncSendThread(NULL)
	, debugThread(NULL)
	, curConnect(NULL)
	, curMsg(NULL)
	, lastConnectClose(false)
	, lastSessionID(GE_UINT32_MAX)
	, msgCnt(0)
	, maxConnect(0)
{
	for (GE::Uint32 uIdx = 0; uIdx < uThread; ++uIdx)
	{
		this->netWorkThreads.push_back(NULL);
	}
}

GE::Net::NetWork::~NetWork()
{
}
