#include "GE_Ticker.h"


GE_Ticker::GE_Ticker()
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
	GE::Uint32 uTouchTime = GE_DateTime::Instance()->Seconds() + uTimeSec;
	// 构建ID，时间为高32位，低32位为累进计数，使得存储到Map中是按时间排序的
	auto uid = uTouchTime << 32 + incId;
	Py_INCREF(pyCallBack_BorrowRef);
	Py_INCREF(pyParam_BorrowRef);

	GE_PyFunction PF(pyCallBack_BorrowRef, pyParam_BorrowRef);
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
	// 减少引用计数(这里直接委托C对象给析构释放，且引用计数减1)
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
	GE_PyFunction PF(std::move(_iter->second));
	// 先从Map中删除,防止在下面的函数调用中修改_iter
	this->rigsters.erase(_iter);

	if (this->obj.IsNone())
	{
		PyObject* pyResult_NewRef = PyObject_CallFunctionObjArgs(PF.GetPointer(), pyTrigger_BorrowRef, PF.GetParamPointer(), NULL);
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
	Py_DECREF(PF.GetPointer());
	Py_DECREF(PF.GetParamPointer());
	return true;
}