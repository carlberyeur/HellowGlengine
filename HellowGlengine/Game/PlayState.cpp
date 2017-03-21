#include "stdafx.h"
#include "PlayState.h"

#include "Level.h"
#include "Scene.h"

CPlayState::CPlayState(CStateStack& aStateStack)
	: IState(aStateStack)
{
}

CPlayState::~CPlayState()
{
}

void CPlayState::Init()
{
	myLevel->Init("");
}

eStateStatus CPlayState::Update(const CU::Time& aDeltaTime)
{
	if (myLevel)
	{
		myLevel->Update(aDeltaTime);
	}
	
	if (myScene)
	{
		myScene->Update(aDeltaTime);
	}

	return eStateStatus::eKeep;
}

void CPlayState::Render()
{
	if (myScene)
	{
		myScene->Render();
	}
}

void CPlayState::OnEnter()
{
}

void CPlayState::OnExit()
{
}
