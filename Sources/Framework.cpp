#include "stdafx.h"
#include "Framework.h"
#include "Mesh.h"
#include "Camera.h"
#include "Renderer.h"

Framework::Framework()
{
}

Framework::~Framework()
{
	Release();
}

void Framework::Initialize()
{
	mesh = new Mesh();
	mesh->Initialize();

	camera = new Camera();
	camera->Initialize();
	
	renderer = new Renderer();
	renderer->Initialize();
	renderer->SetMesh(mesh);
	renderer->SetCamera(camera);
}

void Framework::Update()
{
	camera->Update();
}

void Framework::Render()
{
	renderer->Render();
}

void Framework::Release()
{
	delete mesh;
	delete renderer;
}