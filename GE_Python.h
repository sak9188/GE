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

namespace GE
{
	void InitPyDateTime();

	PyObject* PyObjFromDatetime(GE::Uint32 y, GE::Uint32 m, GE::Uint32 d, GE::Uint32 H, GE::Uint32 M, GE::Uint32 S);

	bool PyDateTimeCheck(PyObject* pyObj);
}


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
			std::cout << "Python û�г�ʼ��" << std::endl;
			return nullptr;
		}
		print("����ģ�飺");
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
		GE::InitPyDateTime();
		print("��ʼ�����");
	}

	~GE_Python()
	{
		Py_Finalize();
	}
};
#endif