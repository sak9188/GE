#pragma once

#include "../GE.h"

#include <boost\thread.hpp>
#include <boost\asio.hpp>

#include "NetStruct.h"
#include "NetMgr.h"

namespace GE
{
	namespace Net
	{
		class MsgBase;
		class NetConnect;

		class NetWork
		{
			GE_BAN_COPY(NetWork)
		public:
			NetWork(GE::Uint32 maxConnect, GE::Uint16 thread);
			~NetWork(void);

			// 监听一个端口
			bool Listen(GE::Uint32 port);
			
			// 开始工作
			void Start();
			
			// 停止
			void Stop();

			// 连接一个远程ip、端口
			bool Connect(const char* sIP, GE::Uint32 uPort, GE::Uint32& uSessionID, GE::Uint16 uWho, void* pBindPoint, GE::Net::ConnectParam* pCP = NULL);
			
			//// 断开一个连接
			//void DisConnect(GE::Uint32 uSessionID);
			//
			//// 延迟断开一个连接
			//void DelayDisConnect(GE::Uint32 uSessionID, GE::Int32 nDelayTime);
			//
			//// 清理一个连接
			//void ClearConnect(GE::Uint32 uSessionID);
			//
			//// 设置连接时间
			//void SetWaitTime(GE::Uint32 uSessionID, GE::Uint16 uWaitWhoTime, GE::Uint16 uWaitRecvTime);
			//
			//// 是否有某个连接
			//bool HasConnect(GE::Uint32 uSessionID);
			//
			//// 给uSessionID连接发送一段字节（线程不安全，只能逻辑线程调用）
			//void SendBytesST(GE::Uint32 uSessionID, const void* pHead, GE::Uint16 uSize);
			//
			//// 给uSessionID连接发送一段字节（线程安全）
			//void SendBytesMT(GE::Uint32 uSessionID, const void* pHead, GE::Uint16 uSize);
			//
			//// 是否网络层还在运行中
			//bool IsRun() { return isRun; }
			//
			//// 是否数据发送完毕
			//bool IsSendOver(GE::Uint32 uSessionID);
			//
			//// 设置异步发送模式
			//void AsyncSendWho(GE::Uint16 uAsycnSendWho);
			//
			//// 获取异步发送
			//GE::Uint16 AsyncSendWho() { return asyncSendWho; }
			//
			//// 在异步发送模式下，标记还有数据
			//void AsyncHasData(GE::Uint32 uSessionID);
			//
			//// 获取IP
			//bool GetSessionIP(GE::Uint32 uSessionID, std::string& sIP);
			//
			//// 强制断开非法连接
			//void				ForceShutdownIllegalConnect_L();

			// 获取消息的函数簇
			// bool				MoveNextMsg();
			//void				SetCurWho(GE::Uint16 uWho) { curConnect->Who(uWho); }
			//void				SetCurPoint(void* p) { curConnect->BindPoint(p); }
			//void				SetCurLong(GE::Uint64 ui64) { curConnect->BindLong(ui64); }
			//GE::Uint32			CurSessionID() { return curConnect->SessionID(); }
			//GE::Uint16			CurWho() { return curConnect->Who(); }
			//void*				CurPoint() { return curConnect->BindPoint(); }
			//GE::Uint64			CurLong() { return curConnect->BindLong(); }
			//GE::Uint32			CurReadMsgCount() { return curConnect->ReadMsgCount(); }
			//GE::Uint32			CurSendMsgCount() { return curConnect->SendMsgCount(); }

			//// MsgBase*			CurMsg() { return m_pCurMsg; }
			//bool				CurIsClose() { return lastConnectClose; }
			//bool				CurIsRound() { return iterCnt == 0; }
			//void				CurRemoteEndPoint(std::string& sIP, GE::Uint32& uPort) { curConnect->RemoteEndPoint(sIP, uPort); }

			// Boost ASIO
			boost::asio::io_service&		IOS() { return ios; }

			// DebugInfo
			// std::vector<GE_NetInfo> GetDebugInfoList_L();

		private:
			/*
			下面函数的后缀_N标识该函数只能在网络线程程调用，否则会有线程问题。
			*/
			// 异步接收连接

			//void AsyncAccept_N();
			//void HandleAccept_N(boost::shared_ptr<GE_NetConnect> spConnect, const boost::system::error_code& error);
			//void ForceShutdownIllegalConnect_us();
			//void AsyncSendFun();
			//void BoostAsioRun();
			//void DebugRun();
			//void AddOutput_N(const char* pS, GE::Int64 p1);
			//void AddOutput_N(const char* pS, GE::Int64 p1, GE::Int64 p2);
			//void AddOutput_N(const char* pS, const char* p1);
			//void PrintOutPut_L();

		private:
			// 连接管理器、线程锁
			NetMgr connectMgr;
			boost::mutex connectMutex;

			// boost的asio相关
			bool isRun;
			bool isStop;
			boost::asio::io_service ios;

			boost::asio::ip::tcp::acceptor*	acceptor;
			std::vector<boost::thread*> netWorkThreads;

			GE::Uint16 asyncSendWho;
			boost::thread* asyncSendThread;
			boost::thread* debugThread;

			// 多线程的输出【因为GEIO中支持IO工具会导致不能多线程下打印】
			boost::mutex		outpubMutex;
			std::vector<std::string>		outputVector;

			// 当前消息的缓存
			NetConnect*			curConnect;
			MsgBase*			curMsg;
			GE::Uint32			iterCnt;
			bool				lastConnectClose;

			// 统计信息
			GE::Uint32			lastSessionID;
			GE::Uint32			msgCnt;
			GE::Uint32			maxConnect;
		};
	}
}
