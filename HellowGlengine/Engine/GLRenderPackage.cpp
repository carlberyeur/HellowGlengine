#include "stdafx.h"
#include "GLRenderPackage.h"

#include "OpenGLExtensions.h"

namespace wendy
{
	CGLRenderPackage::CGLRenderPackage()
		: myFrameBuffer(0)
		, myTexture(0)
		, myDepthBuffer(0)
	{
	}

	CGLRenderPackage::~CGLRenderPackage()
	{
		//glDeleteFramebuffers(1, &myFrameBuffer);
		glDeleteTextures(1, &myTexture);
	}

	bool CGLRenderPackage::Init(const CU::Vector2ui aSize)
	{
		myViewPort.Set(0, 0, aSize.x, aSize.y);

		glGenFramebuffers(1, &myFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer);

		glGenTextures(1, &myTexture);
		glBindTexture(GL_TEXTURE_2D, myTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, aSize.x, aSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		glGenRenderbuffers(1, &myDepthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, myDepthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, aSize.x, aSize.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, myDepthBuffer);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, myTexture, 0);

		GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers); // "1" is the size of drawBuffers

		return (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);
	}

	void CGLRenderPackage::Clear(const CU::Vector4f aClearColor)
	{
		//glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer); -----------------???

		glClearColor(aClearColor.x, aClearColor.y, aClearColor.z, aClearColor.w);

		unsigned int bitMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void CGLRenderPackage::Activate()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer);
		glViewport(myViewPort.x, myViewPort.y, myViewPort.z, myViewPort.w);
	}

	CU::Vector2ui CGLRenderPackage::GetSize()
	{
		return CU::Vector2ui(myViewPort.z - myViewPort.x, myViewPort.w - myViewPort.y);

		//return CU::Vector2ui::Zero;
	}
}