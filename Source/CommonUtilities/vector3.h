#pragma once
#include <math.h>

#define self (*this)

namespace CU
{
	template<typename TYPE>
	class Vector2;

	template<typename TYPE>
	class Vector4;

	template<typename TYPE>
	class Vector3
	{
	public:
		Vector3();
		Vector3(const Vector3& aVector3);
		Vector3(const TYPE aX, const TYPE aY, const TYPE aZ);
		explicit Vector3(const Vector2<TYPE> aVector2, const TYPE aZ = 0);
		explicit Vector3(const Vector4<TYPE>& aVector4);

		template<typename U> explicit Vector3(const Vector3<U>& aVector);
		template<typename U> explicit Vector3(const U aX, const U aY, const U aZ);

		void Set(const TYPE aX, const TYPE aY, const TYPE aZ);
		template <typename U> void Set(const U aX, const U aY, const U aZ);

		Vector3& operator=(const Vector3& aRight);
		template <typename U> Vector3& operator=(const Vector3<U>& aRight);
		Vector3& operator=(const Vector4<TYPE>& aRight);

		Vector3& operator+=(const Vector3& aRight);
		Vector3& operator-=(const Vector3& aRight);
		Vector3& operator*=(const Vector3& aRight);
		Vector3& operator/=(const Vector3& aRight);

		Vector3& operator*=(const TYPE aRight);
		Vector3& operator/=(const TYPE aRight);

		Vector3 operator+(const Vector3& aRight) const;
		Vector3 operator-(const Vector3& aRight) const;
		Vector3 operator*(const Vector3& aRight) const;
		Vector3 operator/(const Vector3& aRight) const;

		Vector3 operator*(const TYPE aScalar) const;
		Vector3 operator/(const TYPE aRight) const;

		Vector3 operator-() const;

		bool operator==(const Vector3& aRight) const;
		bool operator!=(const Vector3& aRight) const;

		TYPE Length() const;
		TYPE Length2() const;
		TYPE Dot(const Vector3& aRight) const;
		Vector3 Cross(const Vector3& aRight) const;
		Vector3 GetNormalized() const;

		Vector3& Normalize();

		Vector3& InterPolateTowards(const Vector3& aVectorToInterPolateTowards, float aInterpolatingSpeed);

		union
		{
#pragma warning(disable : 4201) // nonstandard extension used: nameless struct/union

			struct
			{
				TYPE x, y, z;
			};

			struct
			{
				TYPE r, g, b;
			};

#pragma warning(default : 4201)

			TYPE vector[3];
		};

		static const Vector3 Zero;
		static const Vector3 UnitX;
		static const Vector3 UnitY;
		static const Vector3 UnitZ;
		static const Vector3 One;
	};

	using Vector3i = Vector3<int>;
	using Vector3ui = Vector3<unsigned int>;
	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;

	using Point3i = Vector3<int>;
	using Point3ui = Vector3<unsigned int>;
	using Point3f = Vector3<float>;
	using Point3d = Vector3<double>;

	template<typename TYPE>
	using Point3 = Vector3 < TYPE >;

	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::Zero(0, 0, 0);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitX(1, 0, 0);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitY(0, 1, 0);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::UnitZ(0, 0, 1);
	template<typename TYPE> const Vector3<TYPE> Vector3<TYPE>::One(1, 1, 1);

	template<typename TYPE>
	Vector3<TYPE>& operator*=(const TYPE aLeft, Vector3<TYPE>& aRight)
	{
		return aRight *= aLeft;
	}

	template<typename TYPE>
	Vector3<TYPE> operator*(const TYPE aLeft, Vector3<TYPE> aRight)
	{
		return aRight *= aLeft;
	}

	template<typename TYPE>
	Vector3<TYPE>::Vector3()
		: x(static_cast<TYPE>(0))
		, y(static_cast<TYPE>(0))
		, z(static_cast<TYPE>(0))
	{
	}

	template<typename TYPE>
	Vector3<TYPE>::Vector3(const Vector3& aVector3)
		: x(aVector3.x)
		, y(aVector3.y)
		, z(aVector3.z)
	{
	}

	template<typename TYPE>
	Vector3<TYPE>::Vector3(const TYPE aX, const TYPE aY, const TYPE aZ)
		: x(aX)
		, y(aY)
		, z(aZ)
	{
	}

	template<typename TYPE>
	Vector3<TYPE>::Vector3(const Vector2<TYPE> aVector2, const TYPE aZ)
		: x(aVector2.x)
		, y(aVector2.y)
		, z(aZ)
	{
	}

	template<typename TYPE>
	Vector3<TYPE>::Vector3(const Vector4<TYPE>& aVector4)
		: x(aVector4.x)
		, y(aVector4.y)
		, z(aVector4.z)
	{
	}

	template<typename TYPE>
	template<typename U>
	inline Vector3<TYPE>::Vector3(const Vector3<U> &aVector)
		: x(static_cast<TYPE>(aVector.x))
		, y(static_cast<TYPE>(aVector.y))
		, z(static_cast<TYPE>(aVector.z))
	{
	}

	template<typename TYPE>
	template<typename U>
	inline Vector3<TYPE>::Vector3(const U aX, const U aY, const U aZ)
		: x(static_cast<TYPE>(aX))
		, y(static_cast<TYPE>(aY))
		, z(static_cast<TYPE>(aZ))
	{
	}

