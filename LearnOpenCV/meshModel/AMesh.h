#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/RenderMesh.h"

namespace Core
{
	class AMesh
	{
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
		AMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Core::Image*> textures)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;

			bindRender();
		}

		Render::RenderMesh* getRenderMesh() 
		{
			return mesh;
		};

	private:

		void bindRender();

	private:
		// mesh Data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		std::vector<Core::Image*> textures;

		Render::RenderMesh* mesh;
	};
}
