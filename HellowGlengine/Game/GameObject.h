#pragma once

namespace CU
{
	class ISerializer;
}

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
	//bool AskComponents(SComponentMessage& aMessage);

	void Move(const CU::Vector2f aDisplacement);
	void SetPosition(const CU::Vector2f aPosition);
	void SetPosition(const float aPositionX, const float aPositionY);
	CU::Vector2f GetPosition() const;

	bool Serialize(CU::ISerializer& aSerializer);

private:
	CU::GrowingArray<IComponent*> myComponents;
	CU::Vector2f myPosition;
	float myRotation;
};
