#pragma once

typedef struct _object PyObject;

class CPythonModule;

class CPythonWrapper
{
public:
	CPythonWrapper(wchar_t* aArgv0, const std::function<void()>& aInitModulesFunction);
	~CPythonWrapper();

	void AddSearchPath(const std::string& aPathToAppendFrom, const std::string& aPathToAppend);
	bool ImportModule(const std::string& aModuleName, CPythonModule& aModuleOut);

	static const std::string& GetLastError();

private:
	bool HasError();

	static std::string ourLastError;
};

