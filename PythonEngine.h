#ifndef GE_PYTHON_H
#define GE_PYTHON_H

#include <memory>

#include <sstream>
#include <iostream>

#include <Python.h>
#include <datetime.h>

#include "GE.h"
#include "GEPyObject.h"
#include "Singleton.h"
#include "IO.h"

namespace GE
{
	void InitPyDateTime();

	PyObject* PyObjFromDatetime(GE::Uint32 y, GE::Uint32 m, GE::Uint32 d, GE::Uint32 H, GE::Uint32 M, GE::Uint32 S);

	bool PyDateTimeCheck(PyObject* pyObj);

	class PythonEngine
		: public GE::Singleton<PythonEngine>
	{
		GE_BAN_COPY(PythonEngine)
	public:
		PyObject* RegFuncVoid(PyObject* self, PyObject* arg)
		{
			return nullptr;
		}

		GE::GEPyMoudule* GetModule(const char * str)
		{
			if (!Py_IsInitialized())
			{
				std::cout << "Python 没有初始化" << std::endl;
				return nullptr;
			}
			GE_Info << "载入模块：" << str << "\n";
			return new GE::GEPyMoudule(PyImport_ImportModule(str));
		}

		PythonEngine()
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
			GE::InitPyDateTime();
			GE_Info << "初始化完成\n";
		}

		~PythonEngine()
		{
			Py_Finalize();
		}
	};
}
#endif