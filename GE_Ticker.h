#pragma once
#include <map>
#include <mutex>

#include "GE.h"
#include "GE_PyObject.h"

class GE_Ticker
{
	typedef std::map<GE::Uint64, GE_PyFunction*>		RegTickMap;
public:
	virtual ~GE_Ticker(void);

public:
	GE::Uint64				RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef);	//ע��һ��Tick
	bool					UnregTick(GE::Int64 uID);																	//ȡ��һ��tick
	bool					TriggerTick(GE::Int64 uID);																	//ǿ�ƴ���һ��Tick
	bool					TriggerTick(GE::Int64 uID, PyObject* pyTrigger_BorrowRef);									//ǿ�ƴ���һ��Tick

	virtual bool			CallPerTime() = 0;																		    //ÿ������һ�Σ�����tick

    GE_PyObject&			GetPyObj() { return obj; }

protected:
	// ���еĶ�ͨ�������������������������ǲ����Ա������
	GE_Ticker(void);
	GE_Ticker(PyObject* pPyOwner_BorrowRef);

	void Init() {};

	RegTickMap rigsters;
	GE::Uint32	incId;
	GE_PyObject	obj;
};

// ���뼶��Ķ�ʱ��
class GE_ClockTicker : public GE_Ticker
{
public:
	~GE_ClockTicker() {};

	bool CallPerTime();

private:
	GE_SINGLETON(GE_ClockTicker)
};

//// �뼶��Ķ�ʱ��
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
//// ���Ӽ���Ķ�ʱ��
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
//// Сʱ����Ķ�ʱ��
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
//// �켶��Ķ�ʱ��
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

