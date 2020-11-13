#pragma once

#include "..\GE.h"

#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\enable_shared_from_this.hpp>

#include "GE_NetBlock.h"

class GE_NetWork;

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

class GE_NetConnect
	: public boost::enable_shared_from_this<GE_NetConnect>
{
	GE_BAN_COPY(GE_NetConnect)
public:
	GE_NetConnect();
	~GE_NetConnect();

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

private:
	GE_NetWork*			netWork;
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
	GE_NetSendBuf		sendBuf;		//���ӵķ���buf
	GE_NetRecvBuf		recvBuf;		//���ӵĽ���buf
	GE_NetBlock			recvCache;		//���ӵĵ�ǰ��Ϣ����buf

	boost::mutex		sendMutex;		//����buf���߳���
	boost::mutex		recvMutex;		//����buf���߳���

	GE::Uint16			m_uWaitWhoTime;		//�ȴ������֤��ʱ��
	GE::Uint16			m_uWaitRecvTime;	//�ȴ�������Ϣ��ʱ��
};

