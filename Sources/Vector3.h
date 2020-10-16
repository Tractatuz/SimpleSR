#pragma once

#include "math.h"

struct Vector3
{
	Vector3(): x(0), y (0), z(0) {};
	Vector3(float val) : x(val), y(val), z(val) {};
	Vector3(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {};

	float x;
	float y;
	float z;

	Vector3 operator + (const Vector3 &rhs) const
	{
		return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	Vector3 operator - (const Vector3 &rhs) const
	{
		return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	Vector3 operator * (const float& rhs) const
	{
		return Vector3(x * rhs, y * rhs, z * rhs);
	}

	Vector3& Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;

		return *this;
	}

	float Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 CrossProduct(const Vector3& rhs) const
	{
		return Vector3((y * rhs.z - z * rhs.y), (z * rhs.x - x * rhs.z), (x * rhs.y - y * rhs.x));
	}

	float DotProduct(const Vector3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
};

struct IntVector3
{
	IntVector3() : x(0), y(0), z(0) {};
	IntVector3(int val) : x(val), y(val), z(val) {};
	IntVector3(int x1, int y1, int z1) : x(x1), y(y1), z(z1) {};

	int x;
	int y;
	int z;
};
