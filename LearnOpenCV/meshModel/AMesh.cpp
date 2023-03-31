#include "AMesh.h"
#include "../render/RenderMain.h"

using namespace Core;

Core::AMesh::AMesh(std::string uid, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures):ABaseMesh(uid)
{
	printf("add mesh %s \n", uid.c_str());
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	mesh = Render::CreateRenderMesh(id);
	bindRender();
}

void Core::AMesh::bindRender()
{
	mesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(Vertex), &vertices[0]);
	mesh->BindElementBufferData(indices.size() * sizeof(unsigned int), &indices[0]);

	mesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, Position));
	mesh->VertexAttribPointer(1, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, Normal));
	// vertex texture coords
	mesh->VertexAttribPointer(2, 2, Render::ShaderParamType::SPT_VEC2, false, sizeof(Vertex), offsetof(Vertex, TexCoords));
	// vertex tangent
	mesh->VertexAttribPointer(3, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, Tangent));
	// vertex bitangent
	mesh->VertexAttribPointer(4, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, Bitangent));
	// ids
	//mesh->VertexAttribPointer(5, 4, Render::ShaderParamType::SPT_INT, sizeof(Vertex), offsetof(Vertex, m_BoneIDs));

	// weights
	//mesh->VertexAttribPointer(6, 4, Render::ShaderParamType::SPT_VEC4, false, sizeof(Vertex), offsetof(Vertex, m_Weights));

	mesh->SetImage(textures);
}
