#include "Ticker.h"

GE::Ticker::Ticker()
{
}

GE::Ticker::Ticker(PyObject * pPyOwner_BorrowRef) : obj(pPyOwner_BorrowRef)
{
}


GE::Ticker::~Ticker()
{
}


GE::Uint64 GE::Ticker::RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef)
{
	// �ۼ�ID
	++incId;
	// ����headerʱ��
	GE::Uint64 uTouchTime = 1; // GE_DateTime::Instance()->Seconds() + uTimeSec;
	// ����ID��ʱ��Ϊ��32λ����32λΪ�۽�������ʹ�ô洢��Map���ǰ�ʱ�������
	GE::Uint64 uid = (uTouchTime << 32) + incId;
	Py_XINCREF(pyCallBack_BorrowRef);
	Py_XINCREF(pyParam_BorrowRef);

	GE::GEPyFunction *PF = new GE::GEPyFunction(pyCallBack_BorrowRef, pyParam_BorrowRef);
	this->rigsters.insert(std::make_pair(uid, PF));
	return uid;
}

bool GE::Ticker::UnregTick(GE::Int64 uID)
{
	RegTickMap::iterator _iter = this->rigsters.find(uID);
	if (_iter == this->rigsters.end())
	{
		return false;
	}
	// �������ü���
	GE::GEPyFunction *PF = _iter->second;

	// �������ü���
	Py_XDECREF(PF->GetPointer());
	Py_XDECREF(PF->GetParamPointer());

	// ɾ�����ָ��
	GE_SAFE_DELETE(PF)

	this->rigsters.erase(_iter);
	return true;
}

bool GE::Ticker::TriggerTick(GE::Int64 uID)
{
	return this->TriggerTick(uID, Py_None);
}

bool GE::Ticker::TriggerTick(GE::Int64 uID, PyObject* pyTrigger_BorrowRef)
{
	RegTickMap::iterator _iter = this->rigsters.find(uID);
	if (_iter == this->rigsters.end())
	{
		return false;
	}

	// ע������Ҫ����һ���ٴ�Map��ɾ��
	GE::GEPyFunction *PF = _iter->second;
	// �ȴ�Map��ɾ��,��ֹ������ĺ����������޸�_iter
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
			Py_XDECREF(pyResult_NewRef);
		}
	}
	// �������ü���
	Py_XDECREF(PF->GetPointer());
	Py_XDECREF(PF->GetParamPointer());

	// ɾ�����ָ��
	GE_SAFE_DELETE(PF)
	return true;
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
//

GE::SlowTicker::SlowTicker(void)
{
}

GE::SlowTicker::~SlowTicker(void)
{
}

GE::IntervalTicker::IntervalTicker(void)
{
}

GE::IntervalTicker::~IntervalTicker(void)
{
}

GE::HourTicker::HourTicker()
{
}

GE::HourTicker::~HourTicker()
{
}

GE::PeriodTicker::PeriodTicker(void)
{
}

GE::PeriodTicker::~PeriodTicker(void)
{
}
