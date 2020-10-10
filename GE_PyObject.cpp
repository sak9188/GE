#include "GE_PyObject.h"

GE_PyFunction::GE_PyFunction(PyObject* args, PyObject* param, bool NewRef) : GE_PyObject(args, false), param(param)
{

	if (!NewRef)
	{
		Py_XINCREF(obj); // borrowed
	}
}

GE_PyObject* GE_PyFunction::Call(PyObject* args)
{
	PyObject* pyResult_NewRef = nullptr;
	if (args == nullptr)
	{
		pyResult_NewRef = PyEval_CallObject(obj, NULL);
	}
	else
	{
		pyResult_NewRef = PyEval_CallObject(obj, args);
	}

	if (NULL == pyResult_NewRef)
	{
		PyErr_Print();
	}
	return new GE_PyObject(pyResult_NewRef);
}

GE_PyObject* GE_PyMoudule::Call(const char * str)
{
	if (obj == nullptr)
	{
		print("没有初始化py对象");
		return nullptr;
	}
	// 调用函数
	GE_PyObject* result = nullptr;
	try
	{
		result = funclist.at(str).Call(nullptr);
	}
	catch (const std::exception&)
	{
		print("没有这个函数");
		print(str);
		return nullptr;
	}
	return result;
}

GE_PyObject* GE_PyMoudule::Call(const char * str, const std::initializer_list<PyObject*>& list)
{
	if (obj == nullptr)
	{
		print("没有初始化py对象");
		return nullptr;
	}
	// 调用函数
	auto args = PyTuple_New(list.size());
	GE_PyObject* result = nullptr;
	int count = 0;
	for (auto e : list)
	{
		PyTuple_SetItem(args, count++, e);
	}
	try
	{
		result = funclist.at(str).Call(args);
	}
	catch (const std::exception&)
	{
		print("没有这个函数");
		print(str);
		return nullptr;
	}
	return result;
}