#include "NetConnect.h"



GE::Net::NetConnect::NetConnect(GE::Net::NetWork* pNetWork)
	: boostSocket(pNetWork->IOS())
{
}


GE::Net::NetConnect::~NetConnect()
{
}
