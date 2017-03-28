#pragma once
#include "RenderCommand.h"
#include "TextureRect.h"

namespace wendy
{
	class CSprite;

	class CRenderSpriteCommand : public IRenderCommand
	{
	public:
		CRenderSpriteCommand(CSprite* aSprite, const STextureRect& aTextureRect, const CU::Vector2f aPosition, const CU::Vector2f aScale);
		~CRenderSpriteCommand();

		void Do() override;

	private:
		const STextureRect myTextureRect;
		const CU::Vector2f myPosition;
		const CU::Vector2f myScale;
		CSprite* mySprite;
	};
}
