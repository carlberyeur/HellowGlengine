#pragma once

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

private:
	virtual void Init();

	CGameObject* myParent;
};

