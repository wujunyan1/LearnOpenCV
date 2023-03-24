#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "../file/Image.h"
#include "Texture.h"
#include "../opengl/OpenGLCore.h"
#include "../opengl/GLShader.h"
#include "../render/Material.h"
#include "RenderBaseMesh.h"

namespace Render
{
	/*
		mesh 数据，对应一个vbo
		顶点，uv，光照贴图 等等
	*/
	class RenderMesh : public RenderBaseMesh
	{
	public:
		RenderMesh(std::string& meshName) : RenderBaseMesh(meshName) {};

	public:
		static RenderMesh* createNewRenderMesh(std::string& meshName);
		static RenderMesh* getRenderMesh(std::string& meshName);
		static void addRenderMesh(std::string& meshName, RenderMesh* mesh);
		static RenderMesh* loadMeshFile(std::string& meshName, std::string& path);

	private:
		static std::map<std::string, RenderMesh*>* meshs;
	};

}