#ifndef GE_PYTHON_H
#define GE_PYTHON_H

#include <memory>

#include <sstream>
#include <iostream>

#include <Python.h>
#include <datetime.h>

#include "GE.h"
#include "GE_PyObject.h"
#include "GE_Singleton.h"

class GE_Python
	: public GE_Singleton<GE_Python>
{
public:
	PyObject* RegFuncVoid(PyObject* self, PyObject* arg)
	{
		return nullptr;
	}

	GE_PyMoudule* GetModule(const char * str)
	{
		if (!Py_IsInitialized())
		{
			std::cout << "Python 没有初始化" << std::endl;
			return nullptr;
		}
		print("载入模块：");
		print(str);
		return new GE_PyMoudule(PyImport_ImportModule(str));
	}

	GE_Python()
	{
		if (Py_IsInitialized())
		{
			return;
		}
		std::stringstream ss;
#ifdef _DEBUG
		ss << "..\\python\\DLLs\\;"
			<< "..\\python\\Lib\\python27.zip;"
			<< "..\\python\\pkgs\\;"
			<< ".\\";
#else
		ss << "..\\..\\python\\DLLs\\;"
			<< "..\\..\\python\\Lib\\python27.zip;"
			<< "..\\..\\python\\pkgs\\;"
			<< ".\\";
#endif
		Py_Initialize();
		PySys_SetPath(const_cast<char*>(ss.str().c_str()));
		// 使用了datetime模块，故要在此初始化
		PyDateTime_IMPORT;
		print("初始化完成");
	}

	~GE_Python()
	{
		Py_Finalize();
	}
};

namespace GE
{
	PyObject* PyObjFromDatetime(GE::Uint32 y, GE::Uint32 m, GE::Uint32 d, GE::Uint32 H, GE::Uint32 M, GE::Uint32 S);

	bool PyDateTimeCheck(PyObject* pyObj);
}

#endif