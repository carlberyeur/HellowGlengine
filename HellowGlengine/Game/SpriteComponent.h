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

	virtual IComponent* Copy() override;
	virtual void Init() override;

	void Render();

	virtual bool Serialize(CU::ISerializer& aSerializer) override;

private:
	CU::UniquePointer<wendy::CSpriteInstance> mySpriteInstance;
};
