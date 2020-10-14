#pragma once

#include "BaseObject.h"
#include "Matrix.h"

class Transform : BaseObject
{
public:
	Transform();
	~Transform();

private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Matrix4x4 scaleMatrix;
	Matrix4x4 rotationMatrix;
	Matrix4x4 positionMatrix;
	Matrix4x4 localToWorldMatrix;

public:
	void SetPosition(const Vector3& pos) { this->position = pos; }
	void SetRotation(const Vector3& rot) { this->rotation = rot; }
	Matrix4x4 GetLocalToWorldMatrix() { return localToWorldMatrix; }

private:
	Matrix4x4 MakeScaleMatrix();
	Matrix4x4 MakeRotationMatrix();
	Matrix4x4 MakePositionMatrix();
	void MakeLocalToWorldMatrix();
	float DegreeToRadian(float degree);

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;

protected:
	virtual void Release() override;
};