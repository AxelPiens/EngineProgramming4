#pragma once

namespace engine
{
	struct Vector3
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vector3() {};
		Vector3(float x, float y, float z) :x(x), y(y), z(z) {};


		//arithmetic
		inline Vector3 operator+(const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}
		inline Vector3 operator-(const Vector3& v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}
		inline Vector3 operator*(float scale) const
		{
			return Vector3(x * scale, y * scale, z * scale);
		}
		inline Vector3 operator/(float scale) const
		{
			const auto revScale = 1.0f / scale;
			return Vector3(x * revScale, y * revScale, z * revScale);
		}


		inline Vector3& operator+=(const Vector3& v)
		{
			x += v.x; y += v.y; z += v.z;
			return *this;
		}
		inline Vector3& operator-=(const Vector3& v)
		{
			x -= v.x; y -= v.y; z -= v.z;
			return *this;
		}
		inline Vector3& operator*=(float scale)
		{
			x *= scale; y *= scale; z *= scale;
			return *this;
		}
		inline Vector3& operator/=(float scale)
		{
			const float revScale = 1.0f / scale;
			x *= revScale; y *= revScale; z *= revScale;
			return *this;
		}


		inline bool operator==(const Vector3& v)
		{
			if (x == v.x)
			{
				if (y == v.y)
				{
					if (z == v.z)
					{
						return true;
					}
				}
			}
			return false;
		}
	};
}

