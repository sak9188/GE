#include "GE_NetConnect.h"



GE_NetConnect::GE_NetConnect(GE_NetWork* pNetWork)
	: boostSocket(pNetWork->IOS())
{
}


GE_NetConnect::~GE_NetConnect()
{
}
