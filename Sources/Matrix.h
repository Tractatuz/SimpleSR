#pragma once

#include <istream>
#include "Vector3.h"

struct Matrix4x4
{
	Matrix4x4() { Identity(); }
	~Matrix4x4() { }

	float mMatrix[16];

	Matrix4x4 operator * (Matrix4x4& rhs)
	{
		Matrix4x4 results;
		
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				float sum = 0;
				
				for (int k = 0; k < 4; ++k)
				{
					sum += (*this)(i, k) * rhs(k, j);
				}

				results.mMatrix[i * 4 + j] = sum;
			}
		}

		return results;
	}

	float operator () (const int& x, const int& y) const
	{
		return mMatrix[x * 4 + y];
	}

	static Vector3 TransformNormal(const Matrix4x4& m, const Vector3& v)
	{
		Vector3 result;

		result.x = v.x * m(0, 0) + v.y * m(0, 1) + v.z * m(0, 2);
		result.y = v.x * m(1, 0) + v.y * m(1, 1) + v.z * m(1, 2);
		result.z = v.x * m(2, 0) + v.y * m(2, 1) + v.z * m(2, 2);

		return result;
	}

	static Vector3 TransformCoord(const Matrix4x4& m, const Vector3& v)
	{
		Vector3 result;

		result.x = v.x * m(0, 0) + v.y * m(0, 1) + v.z * m(0, 2) + m(0, 3);
		result.y = v.x * m(1, 0) + v.y * m(1, 1) + v.z * m(1, 2) + m(1, 3);
		result.z = v.x * m(2, 0) + v.y * m(2, 1) + v.z * m(2, 2) + m(2, 3);

		return result;
	}

	void Identity()
	{
		memset(mMatrix, 0, sizeof(mMatrix));
		mMatrix[0] = mMatrix[5] = mMatrix[10] = mMatrix[15] = 1.0f;
	}
};