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
	//wendy::CSpriteInstance sprite;
	//sprite.SetTextureRect({ { 0.75f, 0.75f }, {1.f, 1.f} });
	//sprite.SetPosition(0.25f, 0.25f);
	//sprite.Init("Textures/sewer_tileset.tga");
	//mySpriteInstances.Add(std::move(sprite));


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
