#include "AWarMapMesh.h"
#include "../render/RenderMain.h"
#include "../render/renderMesh/RenderCustomMesh.h"

#include "../war/map/Map.h"

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
	Render::RenderCustomMesh* renderMesh = dynamic_cast<Render::RenderCustomMesh*>(mesh);
	War::MapSetting setting = War::Map::GetInstance()->getMapSetting();
	renderMesh->RenderInstances(program, material, setting.height * 2);
}

Render::Material* Core::AWarMapMesh::getCustomMaterial()
{
	return customMaterial;
}
