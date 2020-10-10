#pragma once
#include <map>

#include "GE.h"
#include "GE_Python.h"

class GE_Ticker
{
	typedef std::map<GE::Uint64, GE_PyFunction>		RegTickMap;
public:
	GE_Ticker(void);
	GE_Ticker(PyObject* pPyOwner_BorrowRef);
	virtual ~GE_Ticker(void);

public:
	GE::Uint64				RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef);	//ע��һ��Tick
	bool					UnregTick(GE::Int64 uID);																	//ȡ��һ��tick
	bool					TriggerTick(GE::Int64 uID);																	//ǿ�ƴ���һ��Tick
	bool					TriggerTick(GE::Int64 uID, PyObject* pyTrigger_BorrowRef);									//ǿ�ƴ���һ��Tick

	virtual void			CallPerTime() = delete;																		//ÿ������һ�Σ�����tick

	GE_PyObject&			GetPyObj() { return obj; }

protected:
	RegTickMap rigsters;
	GE_PyObject	obj;
	GE::Uint32	incId;
};

// ���뼶��Ķ�ʱ��
class GE_ClockTicker : public GE_Ticker
{
public:
	GE_ClockTicker();
	~GE_ClockTicker();

private:
	GE_SINGLETON(GE_ClockTicker)
};

GE_SET_SINGLETON(GE_ClockTicker)

// �뼶��Ķ�ʱ��
class GE_SlowTicker : public GE_Ticker
{
public:
	GE_SlowTicker();
	~GE_SlowTicker();

private:
	GE_SINGLETON(GE_SlowTicker)
};

GE_SET_SINGLETON(GE_SlowTicker)

// ���Ӽ���Ķ�ʱ��
class GE_IntervalTicker : public GE_Ticker
{
public:
	GE_IntervalTicker();
	~GE_IntervalTicker();

private:
	GE_SINGLETON(GE_IntervalTicker)
};

GE_SET_SINGLETON(GE_IntervalTicker)

// Сʱ����Ķ�ʱ��
class GE_HourTicker : public GE_Ticker
{
public:
	GE_HourTicker();
	~GE_HourTicker();
};

// �켶��Ķ�ʱ��
class GE_PeriodTicker : public GE_Ticker
{
public:
	GE_PeriodTicker();
	~GE_PeriodTicker();

private:
	GE_SINGLETON(GE_PeriodTicker)
};

GE_SET_SINGLETON(GE_PeriodTicker)

