#pragma once

namespace wendy
{
	class IRenderPackage
	{
	public:
		IRenderPackage();
		virtual ~IRenderPackage();

		virtual bool Init(const CU::Vector2ui aSize) = 0;
		virtual void Clear(const CU::Vector4f aClearColor = CU::Vector4f::Zero) = 0;
		virtual void Activate() = 0;
		virtual CU::Vector2ui GetSize() = 0;
	};
}
