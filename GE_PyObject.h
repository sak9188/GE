#pragma once
#include <Python.h>
#include <map>
#include <memory>

class GE_PyObject
{
public:
	GE_PyObject():obj(nullptr){}

	GE_PyObject(PyObject* obj)
	{
		Py_XINCREF(obj);
	}

	bool LoadModule(const char * str)
	{
		obj = PyImport_ImportModule(str);
	}

	bool GetAllFunctions()
	{
		// 获得所有函数
		PyObject *pModuleTest = PyImport_ImportModule("testModule"); // new reference
																	 // evaluate dictionary of testModule
		PyObject *const pDict = PyModule_GetDict(pModuleTest); // borrowed
															   // find functions
		std::cout << "Functions of testModule:\n";
		PyObject *pKey = nullptr, *pValue = nullptr;
		for (Py_ssize_t i = 0; PyDict_Next(pDict, &i, &pKey, &pValue);) {
			const char *key = PyUnicode_AsUTF8(pKey);
			if (PyFunction_Check(pValue)) {
				std::cout << "function '" << key << "'\n";
			}
		}
	}

	GE_PyObject* Call(const char * str, const std::initializer_list<PyObject*>& list)
	{
		if (obj == nullptr)
			print("没有初始化py对象");
			return nullptr;

		// 调用函数
		auto args = std::make_shared<GE_PyObject>(PyTuple_New(list.size));
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
			print("没有这个函数");
			return nullptr;
		}
		return result;
	}

	PyObject* GetPointer()
	{
		return obj;
	}
	
private:
	PyObject* obj;
	std::map<const char*, GE_PyFunction*> m_funclist;
	~GE_PyObject()
	{
		Py_XDECREF(obj);
	}
};

class GE_PyFunction
{
public:
	GE_PyFunction(PyObject* args) : obj(args)
	{
		Py_XINCREF(args);
	}

	GE_PyObject* Call(GE_PyObject* args)
	{
		PyObject* pyResult_NewRef = PyEval_CallObject(obj, args->GetPointer());
		if (NULL == pyResult_NewRef)
		{
			PyErr_Print();
		}
		return new GE_PyObject(pyResult_NewRef);
	}

private:
	PyObject* obj;

	~GE_PyFunction()
	{
		Py_XDECREF(obj);
	}
};