#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/RenderMesh.h"
#include "../render/Texture.h"

namespace Core
{
	class AMesh
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
		AMesh(std::string uid, std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Render::Texture> textures)
		{
			printf("add mesh %s \n", uid.c_str());
			id = uid;
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
		std::string id;

		// mesh Data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		std::vector<Render::Texture> textures;

		Render::RenderMesh* mesh;
	};
}
