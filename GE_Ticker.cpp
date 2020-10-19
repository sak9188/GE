#include "GE_Ticker.h"


GE_Ticker::GE_Ticker()
{
}


GE_Ticker::~GE_Ticker()
{
}


GE::Uint64 GE_Ticker::RegTick(GE::Uint32 uTimeSec, PyObject* pyCallBack_BorrowRef, PyObject* pyParam_BorrowRef)
{
	// �ۼ�ID
	++incId;
	// ����headerʱ��
	GE::Uint64 uTouchTime = 1; // GE_DateTime::Instance()->Seconds() + uTimeSec;
	// ����ID��ʱ��Ϊ��32λ����32λΪ�۽�������ʹ�ô洢��Map���ǰ�ʱ�������
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
	// �������ü���(����ֱ��ί��C����������ͷţ������ü�����1)
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

	// ע������Ҫ����һ���ٴ�Map��ɾ��
	GE_PyFunction *PF = _iter->second;
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
			Py_DECREF(pyResult_NewRef);
		}
	}
	// �������ü���
	Py_DECREF(PF->GetPointer());
	Py_DECREF(PF->GetParamPointer());

	// ɾ�����ָ��
	GE_SAFE_DELETE(PF)
	return true;
}