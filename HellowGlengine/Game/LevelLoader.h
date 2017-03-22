#pragma once

class CLevel;
class CScene;

class CLevelLoader
{
public:
	CLevelLoader(CLevel& aLevel, CScene& aScene);
	~CLevelLoader();

	static CLevelLoader* GetInstance();

private:
	CLevel& myLevel;
	CScene& myScene;

	static CLevelLoader* ourInstance;
};

#define GET_LEVEL_LOADER(VARIABLE_NAME)		\
VARIABLE_NAME;
