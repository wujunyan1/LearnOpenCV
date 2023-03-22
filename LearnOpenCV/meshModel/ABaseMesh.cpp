#include "ABaseMesh.h"
#include "../render/RenderMain.h"

using namespace Core;

Core::ABaseMesh::ABaseMesh(std::string uid)
{
	id = uid;
	mesh = Render::CreateRenderMesh(id);
}