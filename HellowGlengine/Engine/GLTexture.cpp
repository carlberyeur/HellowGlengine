#include "stdafx.h"
#include "GLTexture.h"

#include <Windows.h>
#include <gl\GL.h>
#include "OpenGLExtensions.h"

namespace wendy
{
	CGLTexture::CGLTexture()
		: myTextureID(0u)
	{
	}

	CGLTexture::~CGLTexture()
	{
		glDeleteTextures(1, &myTextureID);
	}

	CGLTexture::eLoadResult CGLTexture::Init(const unsigned int aTextureUnit, const void* aPixelData, const CU::Vector2ui& aTextureSize)
	{
		if (aPixelData == nullptr)
		{
			return eLoadResult::eNoPixelData;
		}

		if (aTextureUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - GL_TEXTURE0)
		{
			return eLoadResult::eInvalidTextureUnit;
		}

		myTextureSize = aTextureSize;

		// Set the unique texture unit in which to store the data.
		glActiveTexture(GL_TEXTURE0 + aTextureUnit);

		// Generate an ID for the texture.
		glGenTextures(1, &myTextureID);

		//// Bind the texture as a 2D texture.
		glBindTexture(GL_TEXTURE_2D, myTextureID);

		//// Load the image data into the texture unit.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myTextureSize.x, myTextureSize.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, aPixelData);

		//// Set the texture color to either wrap around or clamp to the edge.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		//// Set the texture filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		//// Generate mipmaps for the texture.
		glGenerateMipmap(GL_TEXTURE_2D);

		return eLoadResult::eSuccess;
	}

	CGLTexture::eLoadResult CGLTexture::Init(const unsigned int aTextureUnit, std::nullptr_t, const CU::Vector2ui& aTextureSize)
	{
		if (aTextureUnit >= GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - GL_TEXTURE0)
		{
			return eLoadResult::eInvalidTextureUnit;
		}

		myTextureSize = aTextureSize;

		glActiveTexture(GL_TEXTURE0 + aTextureUnit);
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myTextureSize.x, myTextureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		return eLoadResult::eSuccess;
	}

	void CGLTexture::SetTexture()
	{
		glBindTexture(GL_TEXTURE_2D, myTextureID);
	}
}
