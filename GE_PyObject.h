#pragma once
#include <map>
#include <memory>
#include <iostream>

#include <Python.h>

#include "GE.h"
#include "GE_Grocery.h"

class GE_PyObject;

class GE_PyFunction
{
public:
	GE_PyFunction(PyObject* args, bool NewRef = true);

	GE_PyObject* Call(GE_PyObject* args);

	~GE_PyFunction()
	{
		Py_XDECREF(obj);
	}
private:
	GE_BAN_COPY(GE_PyFunction)

	PyObject* obj;
};

class GE_PyObject
{
public:
	GE_PyObject():obj(nullptr){}

	GE_PyObject(PyObject* obj, bool NewRef = true):obj(obj)
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

	void GetAllFunctions()
	{
		if (obj == nullptr)
		{
			print("û�г�ʼ��py����");
			return;
		}
		print("�����������к���");
		// ������к���
		PyObject *const pDict = PyModule_GetDict(obj); // borrowed
		PyObject *pKey = nullptr, *pValue = nullptr;
		for (Py_ssize_t i = 0; PyDict_Next(pDict, &i, &pKey, &pValue);) //borrwed
		{
			const char *key = PyUnicode_AsUTF8(pKey);
			if (PyFunction_Check(pValue)) {
				std::cout << "���뺯�� " << key << " \n";
				m_funclist.emplace(std::make_pair(key, new GE_PyFunction(pValue)));
			}
		}
	}

	GE_PyObject* Call(const char * str);

	GE_PyObject* Call(const char * str, const std::initializer_list<PyObject*>& list);

	PyObject* GetPointer()
	{
		return obj;
	}

	~GE_PyObject()
	{
		Py_XDECREF(obj);
	}

private:
	GE_BAN_COPY(GE_PyObject)

	PyObject* obj;
	std::map<const char*, GE_PyFunction*, Fun_StrCmp> m_funclist;
};



