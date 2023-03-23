#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/RenderMesh.h"
#include "../render/Texture.h"
#include "ABaseMesh.h"

namespace Core
{
	class AUIMesh: public ABaseMesh
	{
		friend class AModel;
	public:
		struct Vertex {
			// position
			Math::Vector3 Position;
			// texCoords
			Math::Vector2 TexCoords;
		};

	public:
		AUIMesh(std::string uid, std::vector<Vertex> vertices, std::vector<unsigned int> indices);

		virtual int getMeshType() { return AUIMesh::MeshType; };

		Render::RenderMesh* getRenderMesh() 
		{
			return mesh;
		};

	private:

		void bindRender();

	private:
		std::string id;

		// mesh Data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;

		Render::RenderMesh* mesh;

	public:
		const static int MeshType = 2;
	};
}
