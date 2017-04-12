#pragma once

namespace wendy
{
	class CSpriteInstance;
}

class CScene
{
public:
	CScene();
	~CScene();

	bool Init();
	void Update(const CU::Time aDeltaTime);
	void Render();

	int AddSpriteInstance(wendy::CSpriteInstance&& aSpriteInstance);
	void DestroySpriteInstance(const int aID);
	wendy::CSpriteInstance* GetSpriteInstance(const int aID);

private:
	CU::GrowingArray<wendy::CSpriteInstance, int> mySpriteInstances;
};
