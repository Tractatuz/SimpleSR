#pragma once

#include "BaseObject.h"

class Mesh;
class Camera;
class Renderer;
class Framework : public BaseObject
{
public:
	Framework();
	~Framework();

private:
	Mesh* mesh;
	Camera* camera;
	Renderer* renderer;

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;

protected:
	virtual void Release() override;
};

