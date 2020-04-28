#pragma once
#include <Python.h>
#include <map>
#include <memory>

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
	BAN_COPY(GE_PyFunction)

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
			print("构造GE_PyObject对象失败");
		}
		if (!NewRef)
		{
			Py_XINCREF(obj); // borrowed
			// 增加引用
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

	bool GetAllFunctions()
	{
		if (obj == nullptr)
		{
			print("没有初始化py对象");
			return false;
		}
		print("尝试载入所有函数");
		// 获得所有函数
		PyObject *const pDict = PyModule_GetDict(obj); // borrowed
		PyObject *pKey = nullptr, *pValue = nullptr;
		for (Py_ssize_t i = 0; PyDict_Next(pDict, &i, &pKey, &pValue);) //borrwed
		{
			const char *key = PyUnicode_AsUTF8(pKey);
			if (PyFunction_Check(pValue)) {
				std::cout << "function '" << key << "'\n";
				m_funclist.emplace(std::make_pair(key, new GE_PyFunction(pValue)));
			}
		}
	}

	GE_PyObject* Call(const char * str, const std::initializer_list<PyObject*>& list)
	{
		if (obj == nullptr)
			print("没有初始化py对象");
			return nullptr;
		// 调用函数
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
			print("没有这个函数");
			print(str);
			return nullptr;
		}
		return result;
	}

	PyObject* GetPointer()
	{
		return obj;
	}

	~GE_PyObject()
	{
		Py_XDECREF(obj);
	}

private:
	BAN_COPY(GE_PyObject)

	PyObject* obj;
	std::map<const char*, GE_PyFunction*> m_funclist;
};



GE_PyFunction::GE_PyFunction(PyObject* args, bool NewRef) : obj(args)
{
	if (obj == NULL)
	{
		obj = nullptr;
		PyErr_Print();
		print("构造GE_PyObject对象失败");
	}

	if (!NewRef)
	{
		Py_XINCREF(obj); // borrowed
						 // 增加引用
	}
}

GE_PyObject* GE_PyFunction::Call(GE_PyObject* args)
{
	PyObject* pyResult_NewRef = PyEval_CallObject(obj, args->GetPointer());
	if (NULL == pyResult_NewRef)
	{
		PyErr_Print();
	}
	return new GE_PyObject(pyResult_NewRef);
}