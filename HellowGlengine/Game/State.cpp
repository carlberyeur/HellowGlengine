#include "stdafx.h"
#include "State.h"


IState::IState(CStateStack& aStateStack, const bool aLetThroughRender, const bool aLetThroughUpdate)
	: myStateStack(aStateStack)
	, myStatus(eStateStatus::eKeep)
	, myLetThroughRender(aLetThroughRender)
	, myLetThroughUpdate(aLetThroughUpdate)
{
}

IState::IState(const IState& aCopy)
	: myStateStack(aCopy.myStateStack)
	, myStatus(aCopy.myStatus)
	, myLetThroughRender(aCopy.myLetThroughRender)
	, myLetThroughUpdate(aCopy.myLetThroughUpdate)
{
}

IState::~IState()
{
}

IState& IState::operator=(const IState& aCopy)
{
	myStatus = aCopy.myStatus;
	myLetThroughRender = aCopy.myLetThroughRender;
	myLetThroughUpdate = aCopy.myLetThroughUpdate;

	return *this;
}

void IState::SetStatus(const eStateStatus aStatus)
{
	myStatus = aStatus;
}

bool IState::LetThroughRender() const
{
	return myLetThroughRender;
}

bool IState::LetThroughUpdate() const
{
	return myLetThroughUpdate;
}
