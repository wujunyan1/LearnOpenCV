#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/renderMesh/RenderMesh.h"
#include "../render/Texture.h"
#include "ABaseMesh.h"

namespace Core
{
	class AMesh : public ABaseMesh
	{
		friend class AModel;
	public:
		struct Vertex {
			// position
			Math::Vector3 Position;
			// normal
			Math::Vector3 Normal;
			// texCoords
			Math::Vector2 TexCoords;
			// tangent
			Math::Vector3 Tangent;
			// bitangent
			Math::Vector3 Bitangent;
		};

	public:
		AMesh(std::string uid, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures);

		virtual int getMeshType() { return ABaseMesh::MeshType::Mesh; };

		void updateTexture(std::vector<Render::Texture> textures)
		{
			this->textures = textures;
			bindRender();
		}

		std::vector<Vertex>& getVertices() { return vertices; };

	private:

		virtual void bindRender();

	private:
		// mesh Data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		std::vector<Render::Texture> textures;

		Render::RenderMesh* mesh;

	public:
		const static int MeshType = 1;

	};
}
