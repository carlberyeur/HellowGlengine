#pragma once

namespace CU
{
	class CJsonValue;
}

class CLevel;
class CScene;
class CLevelLoader;

using LoadObjectFunction = int(*)(CLevelLoader&, CU::CJsonValue);

class CLevelLoader
{
public:
	CLevelLoader(CLevel& aLevel, CScene& aScene);
	CLevelLoader(const CLevelLoader&) = delete;
	~CLevelLoader();

	//static CLevelLoader* GetInstance();

	bool LoadLevel(const std::string& aJsonPath);
	void RegisterLoadFunction(const std::string& aFunctionName, const LoadObjectFunction aLoadFunction);

	inline CLevel& GetLevel();
	inline CScene& GetScene();

private:
	std::map<std::string, LoadObjectFunction> myLoadFunctions;
	CLevel& myLevel;
	CScene& myScene;

	static CLevelLoader* ourInstance;
};

inline CLevel& CLevelLoader::GetLevel()
{
	return myLevel;
}

inline CScene& CLevelLoader::GetScene()
{
	return myScene;
}

#define GET_LEVEL_LOADER(VARIABLE_NAME, DEFAULT_RETURN_VALUE)				\
CLevelLoader* VARIABLE_NAME##_secretPointer = CLevelLoader::GetInstance();	\
if (!VARIABLE_NAME##_secretPointer) return DEFAULT_RETURN_VALUE;			\
CLevelLoader& VARIABLE_NAME = *VARIABLE_NAME##_secretPointer; VARIABLE_NAME
