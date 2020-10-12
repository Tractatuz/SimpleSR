#include "stdafx.h"
#include "Framework.h"
#include "Mesh.h"
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
	
	renderer = new Renderer();
	renderer->Initialize();
}

void Framework::Update()
{
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