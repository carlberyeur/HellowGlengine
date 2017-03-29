#pragma once
#include "Component.h"

class CPhysicsComponent : public IComponent
{
public:
	CPhysicsComponent();
	CPhysicsComponent(const CPhysicsComponent& aCopy);
	~CPhysicsComponent();

	CPhysicsComponent& operator=(const CPhysicsComponent& aCopy);
	
	virtual void Update(const CU::Time aDeltaTime) override;
	virtual void Recieve(const SComponentMessage& aMessage) override;
	virtual bool Answer(SComponentMessage& aMessage) override;
	virtual IComponent* Copy() override;

	virtual bool Load(CU::ISerializer& aSerializer) override;
	virtual bool Save(CU::ISerializer& aSerializer) override;

private:
	virtual void Init() override;

};

