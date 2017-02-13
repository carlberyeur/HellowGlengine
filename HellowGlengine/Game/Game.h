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
	void Update(const CU::Time& aDeltaTime);
	void Render();

private:
	CStateStack* myStateStack;
};
