#include "AUIMesh.h"
#include "../render/RenderMain.h"

using namespace Core;

std::map<std::string, AUIMesh> AUIMesh::baseAUIMesh = std::map<std::string, AUIMesh>();

Core::AUIMesh::AUIMesh(std::string uid) : ABaseMesh(uid)
{

}

Core::AUIMesh::AUIMesh(std::string uid, std::vector<Vertex> vertices, std::vector<unsigned int> indices):ABaseMesh(uid)
{
	printf("add mesh %s \n", uid.c_str());
	id = uid;
	this->vertices = vertices;
	this->indices = indices;

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
}

void Core::AUIMesh::initEngine()
{
	std::vector<AUIMesh::Vertex> vertices;
	std::vector<unsigned int> indices;

	AUIMesh::Vertex vertex1;
	//vertex1.Position = Math::Vector3(-0.5f, -0.5f, 0);
	vertex1.Position = Math::Vector3(0.0f, 0.0f, 0);
	vertex1.TexCoords = Math::Vector2(0, 0);
	vertices.push_back(vertex1);

	AUIMesh::Vertex vertex2;
	vertex2.Position = Math::Vector3(1.0f, 0.0f, 0);
	vertex2.TexCoords = Math::Vector2(1, 0);
	vertices.push_back(vertex2);

	AUIMesh::Vertex vertex3;
	vertex3.Position = Math::Vector3(0.0f, 1.0f, 0);
	vertex3.TexCoords = Math::Vector2(0, 1);
	vertices.push_back(vertex3);

	AUIMesh::Vertex vertex4;
	vertex4.Position = Math::Vector3(1.0f, 1.0f, 0);
	vertex4.TexCoords = Math::Vector2(1, 1);
	vertices.push_back(vertex4);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	baseAUIMesh.insert(std::pair<std::string, AUIMesh>("base", AUIMesh("texture2d", vertices, indices)));
}
