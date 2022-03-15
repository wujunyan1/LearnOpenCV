#pragma once
#include "../math/Math.h"
#include "../render/RenderMain.h"


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

		struct Texture {
			Core::Image* image;
			std::string type;
			std::string path;
		};
	public:
		AMesh();

		AMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;
		}

	private:

		void bindRender();

	private:
		// mesh Data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture>      textures;
	};
}
