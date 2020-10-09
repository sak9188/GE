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
		return nullptr;
	}

	GE_PyObject* GetModule(const char * str)
	{
		if (!Py_IsInitialized())
		{
			std::cout << "Python û�г�ʼ��" << std::endl;
			return nullptr;
		}
		print("����ģ�飺");
		print(str);
		return new GE_PyObject(PyImport_ImportModule(str));
	}

	~GE_Python()
	{
		Py_Finalize();
	}

private:
	GE_SINGLETON(GE_Python)

	void Init()
	{
		std::wstringstream ss;
#ifdef _DEBUG
		ss << "..\\python\\DLLs\\;"
			<< "..\\python\\Lib\\python38.zip;"
			<< "..\\python\\pkgs\\;"
			<< ".\\";
#else
		ss << "..\\..\\python\\DLLs\\;"
			<< "..\\..\\python\\Lib\\python38.zip;"
			<< "..\\..\\python\\pkgs\\;"
			<< ".\\";
#endif
		Py_SetPath(ss.str().c_str());
		Py_Initialize();
		print("��ʼ�����");
	}


};

GE_SET_SINGLETON(GE_Python)