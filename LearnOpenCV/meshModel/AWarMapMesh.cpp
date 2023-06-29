#include "AWarMapMesh.h"
#include "../render/RenderMain.h"

using namespace Core;


Core::AWarMapMesh::AWarMapMesh(std::string uid) : ABaseMesh(uid)
{
	customMaterial = new Render::Material();
}

Core::AWarMapMesh::~AWarMapMesh()
{

}

void Core::AWarMapMesh::SetRenderMesh(Render::RenderBaseMesh* renderMesh)
{
	mesh = renderMesh;
}

void Core::AWarMapMesh::render(Render::ShaderProgram* program, Render::Material* material)
{
	program->RenderMaterial(customMaterial);
	mesh->Render(program, material);
}

Render::Material* Core::AWarMapMesh::getCustomMaterial()
{
	return customMaterial;
}
