#pragma once

#include "stdafx.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Camera.h"

extern HWND hWnd;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
	Release();
}

void Renderer::Initialize()
{
	CreateBuffer();

	//this->mesh = mesh;
	//this->camera = camera;
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

void Renderer::CreateBuffer()
{
	screen_dc = GetDC(hWnd);
	backbuffer_dc = CreateCompatibleDC(screen_dc);
	backbuffer_bitmap = CreateCompatibleBitmap(screen_dc, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	SelectObject(backbuffer_dc, backbuffer_bitmap);
}

void Renderer::ClearBuffer()
{
	//memset(gBuffer, 0x88, sizeof(gBuffer));
	std::fill(gBuffer, gBuffer + (WINDOW_SIZE_X * WINDOW_SIZE_Y), 0x000000FF);
	memset(zBuffer, 0, sizeof(zBuffer));
	//std::fill(zBuffer, zBuffer + (WINDOW_SIZE_X * WINDOW_SIZE_Y), camera->far_limit);
}

void Renderer::SwapChain()
{
	int copysize = SetBitmapBits(backbuffer_bitmap, sizeof(gBuffer), gBuffer);
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
			//trianglePrimitive[j] = Matrix4x4::TransformCoord(camera->proj, Matrix4x4::TransformCoord(camera->view, trianglePrimitive[j]));
			trianglePrimitive[j] = Matrix4x4::TransformCoord(camera->view, trianglePrimitive[j]);
		}

		DrawWireframe(trianglePrimitive);

		//	/*if (DrawTriangles(trianglePrimitive))
		//	{
		//		++testTriCount;
		//	}*/
	}
}

void Renderer::DrawLine(const Vector3 & vertex1, const Vector3 & vertex2)
{
	int x1 = (vertex1.x + 1) * WINDOW_SIZE_X * 0.5;
	int y1 = (-vertex1.y + 1) * WINDOW_SIZE_Y * 0.5;
	int x2 = (vertex2.x + 1) * WINDOW_SIZE_X * 0.5;
	int y2 = (-vertex2.y + 1) * WINDOW_SIZE_Y * 0.5;

	//transpose line if it is too steep
	bool steep = false;
	if (std::abs(x1 - x2) < std::abs(y1 - y2)) 
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
		steep = true;
	}

	//Redefine line so that it is left to right
	if (x1 > x2) 
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	//Redefined to use only int arithmetic
	int dx = x2 - x1;
	int dy = y2 - y1;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y1;

	for (int x = x1; x <= x2; x++) 
	{
		if (steep) 
		{
			if (y * WINDOW_SIZE_X + x >= WINDOW_SIZE_X * WINDOW_SIZE_Y)
			{
				continue;
			}

			gBuffer[y * WINDOW_SIZE_X + x] = 0x00;
		}
		else 
		{
			if (x * WINDOW_SIZE_X + y >= WINDOW_SIZE_X * WINDOW_SIZE_Y)
			{
				continue;
			}

			gBuffer[x * WINDOW_SIZE_X + y] = 0x00;
		}

		error2 += derror2;
		if (error2 > dx) 
		{
			y += (y2 > y1 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void Renderer::DrawWireframe(Vector3 * vertices)
{
	DrawLine(vertices[0], vertices[1]);
	DrawLine(vertices[1], vertices[2]);
	DrawLine(vertices[0], vertices[2]);
}

bool Renderer::DrawTriangles(Vector3* vertices)
{
	ViewportTransform(vertices);
	
	int xMax = 0, xMin = 0, yMax = 0, yMin = 0;
	//SetMinMax(xMax, xMin, yMax, yMin, vertices);

	for (int y = yMin; y <= yMax; ++y) 
	{
		for (int x = xMin; x <= xMax; ++x)
		{
			/*if (IsInsideTriangle(x, y, vertices))
			{
				gBuffer[x * WINDOW_SIZE_X + y] = PixelShader(0, 0);
			}
			else
			{
				int i = 0;
			}*/
		}
	}

	return false;
}

void Renderer::ViewportTransform(Vector3* vertices)
{
	for (int i = 0; i < 3; ++i) 
	{
		vertices[i].x = ((vertices[i].x + 1) * WINDOW_SIZE_X * 0.5) + 0.5;
		vertices[i].y = ((vertices[i].y + 1) * WINDOW_SIZE_Y * 0.5) + 0.5;
	}
}

//void Renderer::SetMinMax(int & xMax, int & xMin, int & yMax, int & yMin, const Vector3* vertices)
//{
//	xMax = std::max({ vertices[0].x, vertices[1].x, vertices[2].x });
//	xMin = std::min({ vertices[0].x, vertices[1].x, vertices[2].x });
//
//	yMax = std::max({ vertices[0].y, vertices[1].y, vertices[2].y });
//	yMin = std::min({ vertices[0].y, vertices[1].y, vertices[2].y });
//
//	//Clip against screen
//	xMax = std::min(xMax, WINDOW_SIZE_X - 1);
//	xMin = std::max(xMin, 0);
//
//	yMax = std::min(yMax, WINDOW_SIZE_Y - 1);
//	yMin = std::max(yMin, 0);
//}

void Renderer::Release()
{
	DeleteObject(backbuffer_bitmap);
	DeleteDC(backbuffer_dc);
}