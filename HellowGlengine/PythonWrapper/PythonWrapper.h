#pragma once

typedef struct _object PyObject;
using VoidFunction = void(*)(void);

class CPythonModule;

class CPythonWrapper
{
public:
	CPythonWrapper(wchar_t* aArgv0, const VoidFunction& aInitModulesFunction);
	~CPythonWrapper();

	void AddSearchPath(const std::string& aPathToAppendFrom, const std::string& aPathToAppend);
	bool ImportModule(const std::string& aModuleName, CPythonModule& aModuleOut);

	static const std::string& GetLastError();

	static CPythonWrapper* GetInstance();
	static bool IsCreated();

private:
	bool HasError();

	static std::string ourLastError;
	static CPythonWrapper* ourInstance;
};
