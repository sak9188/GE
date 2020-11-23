#pragma once

#include "..\GE.h"

#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\enable_shared_from_this.hpp>

#include "NetBlock.h"
#include "NetWork.h"


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

struct GE_NetInfo
{
	GE::Uint32			sessionID;
	GE::Uint16			who;
	GE::Uint64			bindLong;
	GE::Int32			connectTime;
	GE::Int32			kickTime;
	GE::Int32			sendTime;
	GE::Int32			recvTime;
	GE::Uint32			readMsgCount;
	GE::Uint32			sendMsgCount;
	GE::Uint16			waitWhoTime;
	GE::Uint16			waitRecvTime;
	std::string			zip;
	ENetConnectState	state;
};

// 连接的默认参数
#define DEFUAL_SEND_BLOCK_SIZE		GE_UINT16_MAX		//发送缓冲区消息块大小
#define DEFUAL_SEND_BLOCK_NUM		100					//发送缓冲区消息块个数
#define DEFUAL_RECV_BLOCK_SIZE		GE_UINT16_MAX		//接收缓冲区消息块大小
#define DEFUAL_RECV_BLOCK_NUM		10					//接收缓冲区消息块个数
#define DEFAUL_WAIT_WHO_TIME		10					//等待身份验证时间
#define DEFAUL_WAIT_RECV_TIME		3600				//等待接收消息时间

struct ConnectParam
{
	ConnectParam()
	{
		sendBlockSize = DEFUAL_SEND_BLOCK_SIZE;
		sendBlockNum = DEFUAL_SEND_BLOCK_NUM;
		recvBlockSize = DEFUAL_RECV_BLOCK_SIZE;
		recvBlockNum = DEFUAL_RECV_BLOCK_NUM;
		waitWhoTime = DEFAUL_WAIT_WHO_TIME;
		waitRecvTime = DEFAUL_WAIT_RECV_TIME;
	}

	GE::Uint16		sendBlockSize;
	GE::Uint16		sendBlockNum;
	GE::Uint16		recvBlockSize;
	GE::Uint16		recvBlockNum;
	GE::Uint16		waitWhoTime;
	GE::Uint16		waitRecvTime;
};

namespace GE
{
	namespace Net
	{
		class NetConnect
			: public boost::enable_shared_from_this<NetConnect>
		{
			GE_BAN_COPY(NetConnect)
		public:
			NetConnect(GE::Net::NetWork* pNetWork);
			~NetConnect();

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

			boost::asio::ip::tcp::socket&		Socket() { return boostSocket; }									//该连接的boost::socket
			void				RemoteEndPoint(std::string& sIP, GE::Uint32& uPort);				//获取该连接的远程IP、端口

		private:
			GE::Net::NetWork*			netWork;
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
													  // GE::Net::NetSendBuf		sendBuf;		//连接的发送buf
													  // GE::Net::NetRecvBuf		recvBuf;		//连接的接收buf
			NetBlock			recvCache;		//连接的当前消息接收buf

			boost::mutex		sendMutex;		//发送buf的线程锁
			boost::mutex		recvMutex;		//接收buf的线程锁

			GE::Uint16			waitWhoTime;	//等待身份验证的时间
			GE::Uint16			waitRecvTime;	//等待接收消息的时间
		};
	}
}



