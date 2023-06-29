#pragma once
#include "../math/Math.h"
#include "../file/Image.h"
#include "../render/renderMesh/RenderCustomMesh.h"
#include "../render/Texture.h"
#include "ABaseMesh.h"

namespace Core
{
	class AWarMapMesh : public ABaseMesh
	{
		friend class AModel;
	public:

	public:
		AWarMapMesh(std::string uid);
		~AWarMapMesh();

		virtual int getMeshType() { return ABaseMesh::MeshType::WarMapMesh; };

		void SetRenderMesh(Render::RenderBaseMesh* renderMesh);

		virtual void render(Render::ShaderProgram* program, Render::Material* material);

		Render::Material* getCustomMaterial();

	private:


	private:
		// Render::RenderCustomMesh* mesh;
		Render::Material* customMaterial;
	public:
	};
}
