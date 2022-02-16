#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"

namespace Render
{
	/*
		mesh 数据，对应一个vbo
		顶点，uv，光照贴图 等等
	*/
	class RenderMesh
	{
	public:
		RenderMesh(std::string _name);
		RenderMesh(std::string _name, void* data);

		virtual void BindArrayBufferData(size_t dataSize, void* data);
		virtual void VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);

	protected:
		std::string name;
		unsigned int vbo;


	};

	class RenderMeshManager
	{
	public:
		static RenderMesh* createNewRenderMesh(std::string meshName);
		static RenderMesh* getRenderMesh(std::string meshName);
		static void addRenderMesh(std::string meshName, RenderMesh* mesh);
		static void loadMeshFile(std::string meshName, std::string path);

	private:
		static std::map<std::string, RenderMesh*>* meshs;
	};
}