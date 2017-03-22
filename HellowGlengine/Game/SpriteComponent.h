#pragma once
#include "Component.h"

namespace wendy
{
	class CSpriteInstance;
}

class CSpriteComponent : public IComponent
{
public:
	CSpriteComponent();
	CSpriteComponent(const std::string& aSpritePath);
	CSpriteComponent(const CSpriteComponent& aCopy);
	~CSpriteComponent();

	CSpriteComponent& operator=(const CSpriteComponent& aCopy);
	IComponent* Copy() override;
	void Init() override;

	void Render();

private:
	CU::UniquePointer<wendy::CSpriteInstance> mySpriteInstance;
};
