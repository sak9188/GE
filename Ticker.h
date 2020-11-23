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
		GE::Uint64				RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef);	//注册一个Tick
		bool					UnregTick(GE::Int64 uID);																	//取消一个tick
		bool					TriggerTick(GE::Int64 uID);																	//强制触发一个Tick
		bool					TriggerTick(GE::Int64 uID, PyObject* pyTrigger_BorrowRef);									//强制触发一个Tick

		virtual bool			CallPerTime() = 0;																		    //每个周期一次，驱动tick

		GE::GEPyObject&			GetPyObj() { return obj; }

	protected:
		// 所有的都通过下面的子类来驱动，这个类是不可以被构造的
		Ticker(void);
		Ticker(PyObject* pPyOwner_BorrowRef);

		void Init() {};

		RegTickMap rigsters;
		GE::Uint32	incId;
		GE::GEPyObject	obj;
	};

	// 秒级别的定时器
	class SlowTicker
		: public Ticker, public GE::Singleton<SlowTicker>
	{
	public:
		SlowTicker(void);
		~SlowTicker(void);
	};

	// 分钟级别的定时器
	class IntervalTicker
		: public Ticker, public GE::Singleton<IntervalTicker>
	{
	public:
		IntervalTicker(void);
		~IntervalTicker(void);
	};

	// 小时级别的定时器
	class HourTicker
		: public Ticker, public GE::Singleton<HourTicker>
	{
	public:
		HourTicker();
		~HourTicker();
	};

	// 天级别的定时器
	class PeriodTicker
		: public Ticker, public GE::Singleton<PeriodTicker>
	{
	public:
		PeriodTicker(void);
		~PeriodTicker(void);
	};

}

