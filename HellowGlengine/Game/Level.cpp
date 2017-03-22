#include "stdafx.h"
#include "Level.h"
#include "GameObject.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	BREAK_POINT_HERE;
}

#include "SpriteComponent.h"
void CLevel::Init(const std::string& /*aLevelPath*/)
{
	myGameObjects.Init(32);
	myGameObjects.Add();

	CSpriteComponent* spriteComponent = new CSpriteComponent("Textures/square.tga");
	myGameObjects.GetLast().AddComponent(*spriteComponent);

	myGameObjects.GetLast().SetPosition(0.2f, 0.23f);
	myGameObjects.GetLast().Init();
}

void CLevel::Update(const CU::Time& /*aDeltaTime*/)
{
}
