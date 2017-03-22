#pragma once
#include "State.h"

class CScene;
class CLevel;

class CPlayState : public IState
{
public:
	CPlayState(CStateStack& aStateStack);
	~CPlayState();

	void Init() override;
	eStateStatus Update(const CU::Time& aDeltaTime) override;
	void Render() override;
	void OnEnter() override;
	void OnExit() override;

private:
	CU::UniquePointer<CScene> myScene;
	CU::UniquePointer<CLevel> myLevel;
};
