#pragma once

#include <istream>
#include "Vector3.h"

struct Matrix4x4
{
	Matrix4x4()
	{
		memset(mMatrix, 0.0f, sizeof(mMatrix));
	}

	Matrix4x4 operator * (Matrix4x4& rhs)
	{
		Matrix4x4 results;
		// TODO : 
		//for (int rows = 0; rows < 4; ++rows) 
		//{
		//	for (int cols = 0; cols < 4; ++cols) 
		//	{
		//		float total = 0;
		//		for (int sub = 0; sub < 4; ++sub) 
		//		{
		//			int rowLhs = rows; //row ind left matrix
		//			int colLhs = sub; //col ind left matrix
		//			int rowRhs = sub; //row ind right matrix
		//			int colRhs = cols; //col ind right matrix

		//			total += (*this)(rowLhs, colLhs) * rhs(rowRhs, colRhs);
		//		}

		//		results.mMatrix[rows * 4 + cols] = total;
		//	}
		//}

		return results;
	}

	float operator () (const int& y, const int& x) const
	{
		return mMatrix[y * 4 + x];
	}

	static Vector3 TransformNormal(const Matrix4x4& m, const Vector3& v)
	{
		Vector3 result;
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

	float mMatrix[16];
};