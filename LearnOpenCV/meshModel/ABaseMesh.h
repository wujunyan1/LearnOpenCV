#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/RenderMesh.h"
#include "../render/Texture.h"

namespace Core
{
	class ABaseMesh
	{
		friend class AModel;
	public:

	public:
		ABaseMesh(std::string uid);

		virtual int getMeshType() { return 0; };

		virtual Render::RenderBaseMesh* getRenderMesh()
		{
			return mesh;
		};

	protected:
		std::string id;

		// mesh Data
		/*std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		std::vector<Render::Texture> textures;*/

		Render::RenderBaseMesh* mesh;
	};
}
