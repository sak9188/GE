#pragma once

#include "../GE.h"

#include <boost\thread.hpp>
#include <boost\asio.hpp>

#include "GE_NetMgr.h"
#include "GE_NetConnect.h"

class MsgBase;

class GE_NetWork
{
	GE_BAN_COPY(GE_NetWork)
public:
	GE_NetWork(GE::Uint32 maxConnect, GE::Uint16 thread);
	~GE_NetWork(void);

	// ����һ���˿�
	bool Listen(GE::Uint32 port);
	
	// ��ʼ����
	void Start();
	
	// ֹͣ
	void Stop();

	// ����һ��Զ��ip���˿�
	bool Connect(const char* sIP, GE::Uint32 uPort, GE::Uint32& uSessionID, GE::Uint16 uWho, void* pBindPoint, ConnectParam* pCP = NULL);
	
	// �Ͽ�һ������
	void DisConnect(GE::Uint32 uSessionID);
	
	// �ӳٶϿ�һ������
	void DelayDisConnect(GE::Uint32 uSessionID, GE::Int32 nDelayTime);
	
	// ����һ������
	void ClearConnect(GE::Uint32 uSessionID);
	
	// ��������ʱ��
	void SetWaitTime(GE::Uint32 uSessionID, GE::Uint16 uWaitWhoTime, GE::Uint16 uWaitRecvTime);
	
	// �Ƿ���ĳ������
	bool HasConnect(GE::Uint32 uSessionID);
	
	// ��uSessionID���ӷ���һ���ֽڣ��̲߳���ȫ��ֻ���߼��̵߳��ã�
	void SendBytesST(GE::Uint32 uSessionID, const void* pHead, GE::Uint16 uSize);
	
	// ��uSessionID���ӷ���һ���ֽڣ��̰߳�ȫ��
	void SendBytesMT(GE::Uint32 uSessionID, const void* pHead, GE::Uint16 uSize);
	
	// �Ƿ�����㻹��������
	bool IsRun() { return isRun; }
	
	// �Ƿ����ݷ������
	bool IsSendOver(GE::Uint32 uSessionID);
	
	// �����첽����ģʽ
	void AsyncSendWho(GE::Uint16 uAsycnSendWho);
	
	// ��ȡ�첽����
	GE::Uint16 AsyncSendWho() { return asyncSendWho; }
	
	// ���첽����ģʽ�£���ǻ�������
	void AsyncHasData(GE::Uint32 uSessionID);
	
	// ��ȡIP
	bool GetSessionIP(GE::Uint32 uSessionID, std::string& sIP);
	
	// ǿ�ƶϿ��Ƿ�����
	void				ForceShutdownIllegalConnect_L();

	// ��ȡ��Ϣ�ĺ�����
	bool				MoveNextMsg();
	void				SetCurWho(GE::Uint16 uWho) { curConnect->Who(uWho); }
	void				SetCurPoint(void* p) { curConnect->BindPoint(p); }
	void				SetCurLong(GE::Uint64 ui64) { curConnect->BindLong(ui64); }
	GE::Uint32			CurSessionID() { return curConnect->SessionID(); }
	GE::Uint16			CurWho() { return curConnect->Who(); }
	void*				CurPoint() { return curConnect->BindPoint(); }
	GE::Uint64			CurLong() { return curConnect->BindLong(); }
	GE::Uint32			CurReadMsgCount() { return curConnect->ReadMsgCount(); }
	GE::Uint32			CurSendMsgCount() { return curConnect->SendMsgCount(); }

	// MsgBase*			CurMsg() { return m_pCurMsg; }
	bool				CurIsClose() { return lastConnectClose; }
	bool				CurIsRound() { return iterCnt == 0; }
	void				CurRemoteEndPoint(std::string& sIP, GE::Uint32& uPort) { curConnect->RemoteEndPoint(sIP, uPort); }

	// Boost ASIO
	boost::asio::io_service&		IOS() { return ios; }

	// DebugInfo
	NetInfoVector		GetDebugInfoList_L();

private:
	/*
	���溯���ĺ�׺_N��ʶ�ú���ֻ���������̵̳߳��ã���������߳����⡣
	*/
	// �첽��������
	void AsyncAccept_N();
	void HandleAccept_N(GE_NetConnect::ConnectSharedPtr spConnect, const boost::system::error_code& error);
	void ForceShutdownIllegalConnect_us();
	void AsyncSendFun();
	void BoostAsioRun();
	void DebugRun();
	void AddOutput_N(const char* pS, GE::Int64 p1);
	void AddOutput_N(const char* pS, GE::Int64 p1, GE::Int64 p2);
	void AddOutput_N(const char* pS, const char* p1);
	void PrintOutPut_L();

private:
	// ���ӹ��������߳���
	GE_NetMgr connectMgr;
	boost::mutex connectMutex;

	// boost��asio���
	bool isRun;
	bool isStop;
	boost::asio::io_service ios;

	boost::asio::ip::tcp::acceptor*	acceptor;
	std::vector<boost::thread*> netWorkThreads;

	GE::Uint16 asyncSendWho;
	boost::thread* asyncSendThread;
	boost::thread* debugThread;

	// ���̵߳��������ΪGEIO��֧��IO���߻ᵼ�²��ܶ��߳��´�ӡ��
	boost::mutex		outpubMutex;
	std::vector<std::string>		outputVector;

	// ��ǰ��Ϣ�Ļ���
	GE_NetConnect*		curConnect;
	MsgBase*			curMsg;
	GE::Uint32			iterCnt;
	bool				lastConnectClose;

	// ͳ����Ϣ
	GE::Uint32			lastSessionID;
	GE::Uint32			msgCnt;
	GE::Uint32			maxConnect;
};