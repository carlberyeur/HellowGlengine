#pragma once

namespace CU
{
	class ISerializer;
	class Time;
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
	bool AskComponents(SComponentMessage& aMessage);

	void Update(const CU::Time aDeltaTime);

	void Move(const CU::Vector2f aDisplacement);
	void Rotate(const float aRotation);
	void SetPosition(const CU::Vector2f aPosition);
	void SetPosition(const float aPositionX, const float aPositionY);
	void SetRotation(const float aRotation);
	CU::Vector2f GetPosition() const;
	float GetRotation() const;

	bool Save();
	bool Load();

private:
	CU::GrowingArray<IComponent*> myComponents;
	CU::Vector2f myPosition;
	float myRotation;
};
