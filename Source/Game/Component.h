#pragma once

namespace CU
{
	class ISerializer;
	class Time;
}

struct SComponentMessage;

class IComponent
{
public:
	friend class CGameObject;
	friend class CComponentManager;

	IComponent();
	virtual ~IComponent();

	virtual void Update(const CU::Time aDeltaTime);
	virtual void Recieve(const SComponentMessage& aMessage);
	virtual bool Answer(SComponentMessage& aMessage);
	virtual IComponent* Copy() = 0;

	virtual bool Load(CU::ISerializer& aSerializer) = 0;
	virtual bool Save(CU::ISerializer& aSerializer) = 0;

	CGameObject* GetParent() /*const*/;
	int GetParentID();
	int GetID() const;

private:
	virtual void Init();

	CGameObject* myParent;
	int myID;
};

