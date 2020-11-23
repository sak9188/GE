#include "GEPyObject.h"

#include "IO.h"

GE::GEPyFunction::GEPyFunction(PyObject* args, PyObject* param, bool NewRef) : GE::GEPyObject(args, false), param(param)
{

	if (!NewRef)
	{
		Py_XINCREF(obj); // borrowed
	}
}

GE::GEPyObject* GE::GEPyFunction::Call(PyObject* args)
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
	return new GE::GEPyObject(pyResult_NewRef);
}

GE::GEPyObject* GE::GEPyMoudule::Call(const char * str)
{
	if (obj == nullptr)
	{
		GE_Error << "没有初始化py对象\n";
		return nullptr;
	}
	try
	{
		return funclist.at(const_cast<char*>(str))->Call(nullptr);
	}
	catch (const std::exception&)
	{
		GE_Error << "没有这个函数" << str <<"\n";
		return nullptr;
	}
}

GE::GEPyObject* GE::GEPyMoudule::Call(const char * str, const std::initializer_list<PyObject*>& list)
{
	if (obj == nullptr)
	{
		GE_Error << "没有初始化py对象\n";
		return nullptr;
	}
	// 调用函数
	auto args = PyTuple_New(list.size());
	int count = 0;
	for (auto e : list)
	{
		PyTuple_SetItem(args, count++, e);
	}
	try
	{
		return funclist.at(const_cast<char*>(str))->Call(args);
	}
	catch (const std::exception&)
	{
		GE_Error << "没有这个函数" << str << "\n";
		return nullptr;
	}
}