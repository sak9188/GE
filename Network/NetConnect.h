#pragma once

#include "..\GE.h"

#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\enable_shared_from_this.hpp>

#include "NetBlock.h"
#include "NetWork.h"

namespace GE{
namespace Net{


class NetConnect
	: public boost::enable_shared_from_this<NetConnect>
{
	GE_BAN_COPY(NetConnect)
public:
	NetConnect(GE::Net::NetWork* pNetWork);
	~NetConnect();

public:
	GE::Uint32			SessionID() { return sessionID; }									//��ȡ�����ӵ�SessionID
	void				SessionID(GE::Uint32 uSessionID) { sessionID = uSessionID; }		//���ø����ӵ�SessionID

	GE::Uint16			Who() { return who; }												//��ȡ�����ӵ�����Who
	void				Who(GE::Uint16 uWho) { who = uWho; }								//���ø����ӵ�����Who

	GE::Uint16			State() { return static_cast<GE::Uint16>(state); }					//���ӵĵ�ǰ״̬

	void*				BindPoint() { return bindPoint; }									//��ȡ�����Ӱ󶨵�ָ��
	void				BindPoint(void* p) { bindPoint = p; }								//���ø����Ӱ󶨵�ָ��

	GE::Uint64			BindLong() { return bindLong; }									//��ȡ�����Ӱ󶨵�����
	void				BindLong(GE::Uint64 ui64) { bindLong = ui64; }					//���ø����Ӱ󶨵�����

	GE::Int32			ConnectTime() { return connectTime; }								//��ȡ�����ӵĴ���ʱ��
	GE::Uint32			ReadMsgCount() { return readMsgCount; }							//��ȡ����Ϣ����
	GE::Uint32			SendMsgCount() { return sendMsgCount; }							//���͵���Ϣ����

	boost::asio::ip::tcp::socket&		Socket() { return boostSocket; }									//�����ӵ�boost::socket
	void				RemoteEndPoint(std::string& sIP, GE::Uint32& uPort);				//��ȡ�����ӵ�Զ��IP���˿�

private:
	GE::Net::NetWork*			netWork;
	GE::Uint32			sessionID;		//����SessionID
	GE::Uint16			who;			//���ӵ�����
	ENetConnectState	state;			//���ӵ�״̬
	void*				bindPoint;		//���Ӱ󶨵�ָ��
	GE::Uint64			bindLong;		//���Ӱ󶨵�����1
	GE::Int32			connectTime;	//�����ӵĴ���ʱ��
	GE::Int32			kickTime;		//�����ӱ��ߵ���ʱ��
	GE::Int32			sendTime;		//�������������Ϣ��ʱ��
	GE::Int32			recvTime;		//��������������Ϣ��ʱ��
	GE::Uint32			readMsgCount;	//��ȡ����Ϣ����
	GE::Uint32			sendMsgCount;	//���͵���Ϣ����

	boost::asio::ip::tcp::socket boostSocket; //���ӵ�boost::socket
												// GE::Net::NetSendBuf		sendBuf;		//���ӵķ���buf
												// GE::Net::NetRecvBuf		recvBuf;		//���ӵĽ���buf
	NetBlock			recvCache;		//���ӵĵ�ǰ��Ϣ����buf

	boost::mutex		sendMutex;		//����buf���߳���
	boost::mutex		recvMutex;		//����buf���߳���

	GE::Uint16			waitWhoTime;	//�ȴ������֤��ʱ��
	GE::Uint16			waitRecvTime;	//�ȴ�������Ϣ��ʱ��
};
}
}



