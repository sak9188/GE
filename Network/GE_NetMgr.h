#pragma once
#include <vector>

#include <boost\unordered_map.hpp>
#include <boost\thread\mutex.hpp>

#include <map>

#include "..\GE.h"

class GE_NetConnect;

class GE_NetMgr
{
	GE_BAN_COPY(GE_NetMgr);
public:
	GE_NetMgr(GE::Uint32 uMaxConnect);
	~GE_NetMgr(void);

public:
	// bool				AddConnect(boost::shared_ptr<GE_NetConnect>& spConnect, GE::Uint32& uID);	//增加一个连接
	// bool				DelConnect(GE::Uint32 uID);												//删除一个连接
	// bool				HasConnect(GE::Uint32 uID);												//是否有某个连接
	// GE_NetConnect*		FindConnect(GE::Uint32 uID);											//查找一个连接（通过ID）
	// GE_NetConnect*		FindConnectForHasData(GE::Uint32 uID);									//查找一个连接（为了发送数据）
	// GE_NetConnect*		NextConnect();															//获取下一个连接（内部循环迭代，增删连接迭代依然有效）
	// GE::Uint32			ConnectCnt() { return m_IndexMgr.UseSize(); }							//连接的数量
	// GE::Uint32			EmptyCnt() { return m_IndexMgr.FreeSize(); }							//空闲的数量
	// void				ConnectHasData(GE::Uint32 uID);											//标记连接有数据
	// void				Lock(GE::Uint32 uID);													//锁住某个连接
	// void				Unlock(GE::Uint32 uID);													//释放某个连接
	// bool				DriverAsyncSendBlock();													//驱动所以的连接异步发送消息，返回是否有连接发送的数据量很大
	// void				DelAllConnect();														//删除所有的连接

private:
	// std::map<>			indexMgr;			//索引ID分配器
	GE_NetMgr**			dataArr;			//连接数组
	bool*				hasData;			//是否有未发送的数据
	boost::unordered_map<GE::Uint32, boost::shared_ptr<GE_NetConnect> >				m_pDataMap;			//用来hold智能指针的map
	std::vector<boost::mutex*>			mutexVector;		//用来管理每个连接的锁（多锁，减少碰撞）
};

