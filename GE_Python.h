#ifndef GE_PYTHON_H
#define GE_PYTHON_H

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
		print("��ʼ�����");
	}


};
GE_SET_SINGLETON(GE_Python)
#endif