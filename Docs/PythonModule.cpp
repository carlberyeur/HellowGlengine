#include "stdafx.h"
#include "PythonModule.h"

#define DIS (*this)

CPythonModule::CPythonModule()
	: myModuleObject(nullptr)
{
}

CPythonModule::CPythonModule(const CPythonModule& aCopy)
{
	DIS = aCopy;
}

CPythonModule::CPythonModule(CPythonModule&& aTemporary)
{
	DIS = std::move(aTemporary);
}

CPythonModule::~CPythonModule()
{
	Py_XDECREF(myModuleObject);
}

void CPythonModule::Init(PyObject* aModuleObject)
{
	Py_XDECREF(myModuleObject);
	myModuleObject = aModuleObject;
}

CPythonModule CPythonModule::operator=(const CPythonModule& aCopy)
{
	Py_XDECREF(myModuleObject);
	myModuleObject = aCopy.myModuleObject;
	Py_XINCREF(myModuleObject);

	return DIS;
}

CPythonModule CPythonModule::operator=(CPythonModule&& aTemporary)
{
	Py_XDECREF(myModuleObject);
	myModuleObject = aTemporary.myModuleObject;
	aTemporary.myModuleObject = nullptr;

	return DIS;
}

bool CPythonModule::HasAttribute(const std::string& aAttributeName) const
{
	return false;
}

bool CPythonModule::GetFunction(const std::string& aFunctionName, CPythonFunction& aFunctionOut)
{
	PyObject* function = PyObject_GetAttrString(myModuleObject, aFunctionName.c_str());
	if (function && PyFunction_Check(function))
	{
		//aFunctionOut.set(function);
		return true;
	}

	return false;
}
