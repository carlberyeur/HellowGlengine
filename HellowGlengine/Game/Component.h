#pragma once

struct SComponentMessage;

class IComponent
{
public:
	friend class CGameObject;

	IComponent();
	virtual ~IComponent();

	virtual void Init();
	virtual void Recieve(const SComponentMessage& aMessage);

	virtual IComponent* Copy() = 0;

private:
	CGameObject* myParent;
};

