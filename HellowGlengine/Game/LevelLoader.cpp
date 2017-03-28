#include "stdafx.h"
#include "LevelLoader.h"
#include "../CommonUtilities/JsonValue.h"

CLevelLoader::CLevelLoader(CLevel& aLevel, CScene& aScene)
	: myLevel(aLevel)
	, myScene(aScene)
{
}

CLevelLoader::~CLevelLoader()
{
}

bool CLevelLoader::LoadLevel(const std::string& aJsonPath)
{
	CU::CJsonValue root(aJsonPath);
	if (CallLoadFunction("root", root) != -1)
	{
		return true;
	}
	
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

int CLevelLoader::CallLoadFunction(const std::string& aJsonObjectKey, const CU::CJsonValue& aJsonObjectValue)
{
	auto function = myLoadFunctions.find(aJsonObjectKey);
	if (function != myLoadFunctions.end())
	{
		return function->second(*this, aJsonObjectValue);
	}

	return -1;
}
