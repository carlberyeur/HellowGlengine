#include "stdafx.h"
#include "StateStack.h"
#include "State.h"

CStateStack::CStateStack()
	: myStates(8u)
{
}

CStateStack::~CStateStack()
{
	while (!myStates.Empty())
	{
		delete myStates.Pop();
	}
}

void CStateStack::Push(IState* aState)
{
	assert(aState);
	if (!myStates.Empty())
	{
		myStates.GetLast()->OnExit();
	}

	aState->Init();
	aState->OnEnter();

	myStates.Add(aState);
}

void CStateStack::Pop()
{
	if (!myStates.Empty())
	{
		myStates.GetLast()->OnExit();
		delete myStates.Pop();
	}

	if (!myStates.Empty())
	{
		myStates.GetLast()->OnEnter();
	}
}

bool CStateStack::Update(const CU::Time aDeltaTime)
{
	if (UpdateAtIndex(myStates.Size() - 1, aDeltaTime) == eStateStatus::ePop)
	{
		Pop();
	}

	return !myStates.Empty();
}

void CStateStack::Render()
{
	RenderAtIndex(myStates.Size() - 1);
}

eStateStatus CStateStack::UpdateAtIndex(const int aIndex, const CU::Time aDeltaTime)
{
	if (aIndex < 0) return eStateStatus::eKeep;

	if (myStates[aIndex]->LetThroughUpdate())
	{
		(void)UpdateAtIndex(aIndex - 1, aDeltaTime);
	}

	return myStates[aIndex]->Update(aDeltaTime);
}

void CStateStack::RenderAtIndex(const int aIndex)
{
	if (aIndex < 0) return;

	if (myStates[aIndex]->LetThroughRender())
	{
		(void)RenderAtIndex(aIndex - 1);
	}

	myStates[aIndex]->Render();
}
