#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

Matrix4x4 Transform::MakeScaleMatrix()
{
	Matrix4x4 scaleMat;
	// TODO : 
	return scaleMat;
}

Matrix4x4 Transform::MakeRotationMatrix()
{
	float xRadian = DegreeToRadian(rotation.x);
	float yRadian = DegreeToRadian(rotation.y);
	float zRadian = DegreeToRadian(rotation.z);

	Matrix4x4 rotXmat, rotYmat, rotZmat;
	rotXmat.mMatrix[0] = 1.0f;
	rotXmat.mMatrix[5] = cos(xRadian);
	rotXmat.mMatrix[6] = -sin(xRadian);
	rotXmat.mMatrix[9] = sin(xRadian);
	rotXmat.mMatrix[10] = cos(xRadian);
	rotXmat.mMatrix[15] = 1.0f;

	rotYmat.mMatrix[0] = cos(yRadian);
	rotYmat.mMatrix[2] = sin(yRadian);
	rotYmat.mMatrix[5] = 1.0f;
	rotYmat.mMatrix[8] = -sin(yRadian);
	rotYmat.mMatrix[10] = cos(yRadian);
	rotYmat.mMatrix[15] = 1.0f;

	rotZmat.mMatrix[0] = cos(zRadian);
	rotZmat.mMatrix[1] = -sin(zRadian);
	rotZmat.mMatrix[4] = sin(zRadian);
	rotZmat.mMatrix[5] = cos(zRadian);
	rotZmat.mMatrix[10] = 1.0f;
	rotZmat.mMatrix[15] = 1.0f;

	return rotXmat * rotYmat * rotZmat;
}

Matrix4x4 Transform::MakePositionMatrix()
{
	Matrix4x4 positionMat;
	// TODO : 
	return positionMat;
}

void Transform::MakeLocalToWorldMatrix()
{
	Matrix4x4 scaleMat = MakeScaleMatrix();
	Matrix4x4 rotationMat = MakeRotationMatrix();
	Matrix4x4 positionMat = MakePositionMatrix();
	localToWorldMatrix = scaleMat * rotationMat * positionMat;
}

float Transform::DegreeToRadian(float degree)
{
	return degree * 3.141592f / 180; 
}

void Transform::Initialize()
{
	position.x = position.y = position.z = 0;
	rotation.x = rotation.y = rotation.z = 1;
	scale.x = scale.y = scale.z = 1;

	localToWorldMatrix.Identity();
}

void Transform::Update()
{
	MakeLocalToWorldMatrix();
}

void Transform::Render()
{
}

void Transform::Release()
{
}
