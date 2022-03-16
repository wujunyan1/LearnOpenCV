#include "AMesh.h"
#include "../render/RenderMain.h"

using namespace Core;

void Core::AMesh::bindRender()
{
	mesh = Render::CreateRenderMesh();

	mesh->BindArrayBufferData(indices.size(), vertices.size() * sizeof(Vertex), &vertices[0]);
	mesh->BindElementBufferData(indices.size() * sizeof(unsigned int), &indices[0]);

	mesh->VertexAttribPointer(0, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, Position));
	mesh->VertexAttribPointer(1, 3, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, Normal));
	// vertex texture coords
	mesh->VertexAttribPointer(2, 2, Render::ShaderParamType::SPT_VEC3, false, sizeof(Vertex), offsetof(Vertex, TexCoords));
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
