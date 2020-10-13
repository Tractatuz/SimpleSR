#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::MakeScaleMatrix()
{
}

void Transform::MakeRotationMatrix()
{
	rotation.x += rotXSpeed;

	Matrix4x4 rotXmat;
	rotXmat.mMatrix[0] = 1.0f;
	rotXmat.mMatrix[5] = cos(rotation.x);
	rotXmat.mMatrix[6] = -sin(rotation.x);
	rotXmat.mMatrix[9] = sin(rotation.x);
	rotXmat.mMatrix[10] = cos(rotation.x);
	rotXmat.mMatrix[15] = 1.0f;

	localToWorldMatrix = rotXmat;
}

void Transform::MakePositionMatrix()
{
}

void Transform::MakeLocalToWorldMatrix()
{
	MakeScaleMatrix();
	MakeRotationMatrix();
	MakePositionMatrix();
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
