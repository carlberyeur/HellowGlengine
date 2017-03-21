#pragma once
#include "Component.h"

class CSpriteInstance;

class CSpriteComponent : public IComponent
{
public:
	CSpriteComponent();
	CSpriteComponent(const CSpriteComponent& aCopy);
	~CSpriteComponent();

	CSpriteComponent& operator=(const CSpriteComponent& aCopy);
	IComponent* Copy() override;

	void Render();

private:
	CU::UniquePointer<CSpriteInstance> mySpriteInstance;
};
