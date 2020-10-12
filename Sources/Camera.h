#pragma once

#include "Vector3.h"
#include "Matrix.h"

// Simple Perspective Camera
class Camera
{
public:
	Camera();
	~Camera();

public:
	Vector3 position	= Vector3(0.0f, 0.0f, -5.0f);
	Vector3 target		= Vector3(0.0f, 0.0f, 0.0f);
	Vector3 up			= Vector3(0.0f, 1.0f, 0.0f);
	Vector3 front		= Vector3(0.0f, 0.0f, 1.0f);

	float fovY = 60.0f;
	float aspect = 1.778f;
	float near_limit = 0.1f;
	float far_limit = 1000.0f;
	float camSpeed = 0.1f;

	Matrix4x4 view;
	Matrix4x4 proj;

public:
	void Initialize();
	void Update();
	void Release();

private:
	void CalcViewMatrix();
	void CalcProjMatrix();
};

