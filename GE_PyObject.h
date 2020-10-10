#pragma once
#include <map>
#include <memory>
#include <iostream>

#include <Python.h>

#include "GE.h"
#include "GE_Grocery.h"

class GE_PyObject;

class GE_PyFunction : public GE_PyObject
{
public:

	GE_PyFunction(PyObject* obj, bool newRef = false) : GE_PyObject(obj, newRef){}

	GE_PyFunction(PyObject* args, PyObject* param, bool NewRef = true);
	
	// 调用其他的参数
	GE_PyObject* Call(PyObject* args);

	//调用默认的参数
	GE_PyObject* CallWithDefault();

	~GE_PyFunction()
	{
		Py_XDECREF(obj);
	}

private:
	GE_BAN_COPY(GE_PyFunction)
	PyObject* param;
};

class GE_PyObject
{
public:
	GE_PyObject():obj(nullptr){}
	GE_PyObject(PyObject* obj, bool newRef = true) :obj(obj)
	{
		if (obj == NULL)
		{
			obj = nullptr;
			PyErr_Print();
			print("构造GE_PyObject对象失败");
		}
		if (!newRef)
		{
			Py_XINCREF(obj); // borrowed
			// 增加引用
		}
	}

	PyObject* GetPointer()
	{
		return obj;
	}

	virtual ~GE_PyObject()
	{
		Py_XDECREF(obj);
	}

protected:
	PyObject* obj;

private:
	GE_BAN_COPY(GE_PyObject)

};


class GE_PyMoudule : public GE_PyObject
{
	GE_PyMoudule() : GE_PyObject(nullptr){}

	bool LoadModule(const char * str)
	{
		if (obj == nullptr)
		{
			obj = PyImport_ImportModule(str);
		}
		else
		{
			Py_XDECREF(obj);
			obj = PyImport_ImportModule(str);
			Py_XINCREF(obj);
		}
	}

	GE_PyObject* Call(const char * str);
	GE_PyObject* Call(const char * str, const std::initializer_list<PyObject*>& list);

	void GetAllFunctions()
	{
		if (obj == nullptr)
		{
			print("没有初始化py对象");
			return;
		}
		print("尝试载入所有函数");
		// 获得所有函数
		PyObject *const pDict = PyModule_GetDict(obj); // borrowed
		PyObject *pKey = nullptr, *pValue = nullptr;
		for (Py_ssize_t i = 0; PyDict_Next(pDict, &i, &pKey, &pValue);) //borrwed
		{
			const char *key = PyUnicode_AsUTF8(pKey);
			if (PyFunction_Check(pValue)) {
				std::cout << "载入函数 " << key << " \n";
				funclist.emplace(std::make_pair(key, GE_PyFunction(pValue)));
			}
		}
	}

private:
	GE_BAN_COPY(GE_PyMoudule)

	std::map<const char*, GE_PyFunction&, Fun_StrCmp> funclist;
};
