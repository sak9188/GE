#pragma once
#include <map>
#include <mutex>

#include "GE.h"
#include "GEPyObject.h"
#include "Singleton.h"

namespace GE
{
	class Ticker
	{
		typedef std::map<GE::Uint64, GE::GEPyFunction*>		RegTickMap;
	public:
		virtual ~Ticker(void);

	public:
		GE::Uint64				RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef);	//ע��һ��Tick
		bool					UnregTick(GE::Int64 uID);																	//ȡ��һ��tick
		bool					TriggerTick(GE::Int64 uID);																	//ǿ�ƴ���һ��Tick
		bool					TriggerTick(GE::Int64 uID, PyObject* pyTrigger_BorrowRef);									//ǿ�ƴ���һ��Tick

		virtual bool			CallPerTime() = 0;																		    //ÿ������һ�Σ�����tick

		GE::GEPyObject&			GetPyObj() { return obj; }

	protected:
		// ���еĶ�ͨ�������������������������ǲ����Ա������
		Ticker(void);
		Ticker(PyObject* pPyOwner_BorrowRef);

		void Init() {};

		RegTickMap rigsters;
		GE::Uint32	incId;
		GE::GEPyObject	obj;
	};

	// �뼶��Ķ�ʱ��
	class SlowTicker
		: public Ticker, public GE::Singleton<SlowTicker>
	{
	public:
		SlowTicker(void);
		~SlowTicker(void);
	};

	// ���Ӽ���Ķ�ʱ��
	class IntervalTicker
		: public Ticker, public GE::Singleton<IntervalTicker>
	{
	public:
		IntervalTicker(void);
		~IntervalTicker(void);
	};

	// Сʱ����Ķ�ʱ��
	class HourTicker
		: public Ticker, public GE::Singleton<HourTicker>
	{
	public:
		HourTicker();
		~HourTicker();
	};

	// �켶��Ķ�ʱ��
	class PeriodTicker
		: public Ticker, public GE::Singleton<PeriodTicker>
	{
	public:
		PeriodTicker(void);
		~PeriodTicker(void);
	};

}

