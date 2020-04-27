#pragma once
#include <mutex>
#include <memory>
#include <Python.h>

#include <sstream>
#include <iostream>

#include "GE.h"
#include "GE_PyObject.h"

class GE_Python
{
public:
	PyObject* RegFuncVoid(PyObject* self, PyObject* arg)
	{
		Py_RETURN_NONE;
	}

private:
	SINGLETON(GE_Python)

	void Init()
	{
		std::wstringstream ss;
		ss << "..\\..\\python\\DLLs\\;"
			<< "..\\..\\python\\Lib\\python38.zip;"
			<< "..\\..\\python\\pkgs\\;";
		Py_SetPath(ss.str().c_str());
		Py_Initialize();
	}

	GE_PyObject* GetModule(const char * str)
	{
		if (!Py_IsInitialized)
		{
			std::cout << "Python 没有初始化" << std::endl;
			return nullptr;
		}

		return new GE_PyObject(PyImport_ImportModule(str));
	}
};

SET_SINGLETON(GE_Python)