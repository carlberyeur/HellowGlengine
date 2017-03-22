#pragma once
#include "RenderCommand.h"

namespace wendy
{
	class CSprite;

	class CRenderSpriteCommand : public IRenderCommand
	{
	public:
		CRenderSpriteCommand(CSprite* aSprite, const CU::Vector2f aPosition);
		~CRenderSpriteCommand();

		void Do() override;

	private:
		const CU::Vector2f myPosition;
		CSprite* mySprite;
	};
}
