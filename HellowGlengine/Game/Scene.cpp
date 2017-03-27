#include "stdafx.h"
#include "Scene.h"
#include "../Engine/SpriteInstance.h"

CScene::CScene()
	: mySpriteInstances(8)
{
}

CScene::~CScene()
{
}

bool CScene::Init()
{
	mySpriteInstances.Optimize();
	return true;
}

void CScene::Update(const CU::Time& /*aDeltaTime*/)
{
}

void CScene::Render()
{
	for (wendy::CSpriteInstance& spriteInstance : mySpriteInstances)
	{
		spriteInstance.Render();
		break;
	}
}

int CScene::AddSpriteInstance(wendy::CSpriteInstance&& aSpriteInstance)
{
	int id = mySpriteInstances.Size();
	mySpriteInstances.Add(std::move(aSpriteInstance));
	return id;
}

void CScene::DestroySpriteInstance(const int aID)
{
	if (mySpriteInstances.HasIndex(aID))
	{
		mySpriteInstances[aID] = wendy::CSpriteInstance();
	}
}

wendy::CSpriteInstance* CScene::GetSpriteInstance(const int aID)
{
	return mySpriteInstances.TryGet(aID);
}
