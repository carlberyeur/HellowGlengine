#pragma once

#ifdef _DEBUG
#undef _DEBUG
#include "../Dependencies/python34/include/Python.h"
#define _DEBUG
#else // !_DEBUG
#include "../Dependencies/python34/include/Python.h"
#endif // _DEBUG

#define TO_STRING(NAME) #NAME
#define CONCAT_VARS(FIRST, SECOND) FIRST##SECOND

#define DEFINE_PYTHON_MODULE_INIT(MODULE_NAME)			\
PyMODINIT_FUNC CONCAT_VARS(PyInit_, MODULE_NAME)() {	\
	return PyModule_Create(&MODULE_NAME);				\
}


#define DEFINE_PYTHON_FUNCTION(FUNCTION_NAME, FUNCTION_PTR)	\
static PyMethodDef FUNCTION_NAME = {						\
	TO_STRING(FUNCTION_PTR),								\
	FUNCTION_PTR,											\
	METH_VARARGS,											\
	nullptr													\
};


#define DEFINE_PYTHON_MODULE(MODULE_NAME, ...)								\
static PyMethodDef CONCAT_VARS(MODULE_NAME, _methods)[] = { __VA_ARGS__ };	\
static PyModuleDef MODULE_NAME = {											\
	PyModuleDef_HEAD_INIT,													\
	TO_STRING(MODULE_NAME), NULL, -1, CONCAT_VARS(MODULE_NAME, _methods),	\
	NULL, NULL, NULL, NULL													\
};																			\
DEFINE_PYTHON_MODULE_INIT(MODULE_NAME)


#define APPEND_MODULE_INIT_TAB(MODULE_NAME)	PyImport_AppendInittab(TO_STRING(MODULE_NAME), &CONCAT_VARS(PyInit_, MODULE_NAME))
