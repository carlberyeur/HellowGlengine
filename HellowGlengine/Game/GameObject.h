#pragma once

struct SComponentMessage;
class IComponent;

class CGameObject final
{
public:
	CGameObject();
	CGameObject(const CGameObject& aOther);
	CGameObject(CGameObject&& aOther);
	~CGameObject();

	CGameObject& operator=(const CGameObject& aOther);
	CGameObject& operator=(CGameObject&& aOther);

	void Init();
	void AddComponent(IComponent& aComponent);
	void NotifyComponents(const SComponentMessage& aMessage);

private:
	CU::GrowingArray<IComponent*> myComponents;
};
