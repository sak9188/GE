#pragma once
#include <vector>

#include <boost\unordered_map.hpp>
#include <boost\thread\mutex.hpp>

#include <map>

#include "..\GE.h"

namespace GE
{
	namespace Net
	{
		class NetConnect;

		class NetMgr
		{
			GE_BAN_COPY(NetMgr);
		public:
			NetMgr(GE::Uint32 uMaxConnect);
			~NetMgr(void);

		public:
			// bool				AddConnect(boost::shared_ptr<GE_NetConnect>& spConnect, GE::Uint32& uID);	//����һ������
			// bool				DelConnect(GE::Uint32 uID);												//ɾ��һ������
			// bool				HasConnect(GE::Uint32 uID);												//�Ƿ���ĳ������
			// GE_NetConnect*		FindConnect(GE::Uint32 uID);											//����һ�����ӣ�ͨ��ID��
			// GE_NetConnect*		FindConnectForHasData(GE::Uint32 uID);									//����һ�����ӣ�Ϊ�˷������ݣ�
			// GE_NetConnect*		NextConnect();															//��ȡ��һ�����ӣ��ڲ�ѭ����������ɾ���ӵ�����Ȼ��Ч��
			// GE::Uint32			ConnectCnt() { return m_IndexMgr.UseSize(); }							//���ӵ�����
			// GE::Uint32			EmptyCnt() { return m_IndexMgr.FreeSize(); }							//���е�����
			// void				ConnectHasData(GE::Uint32 uID);											//�������������
			// void				Lock(GE::Uint32 uID);													//��סĳ������
			// void				Unlock(GE::Uint32 uID);													//�ͷ�ĳ������
			// bool				DriverAsyncSendBlock();													//�������Ե������첽������Ϣ�������Ƿ������ӷ��͵��������ܴ�
			// void				DelAllConnect();														//ɾ�����е�����

		private:
			// std::map<>			indexMgr;			//����ID������
			NetMgr**			dataArr;			//��������
			bool*				hasData;			//�Ƿ���δ���͵�����
			boost::unordered_map<GE::Uint32, boost::shared_ptr<NetConnect> >				m_pDataMap;			//����hold����ָ���map
			std::vector<boost::mutex*>			mutexVector;		//��������ÿ�����ӵ�����������������ײ��
		};
	}
}



