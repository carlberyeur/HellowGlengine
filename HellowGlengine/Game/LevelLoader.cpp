#include "stdafx.h"
#include "LevelLoader.h"
#include "../CommonUtilities/JsonValue.h"

CLevelLoader* CLevelLoader::ourInstance = nullptr;

CLevelLoader::CLevelLoader(CLevel& aLevel, CScene& aScene)
	: myLevel(aLevel)
	, myScene(aScene)
{
	assert(ourInstance == nullptr);
	ourInstance = this;
}

CLevelLoader::~CLevelLoader()
{
	assert(ourInstance == this);
	ourInstance = nullptr;
}

//CLevelLoader* CLevelLoader::GetInstance()
//{
//	return ourInstance;
//}

bool CLevelLoader::LoadLevel(const std::string& aJsonPath)
{
	CU::CJsonValue root(aJsonPath);
	CU::CJsonValue data = root.at("layers").at(0).at("data");

	const char* rawData = data.GetString().c_str();
	unsigned int* gids = new unsigned int[data.GetString().size()];
	for (int i = 0; i < data.GetString().size(); i++)
	{
		gids[i] = (unsigned int)data.GetString()[i];
	}

	delete[] gids;
	
	return false;
}

void CLevelLoader::RegisterLoadFunction(const std::string& aFunctionName, const LoadObjectFunction aLoadFunction)
{
	if (myLoadFunctions.find(aFunctionName) != myLoadFunctions.end())
	{
		DL_MESSAGE_BOX("Load function with name %s already exists in level loader", aFunctionName.c_str());
		return;
	}

	myLoadFunctions[aFunctionName] = aLoadFunction;
}
