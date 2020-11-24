#pragma once

#include <string>

#include "..\GE.h"

// ���ӵ�Ĭ�ϲ���
#define DEFUAL_SEND_BLOCK_SIZE		GE_UINT16_MAX		//���ͻ�������Ϣ���С
#define DEFUAL_SEND_BLOCK_NUM		100					//���ͻ�������Ϣ�����
#define DEFUAL_RECV_BLOCK_SIZE		GE_UINT16_MAX		//���ջ�������Ϣ���С
#define DEFUAL_RECV_BLOCK_NUM		10					//���ջ�������Ϣ�����
#define DEFAUL_WAIT_WHO_TIME		10					//�ȴ������֤ʱ��
#define DEFAUL_WAIT_RECV_TIME		3600				//�ȴ�������Ϣʱ��

namespace GE
{
	namespace Net
	{
		// һ�����ӵ�״̬
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
