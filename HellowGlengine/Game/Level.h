#pragma once

class CGameObject;

class CLevel
{
public:
	CLevel();
	~CLevel();

	void Init();
	void Update(const CU::Time& aDeltaTime);

	int AddGameObject();
	int AddGameObject(CGameObject&& aGameObject);
	void DestroyGameObject(const int aID);
	CGameObject* GetGameObject(const int aID);

private:
	CU::GrowingArray<CGameObject> myGameObjects;
	CU::GrowingArray<int> myFreeIDs;
};
