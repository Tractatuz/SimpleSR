#pragma once

#include "BaseObject.h"
#include "Vector3.h"

class Mesh;
class Camera;
class Renderer : BaseObject
{
public:
	Renderer();
	~Renderer();

private:
	int gBuffer[WINDOW_SIZE_X * WINDOW_SIZE_Y];
	float zBuffer[WINDOW_SIZE_X * WINDOW_SIZE_Y];

	HDC screen_dc;
	HDC backbuffer_dc;
	HBITMAP backbuffer_bitmap;

	Mesh* mesh;
	Camera* camera;
	
	Vector3 lightDir = Vector3(1, 1, 1);

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;

protected:
	virtual void Release() override;

public:
	void SetMesh(Mesh* m) { this->mesh = m; }
	void SetCamera(Camera* c) { this->camera = c; }

private:
	void CreateBuffer();
	void ClearBuffer();
	void SwapChain();
	void DrawMesh();

	void DrawLine(const Vector3& vertex1, const Vector3& vertex2);
	void DrawWireframe(Vector3* vertices);
	void DrawTriangles(Vector3* vertices);
	void ViewportTransform(Vector3* vertices);
	//void SetMinMax(int &xMax, int &xMin, int &yMax, int &yMin, const Vector3* vertices);
};

