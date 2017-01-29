#pragma once

namespace CU
{
	class Time;
}

class CGameWorld;

class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	void Update(const CU::Time aDeltaTime);
	void Render();

private:
	CGameWorld* myGameWorld;
};
