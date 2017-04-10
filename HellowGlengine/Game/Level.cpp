#include "stdafx.h"
#include "Level.h"
#include "GameObject.h"

CLevel::CLevel()
	: myGameObjects(32)
	, myFreeIDs(16)
{
}

CLevel::~CLevel()
{
}

#include "SpriteComponent.h"
void CLevel::Init()
{
	myGameObjects.Add();

	CSpriteComponent* spriteComponent = new CSpriteComponent("Textures/square.tga");
	myGameObjects.GetLast().AddComponent(*spriteComponent);

	myGameObjects.GetLast().SetPosition(0.2f, 0.23f);
	myGameObjects.GetLast().Init();
}

void CLevel::Update(const CU::Time aDeltaTime)
{
	for (CGameObject& gameObject : myGameObjects)
	{
		gameObject.Update(aDeltaTime);
	}
}

int CLevel::AddGameObject()
{
	if (!myFreeIDs.Empty())
	{
		return myFreeIDs.Pop();
	}

	int id = myGameObjects.Size();
	myGameObjects.Add(id);
	return id;
}

//int CLevel::AddGameObject(CGameObject&& aGameObject)
//{
//	int id = myGameObjects.Size();
//	if (!myFreeIDs.Empty())
//	{
//		id = myFreeIDs.Pop();
//		myGameObjects[id] = std::move(aGameObject);
//		return id;
//	}
//
//	myGameObjects.Add(std::move(aGameObject));
//	return id;
//}

void CLevel::DestroyGameObject(const int aID)
{
	myGameObjects[aID] = CGameObject();
	myFreeIDs.Add(aID);
}

CGameObject* CLevel::GetGameObject(const int aID)
{
	return myGameObjects.TryGet(aID);
}
