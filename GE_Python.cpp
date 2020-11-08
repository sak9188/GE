#include "GE_Python.h"

void GE::InitPyDateTime()
{
	PyDateTime_IMPORT;
}

PyObject* GE::PyObjFromDatetime(GE::Uint32 y, GE::Uint32 m, GE::Uint32 d, GE::Uint32 H, GE::Uint32 M, GE::Uint32 S)
{
	return (PyObject*)PyDateTime_FromDateAndTime(static_cast<int>(y), static_cast<int>(m), static_cast<int>(d),
		static_cast<int>(H), static_cast<int>(M), static_cast<int>(S), 0);
}

bool GE::PyDateTimeCheck(PyObject* pyObj)
{
	return PyDateTime_CheckExact(pyObj);
}