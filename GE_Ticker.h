#pragma once
#include <map>

#include "GE.h"
#include "GE_PyObject.h"

class GE_Ticker
{
	typedef std::map<GE::Uint64, GE_PyFunction*>		RegTickMap;
public:
	GE_Ticker(void);
	GE_Ticker(PyObject* pPyOwner_BorrowRef);
	virtual ~GE_Ticker(void);

public:
	GE::Uint64				RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef);	//注册一个Tick
	bool					UnregTick(GE::Int64 uID);																	//取消一个tick
	bool					TriggerTick(GE::Int64 uID);																	//强制触发一个Tick
	bool					TriggerTick(GE::Int64 uID, PyObject* pyTrigger_BorrowRef);									//强制触发一个Tick

	// virtual void			CallPerTime() = delete;																		//每个周期一次，驱动tick

    GE_PyObject&			GetPyObj() { return obj; }

protected:
	void Init() {};

	RegTickMap rigsters;
	GE::Uint32	incId;
	GE_PyObject	obj;
};

//// 毫秒级别的定时器
//class GE_ClockTicker : public GE_Ticker
//{
//public:
//	~GE_ClockTicker();
//
//private:
//	GE_SINGLETON(GE_ClockTicker)
//};
//
//GE_SET_SINGLETON(GE_ClockTicker)
//
//// 秒级别的定时器
//class GE_SlowTicker : public GE_Ticker
//{
//public:
//	~GE_SlowTicker();
//
//private:
//	GE_SINGLETON(GE_SlowTicker)
//};
//
//GE_SET_SINGLETON(GE_SlowTicker)
//
//// 分钟级别的定时器
//class GE_IntervalTicker : public GE_Ticker
//{
//public:
//	~GE_IntervalTicker();
//
//private:
//	GE_SINGLETON(GE_IntervalTicker)
//};
//
//GE_SET_SINGLETON(GE_IntervalTicker)
//
//// 小时级别的定时器
//class GE_HourTicker : public GE_Ticker
//{
//public:
//	~GE_HourTicker();
//
//private:
//	GE_SINGLETON(GE_HourTicker)
//};
//GE_SET_SINGLETON(GE_HourTicker)
//
//// 天级别的定时器
//class GE_PeriodTicker : public GE_Ticker
//{
//public:
//	~GE_PeriodTicker();
//
//private:
//	GE_SINGLETON(GE_PeriodTicker)
//};
//
//GE_SET_SINGLETON(GE_PeriodTicker)