	template<typename TYPE>
	template<typename U>
	inline void Vector3<TYPE>::Set(const U aX, const U aY, const U aZ)
	{
		x = static_cast<TYPE>(aX);
		y = static_cast<TYPE>(aY);
		z = static_cast<TYPE>(aZ);
	}

	template<typename TYPE>
	inline void Vector3<TYPE>::Set(const TYPE aX, const TYPE aY, const TYPE aZ)
	{
		x = aX;
		y = aY;
		z = aZ;
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator=(const Vector3& aRight)
	{
		x = aRight.x;
		y = aRight.y;
		z = aRight.z;

		return self;
	}

	template<typename TYPE>
	template<typename U>
	Vector3<TYPE>& Vector3<TYPE>::operator=(const Vector3<U>& aRight)
	{
		x = static_cast<TYPE>(aRight.x);
		y = static_cast<TYPE>(aRight.y);
		z = static_cast<TYPE>(aRight.z);

		return self;
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator=(const Vector4<TYPE>& aRight)
	{
		x = aRight.x;
		y = aRight.y;
		z = aRight.z;

		return self;
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator+=(const Vector3& aRight)
	{
		x += aRight.x;
		y += aRight.y;
		z += aRight.z;

		return self;
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator-=(const Vector3& aRight)
	{
		x -= aRight.x;
		y -= aRight.y;
		z -= aRight.z;

		return self;
	}

	template<typename TYPE>
	inline Vector3<TYPE>& Vector3<TYPE>::operator*=(const Vector3& aRight)
	{
		x *= aRight.x;
		y *= aRight.y;
		z *= aRight.z;

		return self;
	}

	template<typename TYPE>
	inline Vector3<TYPE>& Vector3<TYPE>::operator/=(const Vector3& aRight)
	{
		x /= aRight.x;
		y /= aRight.y;
		z /= aRight.z;

		return self;
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator*=(const TYPE aRight)
	{
		x *= aRight;
		y *= aRight;
		z *= aRight;
		
		return self;
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::operator/=(const TYPE aRight)
	{
		x /= aRight;
		y /= aRight;
		z /= aRight;

		return self;
	}

	template<typename TYPE>
	inline Vector3<TYPE> Vector3<TYPE>::operator+(const Vector3& aRight) const
	{
		Vector3 sum = self;
		return sum += aRight;
	}

	template<typename TYPE>
	inline Vector3<TYPE> Vector3<TYPE>::operator-(const Vector3& aRight) const
	{
		Vector3 difference = self;
		return difference -= aRight;
	}

	template<typename TYPE>
	inline Vector3<TYPE> Vector3<TYPE>::operator*(const Vector3& aRight) const
	{
		Vector3 product = self;
		return product *= aRight;
	}

	template<typename TYPE>
	inline Vector3<TYPE> Vector3<TYPE>::operator/(const Vector3& aRight) const
	{
		Vector3 quotient = self;
		return quotient /= aRight;
	}

	template<typename TYPE>
	inline Vector3<TYPE> Vector3<TYPE>::operator*(const TYPE aScalar) const
	{
		Vector3 product = self;
		return product *= aScalar;
	}

	template<typename TYPE>
	inline Vector3<TYPE> Vector3<TYPE>::operator/(const TYPE aRight) const
	{
		Vector3 quotient = self;
		return quotient /= aRight;
	}

	template<typename TYPE>
	inline Vector3<TYPE> Vector3<TYPE>::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	template<typename TYPE>
	inline bool Vector3<TYPE>::operator==(const Vector3& aRight) const
	{
		return (x == aRight.x && y == aRight.y && z == aRight.z);
	}

	template<typename TYPE>
	inline bool Vector3<TYPE>::operator!=(const Vector3& aRight) const
	{
		return !(self == aRight);
	}

	template<typename TYPE>
	TYPE Vector3<TYPE>::Length() const
	{
		return sqrt(Length2());
	}

	template<typename TYPE>
	TYPE Vector3<TYPE>::Length2() const
	{
		return ((x * x) + (y * y) + (z * z));
	}

	template<typename TYPE>
	TYPE Vector3<TYPE>::Dot(const Vector3& aRight) const
	{
		return ((x * aRight.x) + (y * aRight.y) + (z * aRight.z));
	}

	template<typename TYPE>
	Vector3<TYPE> Vector3<TYPE>::Cross(const Vector3 &aRight) const
	{
		return Vector3(
			(y * aRight.z) - (z * aRight.y),
			(z * aRight.x) - (x * aRight.z),
			(x * aRight.y) - (y * aRight.x)
		);
	}

	template<typename TYPE>
	Vector3<TYPE> Vector3<TYPE>::GetNormalized() const
	{
		Vector3<TYPE> normalized = self;
		return normalized.Normalize();
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::Normalize()
	{
		TYPE length = Length();
		if (length > 0)
		{
			x /= length;
			y /= length;
			z /= length;
		}

		return self;
	}

	template<typename TYPE>
	Vector3<TYPE>& Vector3<TYPE>::InterPolateTowards(const Vector3& aVectorToInterPolateTowards, float aInterpolatingSpeed)
	{
		x = x + aInterpolatingSpeed * (aVectorToInterPolateTowards.x - x);
		y = y + aInterpolatingSpeed * (aVectorToInterPolateTowards.y - y);
		z = z + aInterpolatingSpeed * (aVectorToInterPolateTowards.z - z);

		return self;
	}
} 

#undef self