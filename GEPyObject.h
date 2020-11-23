#pragma once
#include <map>
#include <memory>
#include <iostream>

#include <Python.h>

#include "GE.h"
#include "Grocery.h"
#include "IO.h"

namespace GE
{
	class GEPyObject
	{
	public:
		GEPyObject() :obj(nullptr) {}
		GEPyObject(PyObject* obj, bool newRef = true) :obj(obj)
		{
			if (!newRef)
			{
				Py_XINCREF(obj); // borrowed
								 // ��������
			}
		}

		void SetPythonObject(PyObject* pobj)
		{
			if (IsNone())
			{
				this->obj = pobj;
				Py_XINCREF(pobj);
			}
			else
			{
				// ��ԭ���Ķ����һ������
				Py_XDECREF(obj);

				this->obj = pobj;
				Py_XINCREF(pobj);
			}
		}

		bool IsNone()
		{
			return obj == NULL || obj == nullptr;
		}

		PyObject* GetPointer()
		{
			return obj;
		}

		virtual ~GEPyObject()
		{
			Py_XDECREF(obj);
		}

	protected:
		PyObject* obj;

	private:
		GE_BAN_COPY(GEPyObject)

	};

	class GEPyFunction : public GEPyObject
	{
	public:
		GEPyFunction(PyObject* obj, bool newRef = false) : GEPyObject(obj, newRef) {}

		GEPyFunction(PyObject* args, PyObject* param, bool NewRef = true);

		// ���������Ĳ���
		GEPyObject* Call(PyObject* args);

		//����Ĭ�ϵĲ���
		GEPyObject* CallWithDefault();

		~GEPyFunction()
		{
			Py_XDECREF(obj);
		}

		PyObject* GetParamPointer() { return this->param; }
		PyObject* param;
	private:
		GE_BAN_COPY(GEPyFunction)
	};


	class GEPyMoudule : public GEPyObject
	{
	public:
		// ������
		GEPyMoudule() : GEPyObject(nullptr) {}

		// ����������
		GEPyMoudule(PyObject* obj) : GEPyObject(obj) {}
		GEPyMoudule(GEPyObject* obj) : GEPyObject(obj->GetPointer()) {}

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

		GEPyObject* Call(const char * str);
		GEPyObject* Call(const char * str, const std::initializer_list<PyObject*>& list);

		void GetAllFunctions()
		{
			if (obj == nullptr)
			{
				// print("û�г�ʼ��py����");
				GE_Error << "û�г�ʼ��py����\n";
				return;
			}
			GE_Info << "�����������к���\n";
			// ������к���
			PyObject *const pDict = PyModule_GetDict(obj); // borrowed
			PyObject *pKey = nullptr, *pValue = nullptr;
			for (Py_ssize_t i = 0; PyDict_Next(pDict, &i, &pKey, &pValue);) //borrwed
			{
				char *key = PyString_AsString(pKey);
				if (PyFunction_Check(pValue)) {
					std::cout << "���뺯�� " << key << " \n";
					funclist.emplace(std::make_pair(key, &GEPyFunction(pValue)));
				}
			}
		}

	private:
		GE_BAN_COPY(GEPyMoudule)
		std::map<char*, GEPyFunction*, Fun_StrCmp> funclist;
	};
}

