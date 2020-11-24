#pragma once

#include <string>

#include "..\GE.h"

// 连接的默认参数
#define DEFUAL_SEND_BLOCK_SIZE		GE_UINT16_MAX		//发送缓冲区消息块大小
#define DEFUAL_SEND_BLOCK_NUM		100					//发送缓冲区消息块个数
#define DEFUAL_RECV_BLOCK_SIZE		GE_UINT16_MAX		//接收缓冲区消息块大小
#define DEFUAL_RECV_BLOCK_NUM		10					//接收缓冲区消息块个数
#define DEFAUL_WAIT_WHO_TIME		10					//等待身份验证时间
#define DEFAUL_WAIT_RECV_TIME		3600				//等待接收消息时间

namespace GE
{
	namespace Net
	{
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

		struct NetInfo
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
	}
}
