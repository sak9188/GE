#include "GE_PyObject.h"

GE_PyFunction::GE_PyFunction(PyObject* args, bool NewRef) : obj(args)
{
	if (obj == NULL)
	{
		obj = nullptr;
		PyErr_Print();
		print("����GE_PyObject����ʧ��");
	}

	if (!NewRef)
	{
		Py_XINCREF(obj); // borrowed
						 // ��������
	}
}

GE_PyObject* GE_PyFunction::Call(GE_PyObject* args)
{
	PyObject* pyResult_NewRef = nullptr;
	if (args == nullptr)
	{
		pyResult_NewRef = PyEval_CallObject(obj, NULL);
	}
	else
	{
		pyResult_NewRef = PyEval_CallObject(obj, args->GetPointer());
	}

	if (NULL == pyResult_NewRef)
	{
		PyErr_Print();
	}
	return new GE_PyObject(pyResult_NewRef);
}

GE_PyObject* GE_PyObject::Call(const char * str)
{
	if (obj == nullptr)
	{
		print("û�г�ʼ��py����");
		return nullptr;
	}
	// ���ú���
	GE_PyObject* result = nullptr;
	try
	{
		result = m_funclist.at(str)->Call(nullptr);
	}
	catch (const std::exception&)
	{
		print("û���������");
		print(str);
		return nullptr;
	}
	return result;
}

GE_PyObject* GE_PyObject::Call(const char * str, const std::initializer_list<PyObject*>& list)
{
	if (obj == nullptr)
	{
		print("û�г�ʼ��py����");
		return nullptr;
	}
	// ���ú���
	auto args = std::make_shared<GE_PyObject>(PyTuple_New(list.size()));
	GE_PyObject* result = nullptr;
	int count = 0;
	for (auto e : list)
	{
		PyTuple_SetItem(args.get()->GetPointer(), count++, e);
	}
	try
	{
		result = m_funclist.at(str)->Call(args.get());
	}
	catch (const std::exception&)
	{
		print("û���������");
		print(str);
		return nullptr;
	}
	return result;
}