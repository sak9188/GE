#pragma once

#include "..\GE.h"

#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\enable_shared_from_this.hpp>

class GE_NetWork;

// 一个连接的状态
enum ENetConnectState
{
	eWork,
	eRemoteClose,
	eMsgError,
	eSendBufFull,
	eRecvBufFull,
	
	eConnectFull,
	eLocalClose,
	eForceClose,
};

class GE_NetConnect
	: public boost::enable_shared_from_this<GE_NetConnect>
{
	GE_BAN_COPY(GE_NetConnect)
public:
	GE_NetConnect();
	~GE_NetConnect();

public:
	GE::Uint32			SessionID() { return sessionID; }									//获取该连接的SessionID
	void				SessionID(GE::Uint32 uSessionID) { sessionID = uSessionID; }		//设置该连接的SessionID
	
	GE::Uint16			Who() { return who; }												//获取该连接的类型Who
	void				Who(GE::Uint16 uWho) { who = uWho; }								//设置该连接的类型Who
	
	GE::Uint16			State() { return static_cast<GE::Uint16>(state); }					//连接的当前状态
	
	void*				BindPoint() { return bindPoint; }									//获取该连接绑定的指针
	void				BindPoint(void* p) { bindPoint = p; }								//设置该连接绑定的指针
	
	GE::Uint64			BindLong() { return bindLong; }									//获取该连接绑定的整数
	void				BindLong(GE::Uint64 ui64) { bindLong = ui64; }					//设置该连接绑定的整数
	
	GE::Int32			ConnectTime() { return connectTime; }								//获取该连接的创建时间
	GE::Uint32			ReadMsgCount() { return readMsgCount; }							//读取的消息条数
	GE::Uint32			SendMsgCount() { return sendMsgCount; }							//发送的消息条数

private:
	GE_NetWork*			netWork;
	GE::Uint32			sessionID;		//连接SessionID
	GE::Uint16			who;			//连接的类型
	ENetConnectState	state;			//连接的状态
	void*				bindPoint;		//连接绑定的指针
	GE::Uint64			bindLong;		//连接绑定的整数1
	GE::Int32			connectTime;	//该连接的创建时间
	GE::Int32			kickTime;		//该连接被踢掉的时间
	GE::Int32			sendTime;		//该连接最后发送消息的时间
	GE::Int32			recvTime;		//该连接最后接收消息的时间
	GE::Uint32			readMsgCount;	//读取的消息条数
	GE::Uint32			sendMsgCount;	//发送的消息条数

	boost::asio::ip::tcp::socket boostSocket; //连接的boost::socket
	GE_NetSendBuf		sendBuf;		//连接的发送buf
	GE_NetRecvBuf		recvBuf;		//连接的接收buf
	GE_NetBuf			recvCache;		//连接的当前消息接收buf

	boost::mutex		sendMutex;		//发送buf的线程锁
	boost::mutex		recvMutex;		//接收buf的线程锁

	GE::Uint16			m_uWaitWhoTime;		//等待身份验证的时间
	GE::Uint16			m_uWaitRecvTime;	//等待接收消息的时间
};

