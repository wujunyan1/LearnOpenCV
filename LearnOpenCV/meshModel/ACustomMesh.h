#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/renderMesh/RenderCustomMesh.h"
#include "../render/Texture.h"
#include "ABaseMesh.h"

namespace Core
{
	class ACustomMesh : public ABaseMesh
	{
		friend class AModel;
	public:

	public:
		ACustomMesh(std::string uid);

		virtual int getMeshType() { return ABaseMesh::MeshType::CustomMesh; };

		void BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data);
		void BindElementBufferData(std::vector<unsigned int> indices);
		void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);

		void setImage(std::vector<Render::Texture> textures);

	private:


	private:
		Render::RenderCustomMesh* mesh;

	public:
	};
}
