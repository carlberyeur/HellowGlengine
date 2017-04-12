#pragma once

typedef struct _object PyObject;

class CPythonFunction;

class CPythonModule
{
public:
	friend class CPythonWrapper;

	CPythonModule();
	CPythonModule(const CPythonModule& aCopy);
	CPythonModule(CPythonModule&& aTemporary);
	~CPythonModule();

	CPythonModule operator=(const CPythonModule& aCopy);
	CPythonModule operator=(CPythonModule&& aTemporary);

	bool HasAttribute(const std::string& aAttributeName) const;
	bool GetFunction(const std::string& aFunctionName, CPythonFunction& aFunctionOut);

private:
	void Init(PyObject* aModuleObject);

	PyObject* myModuleObject;
};
