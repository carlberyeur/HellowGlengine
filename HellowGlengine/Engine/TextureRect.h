#pragma once

namespace wendy
{
	struct STextureRect
	{
		CU::Vector2f topleft;
		CU::Vector2f botright;

		CU::Vector4f AsVector4f() const
		{
			return CU::Vector4f(topleft, botright);
		}
	};
}
