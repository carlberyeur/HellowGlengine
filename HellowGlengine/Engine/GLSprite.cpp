#include "stdafx.h"
#include "GLSprite.h"
#include "TextureManager.h"

#include "OpenGLFramework.h"
#include <Windows.h>
#include <gl/GL.h>
#include "wglext.h"
#include "glext.h"

#include "GLRenderObject.h"
#include "GLEffect.h"
#include "GLTexture.h"
#include "EInputLayout.h"

CGLSprite::CGLSprite()
{
	myRenderObject = new CGLRenderObject();
	myRenderObject->Init();

	ITexture* tex = nullptr;
	CEngine::GetInstance().GetTextureManager().LoadTexture("Textures/square.tga", tex);
	myTexture = CU::UniquePointer<ITexture>(tex);

	myEffect = new CGLEffect();
	myEffect->Init("Shaders/VS_", "", "Shaders/FS_", eInputLayout::eInputLayout_ePos | eInputLayout::eInputLayout_eTex);

	CGLEffect* effect = (CGLEffect*)myEffect.GetRawPointer();
	mySetPositionUniform = effect->BindUniformVector3("spritePosition");
	mySetSizeUniform = effect->BindUniformVector2("spriteSize");
	mySetTextureUniform = effect->BindUniformInt("albedoTexture");
}

CGLSprite::~CGLSprite()
{
}

void CGLSprite::Render(const CU::Vector2f aPosition)
{
	myEffect->Activate();

	mySetTextureUniform(0);
	mySetPositionUniform(CU::Vector3f(aPosition, 0));
	mySetSizeUniform(myTexture->GetTextureSizeF() / CEngine::GetInstance().GetWindowSizeF());

	myRenderObject->Render();
}
