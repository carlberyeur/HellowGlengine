#pragma once
#include "Component.h"

class CSpriteComponent : public IComponent
{
public:
	CSpriteComponent();
	CSpriteComponent(const CSpriteComponent& aCopy);
	~CSpriteComponent();

	CSpriteComponent& operator=(const CSpriteComponent& aCopy);

	IComponent* Copy() override;
};
