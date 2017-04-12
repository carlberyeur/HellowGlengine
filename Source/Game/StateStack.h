#pragma once

class IState;
enum class eStateStatus : short;

class CStateStack
{
public:
	CStateStack();
	~CStateStack();

	void Push(IState* aState);
	void Pop();

	bool Update(const CU::Time aDeltaTime);
	void Render();

private:
	eStateStatus UpdateAtIndex(const int aIndex, const CU::Time aDeltaTime);
	void RenderAtIndex(const int aIndex);

	CU::GrowingArray<IState*, int> myStates;
};
