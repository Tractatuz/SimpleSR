#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Initialize()
{
}

void Camera::Update()
{
	// TODO : Camera move by Input

	Vector3 look = target - position;
	look.Normalize();

	Vector3 right = look.CrossProduct(up);
	right.Normalize();

	Vector3 lookUp = look.CrossProduct(right);
	lookUp.Normalize();

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			position = position + look * camSpeed;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			position = position - right * camSpeed;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			position = position - look * camSpeed;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			position = position + right * camSpeed;
		}

		if (GetAsyncKeyState('Q') & 0x8000)
		{
			position = position + lookUp * camSpeed;
		}

		if (GetAsyncKeyState('Z') & 0x8000)
		{
			position = position - lookUp * camSpeed;
		}
	}

	CalcViewMatrix();
	CalcProjMatrix();
}

void Camera::CalcViewMatrix()
{
	view.Identity();

	Vector3 zaxis = target - position;
	zaxis.Normalize();
	Vector3 xaxis = up.CrossProduct(zaxis);
	xaxis.Normalize();
	Vector3 yaxis = zaxis.CrossProduct(xaxis);

	view.mMatrix[0] = xaxis.x;
	view.mMatrix[1] = yaxis.x;
	view.mMatrix[2] = zaxis.x;
	view.mMatrix[4] = xaxis.y;
	view.mMatrix[5] = yaxis.y;
	view.mMatrix[6] = zaxis.y;
	view.mMatrix[8] = xaxis.z;
	view.mMatrix[9] = yaxis.z;
	view.mMatrix[10] = zaxis.z;
	view.mMatrix[12] = -1.0f * xaxis.DotProduct(position);
	view.mMatrix[13] = -1.0f * yaxis.DotProduct(position);
	view.mMatrix[14] = -1.0f * zaxis.DotProduct(position);
	view.mMatrix[15] = 1.0f;
}

void Camera::CalcProjMatrix()
{
	proj.Identity();

	float h = 1.0f / tanf(fovY / 2.0f);
	float w = h / aspect;
	proj.mMatrix[0] = w;
	proj.mMatrix[5] = h;
	proj.mMatrix[10] = far_limit / (far_limit - near_limit);
	proj.mMatrix[11] = 1;
	proj.mMatrix[14] = near_limit * far_limit / (near_limit - far_limit);
}

void Camera::Release()
{
}