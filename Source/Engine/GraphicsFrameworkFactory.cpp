#include "stdafx.h"
#include "GraphicsFrameworkFactory.h"

namespace wendy
{
	CU::UniquePointer<IGraphicsFramework> CGraphicsFrameworkFactory::CreateFramework(const unsigned int aEngineFlags, IWindow& aWindow)
	{
		CU::UniquePointer<IGraphicsFramework> framework;

		if (aEngineFlags & CEngine::SCreationParameters::eGL)
		{
			framework = CU::MakeUnique<COpenGLFramework>();
			if (!framework->Init(aWindow))
			{
				framework.SafeDelete();
			}
		}
		else if (aEngineFlags & CEngine::SCreationParameters::eDX)
		{
			// not implemented
		}
		else
		{
		}

		return framework;
	}
}