#include "GE_Ticker.h"


GE_Ticker::GE_Ticker()
{
}

GE_Ticker::GE_Ticker(PyObject * pPyOwner_BorrowRef) : obj(pPyOwner_BorrowRef)
{
}


GE_Ticker::~GE_Ticker()
{
}


GE::Uint64 GE_Ticker::RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef)
{
	// 累加ID
	++incId;
	// 计算header时间
	GE::Uint64 uTouchTime = 1; // GE_DateTime::Instance()->Seconds() + uTimeSec;
	// 构建ID，时间为高32位，低32位为累进计数，使得存储到Map中是按时间排序的
	GE::Uint64 uid = (uTouchTime << 32) + incId;
	Py_INCREF(pyCallBack_BorrowRef);
	Py_INCREF(pyParam_BorrowRef);

	GE_PyFunction *PF = new GE_PyFunction(pyCallBack_BorrowRef, pyParam_BorrowRef);
	this->rigsters.insert(std::make_pair(uid, PF));
	return uid;
}

bool GE_Ticker::UnregTick(GE::Int64 uID)
{
	RegTickMap::iterator _iter = this->rigsters.find(uID);
	if (_iter == this->rigsters.end())
	{
		return false;
	}
	// 减少引用计数
	GE_PyFunction *PF = _iter->second;

	// 减少引用计数
	Py_DECREF(PF->GetPointer());
	Py_DECREF(PF->GetParamPointer());

	// 删掉这个指针
	GE_SAFE_DELETE(PF)

	this->rigsters.erase(_iter);
	return true;
}

bool GE_Ticker::TriggerTick(GE::Int64 uID)
{
	return this->TriggerTick(uID, Py_None);
}

bool GE_Ticker::TriggerTick(GE::Int64 uID, PyObject* pyTrigger_BorrowRef)
{
	RegTickMap::iterator _iter = this->rigsters.find(uID);
	if (_iter == this->rigsters.end())
	{
		return false;
	}

	// 注意这里要拷贝一份再从Map中删除
	GE_PyFunction *PF = _iter->second;
	// 先从Map中删除,防止在下面的函数调用中修改_iter
	this->rigsters.erase(_iter);

	if (this->obj.IsNone())
	{
		PyObject* pyResult_NewRef = PyObject_CallFunctionObjArgs(PF->GetPointer(), pyTrigger_BorrowRef, PF->GetParamPointer(), NULL);
		if (NULL == pyResult_NewRef)
		{
			PyErr_Print();
		}
		else
		{
			Py_DECREF(pyResult_NewRef);
		}
	}
	// 减少引用计数
	Py_DECREF(PF->GetPointer());
	Py_DECREF(PF->GetParamPointer());

	// 删掉这个指针
	GE_SAFE_DELETE(PF)
	return true;
}

bool GE_ClockTicker::CallPerTime()
{
	return false;
}

//GE_ClockTicker::~GE_ClockTicker()
//{
//}
//
//GE_SlowTicker::~GE_SlowTicker()
//{
//}
//
//GE_IntervalTicker::~GE_IntervalTicker()
//{
//}
//
//GE_HourTicker::~GE_HourTicker()
//{
//}
//
//GE_PeriodTicker::~GE_PeriodTicker()
//{
//}


