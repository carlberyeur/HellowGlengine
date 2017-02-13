#pragma once

class CStateStack;

enum class eStateStatus : short
{
	ePop,
	eKeep
};

class IState
{
public:
	IState(CStateStack& aStateStack, const bool aLetThroughRender = false, const bool aLetThroughUpdate = false);
	IState(const IState& aCopy);
	virtual ~IState();

	IState& operator=(const IState& aCopy);

	virtual void Init() = 0;
	virtual eStateStatus Update(const CU::Time& aDeltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	void SetStatus(const eStateStatus aStatus);

	bool LetThroughRender() const;
	bool LetThroughUpdate() const;

private:
	CStateStack& myStateStack;
	eStateStatus myStatus;

	bool myLetThroughRender;
	bool myLetThroughUpdate;
};
