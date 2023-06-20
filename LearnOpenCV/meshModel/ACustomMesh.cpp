#include "ACustomMesh.h"
#include "../render/RenderMain.h"

using namespace Core;


Core::ACustomMesh::ACustomMesh(std::string uid) : ABaseMesh(uid)
{
	mesh = Render::CreateRenderCustomMesh();
}

void Core::ACustomMesh::BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data)
{
	mesh->BindArrayBufferData(verticesNum, dataSize, data);
}

void Core::ACustomMesh::BindElementBufferData(std::vector<unsigned int> indices)
{
	mesh->BindElementBufferData(indices.size() * sizeof(unsigned int), &indices[0]);
}

void Core::ACustomMesh::VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
{
	mesh->VertexAttribPointer(passageway, dataSize, dataType, b, delaySize, startIndex);
}

void Core::ACustomMesh::setImage(std::vector<Render::Texture> textures)
{
	mesh->SetImage(textures);
}
