#include "AUIMesh.h"
#include "../render/RenderMain.h"

using namespace Core;

Core::AUIMesh::AUIMesh(std::string uid, std::vector<Vertex> vertices, std::vector<unsigned int> indices, Render::Texture textures):ABaseMesh(uid)
{
	printf("add mesh %s \n", uid.c_str());
	id = uid;
	this->vertices = vertices;
	this->indices = indices;
	this->textures.clear();
	this->textures.push_back(textures);

	mesh = Render::CreateRenderMesh(id);
	bindRender();
}

void Core::AUIMesh::bindRender()
{
	mesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(Vertex), &vertices[0]);
	mesh->BindElementBufferData(indices.size() * sizeof(unsigned int), &indices[0]);

	mesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, Position));
	// vertex texture coords
	mesh->VertexAttribPointer(1, 2, Render::ShaderParamType::SPT_VEC2, false, sizeof(Vertex), offsetof(Vertex, TexCoords));
	// ids
	//mesh->VertexAttribPointer(5, 4, Render::ShaderParamType::SPT_INT, sizeof(Vertex), offsetof(Vertex, m_BoneIDs));

	// weights
	//mesh->VertexAttribPointer(6, 4, Render::ShaderParamType::SPT_VEC4, false, sizeof(Vertex), offsetof(Vertex, m_Weights));

	mesh->SetImage(textures);
}
