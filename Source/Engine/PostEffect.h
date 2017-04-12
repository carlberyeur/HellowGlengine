#pragma once

namespace wendy
{
	class IRenderPackage;

	class IPostEffect
	{
	public:
		IPostEffect();
		virtual ~IPostEffect();

		virtual void DoEffect(const int aRenderPackageCount, IRenderPackage* aRenderPackages) = 0;
	};
}
