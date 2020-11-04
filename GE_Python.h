#ifndef GE_PYTHON_H
#define GE_PYTHON_H

#include <mutex>
#include <memory>
#include <Python.h>
#include <datetime.h>

#include <sstream>
#include <iostream>

#include "GE.h"
#include "GE_PyObject.h"

class GE_Python
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

	~GE_Python()
	{
		Py_Finalize();
	}


private:
	GE_SINGLETON(GE_Python)

	void Init()
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
		print("初始化完成");
	}


};
GE_SET_SINGLETON(GE_Python)
#endif

namespace GE
{
	PyObject* PyObjFromDatetime(GE::Uint32 y, GE::Uint32 m, GE::Uint32 d, GE::Uint32 H, GE::Uint32 M, GE::Uint32 S)
	{
		return (PyObject*)PyDateTime_FromDateAndTime(static_cast<int>(y), static_cast<int>(m), static_cast<int>(d),
			static_cast<int>(H), static_cast<int>(M), static_cast<int>(S), 0);
	}

	bool PyDateTimeCheck(PyObject* pyObj)
	{
		return PyDateTime_CheckExact(pyObj);
	}
}