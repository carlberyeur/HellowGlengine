#include "stdafx.h"
#include "PlayState.h"

#include "Level.h"
#include "Scene.h"

#include "LevelLoader.h"

CPlayState::CPlayState(CStateStack& aStateStack)
	: IState(aStateStack)
{
}

CPlayState::~CPlayState()
{
}

void CPlayState::Init()
{
	myLevel = new CLevel();
	if (!myLevel)
	{
		return;
	}

	myScene = new CScene();
	if (!myScene)
	{
		return;
	}

	CLevelLoader levelLoader(*myLevel, *myScene);
	levelLoader.LoadLevel("Data/Levels/sewers.json");

	myLevel->Init("");
	myScene->Init();
}

eStateStatus CPlayState::Update(const CU::Time& aDeltaTime)
{
	myLevel->Update(aDeltaTime);
	myScene->Update(aDeltaTime);

	return eStateStatus::eKeep;
}

void CPlayState::Render()
{
	myScene->Render();
}

void CPlayState::OnEnter()
{
}

void CPlayState::OnExit()
{
}
