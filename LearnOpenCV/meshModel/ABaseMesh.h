#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/renderMesh/RenderMesh.h"
#include "../render/Texture.h"

namespace Core
{
	class ABaseMesh
	{
		friend class AModel;
	public:

		enum MeshType
		{
			Mesh,
			UIMesh,
			CustomMesh,
		};

	public:
		ABaseMesh(std::string uid);

		std::string getId()
		{
			return id;
		};

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
