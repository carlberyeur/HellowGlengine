#include "stdafx.h"
#include "Level.h"
#include "GameObject.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
}

void CLevel::Init(const std::string& /*aLevelPath*/)
{
	myGameObjects.Add();
}

void CLevel::Update(const CU::Time& /*aDeltaTime*/)
{
}
