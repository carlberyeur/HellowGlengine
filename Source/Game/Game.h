#pragma once

namespace CU
{
	class Time;
}

class CStateStack;

class CGame
{
public:
	CGame();
	~CGame();

	void Init();
	bool Update(const CU::Time aDeltaTime);
	void Render();

private:
	CU::UniquePointer<CStateStack> myStateStack;
};
