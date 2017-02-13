#pragma once

class CScene
{
public:
	CScene();
	~CScene();

	void Update(const CU::Time& aDeltaTime);
	void Render();
};
