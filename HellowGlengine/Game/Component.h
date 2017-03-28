#pragma once

namespace CU
{
	class ISerializer;
}

struct SComponentMessage;

class IComponent
{
public:
	friend class CGameObject;

	IComponent();
	virtual ~IComponent();

	virtual void Recieve(const SComponentMessage& aMessage);
	virtual IComponent* Copy() = 0;

	CGameObject* GetParent();

	virtual bool Serialize(CU::ISerializer& aSerializer) = 0;

private:
	virtual void Init();

	CGameObject* myParent;
};

