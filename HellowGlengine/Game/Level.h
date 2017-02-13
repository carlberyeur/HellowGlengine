#pragma once

class CGameObject;

class CLevel
{
public:
	CLevel();
	~CLevel();

	void Init(const std::string& aLevelPath);
	void Update(const CU::Time& aDeltaTime);

private:
	CU::GrowingArray<CGameObject> myGameObjects;
};
