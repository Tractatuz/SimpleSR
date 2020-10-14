#pragma once

#include "stdafx.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Camera.h"
#include "Transform.h"

extern HWND hWnd;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	Release();
}

void Renderer::CreateBuffer()
{
	screen_dc = GetDC(hWnd);
	backbuffer_dc = CreateCompatibleDC(screen_dc);
	backbuffer_bitmap = CreateCompatibleBitmap(screen_dc, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	SelectObject(backbuffer_dc, backbuffer_bitmap);
}

void Renderer::ClearBuffer()
{
	// Reset gBuffer Blue
	std::fill(gBuffer, gBuffer + (WINDOW_SIZE_X * WINDOW_SIZE_Y), 0x000000FF);
	// Reset zBuffer zero
	memset(zBuffer, 0, sizeof(zBuffer));
}

void Renderer::SwapChain()
{
	SetBitmapBits(backbuffer_bitmap, sizeof(gBuffer), gBuffer);
	BitBlt(screen_dc, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y, backbuffer_dc, 0, 0, SRCCOPY);
}

void Renderer::DrawMesh()
{
	int numFaces = mesh->numFaces;
	Vector3 trianglePrimitive[3], normalPrimitive[3];
	for (int i = 0; i < numFaces; ++i)
	{
		trianglePrimitive[0] = mesh->vertices[mesh->vertexIndices[i].x];
		trianglePrimitive[1] = mesh->vertices[mesh->vertexIndices[i].y];
		trianglePrimitive[2] = mesh->vertices[mesh->vertexIndices[i].z];

		normalPrimitive[0] = mesh->normals[mesh->normalsIndices[i].x];
		normalPrimitive[1] = mesh->normals[mesh->normalsIndices[i].y];
		normalPrimitive[2] = mesh->normals[mesh->normalsIndices[i].z];

		for (int j = 0; j < 3; ++j)
		{
			trianglePrimitive[j] = Matrix4x4::TransformCoord(camera->proj, Matrix4x4::TransformCoord(camera->view, Matrix4x4::TransformCoord(mesh->transform->GetLocalToWorldMatrix(), trianglePrimitive[j])));
		}

		if (isWireFrameMode)
		{
			DrawWireframe(trianglePrimitive);
		}
		else
		{
			DrawTriangles(trianglePrimitive);
		}
	}
}

void Renderer::DrawLine(const Vector3 & vertex1, const Vector3 & vertex2)
{
	// x1, y1 is always leftside;
	int x1, x2, y1, y2;
	if (vertex2.x >= vertex1.x)
	{
		x1 = (int)vertex1.x;
		y1 = (int)vertex1.y;
		x2 = (int)vertex2.x;
		y2 = (int)vertex2.y;
	}
	else
	{
		x1 = (int)vertex2.x;
		y1 = (int)vertex2.y;
		x2 = (int)vertex1.x;
		y2 = (int)vertex1.y;
	}

	float dx = vertex2.x - vertex1.x;
	float dy = vertex2.y - vertex1.y;
	
	bool isSteep = false;
	if (std::abs(dx) < 1)
	{
		isSteep = true;
	}

	if (isSteep)
	{
		if (dy > 0)
		{
			for (int x = x1, y = y1; y <= y2; ++y)
			{
				gBuffer[y * WINDOW_SIZE_X + x] = 0x00;
			}

			return;
		}
		else
		{
			for (int x = x1, y = y1; y >= y2; --y)
			{
				gBuffer[y * WINDOW_SIZE_X + x] = 0x00;
			}

			return;
		}
	}
	else
	{
		bool isSlopeNegative = false;
		if (dx * dy < 0)
		{
			isSlopeNegative = true;
		}

		for (int x = x1, y = y1; x <= x2; ++x)
		{
			if (std::abs(dy) < 1)
			{
				gBuffer[y * WINDOW_SIZE_X + x] = 0x00;
			}
			else
			{
				if (isSlopeNegative)
				{
					for (; (y - y1) >= dy / dx * (x - x1); --y)
					{
						gBuffer[y * WINDOW_SIZE_X + x] = 0x00;
					}
				}
				else
				{
					for (; (y - y1) <= dy / dx * (x - x1); ++y)
					{
						gBuffer[y * WINDOW_SIZE_X + x] = 0x00;
					}
				}
			}
		}
	}
}

void Renderer::DrawWireframe(Vector3 * vertices)
{
	ViewportTransform(vertices);

	DrawLine(vertices[0], vertices[1]);
	DrawLine(vertices[1], vertices[2]);
	DrawLine(vertices[0], vertices[2]);
}

void Renderer::DrawTriangles(Vector3* vertices)
{
	ViewportTransform(vertices);

	int xMax = 0, xMin = 0, yMax = 0, yMin = 0;
	SetMinMax(xMax, xMin, yMax, yMin, vertices);

	for (int y = yMin; y <= yMax; ++y) 
	{
		for (int x = xMin; x <= xMax; ++x)
		{
			if (IsInsideTriangle(x, y, vertices))
			{
				//gBuffer[x * WINDOW_SIZE_X + y] = PixelShader(0, 0);
				gBuffer[x * WINDOW_SIZE_X + y] = 0x00;
			}
			else
			{
				int i = 0;
			}
		}
	}
}

void Renderer::ViewportTransform(Vector3* vertices)
{
	for (int i = 0; i < 3; ++i) 
	{
		vertices[i].x = ((vertices[i].x + 1) * WINDOW_SIZE_X * 0.5f) + 0.5f;
		vertices[i].y = ((vertices[i].y + 1) * WINDOW_SIZE_Y * 0.5f) + 0.5f;
	}
}

void Renderer::SetMinMax(int& xMax, int& xMin, int& yMax, int& yMin, const Vector3* vertices)
{
	/*xMax = std::max({ vertices[0].x, vertices[1].x, vertices[2].x });
	xMin = std::min({ vertices[0].x, vertices[1].x, vertices[2].x });
	
	yMax = std::max({ vertices[0].y, vertices[1].y, vertices[2].y });
	yMin = std::min({ vertices[0].y, vertices[1].y, vertices[2].y });
	
	xMax = std::min(xMax, WINDOW_SIZE_X - 1);
	xMin = std::max(xMin, 0);
	
	yMax = std::min(yMax, WINDOW_SIZE_Y - 1);
	yMin = std::max(yMin, 0);*/
}

bool Renderer::IsInsideTriangle(int x, int y, const Vector3* vertices)
{
	return false;
}

//Vector3 Renderer::VertexShader(const Matrix4x4 & viewProj, const Vector3 & vertex)
//{
//	return Vector3();
//}
//
//int Renderer::PixelShader(float u, float v)
//{
//	return 0;
//}

void Renderer::Initialize()
{
	CreateBuffer();
}

void Renderer::Update()
{
}

void Renderer::Render()
{
	ClearBuffer();
	DrawMesh();
	SwapChain();
}

void Renderer::Release()
{
	DeleteObject(backbuffer_bitmap);
	DeleteDC(backbuffer_dc);
}