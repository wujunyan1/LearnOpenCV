#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "../file/Image.h"
#include "Texture.h"

namespace Render
{
	/*
		mesh ���ݣ���Ӧһ��vbo
		���㣬uv��������ͼ �ȵ�
	*/
	class RenderMesh
	{
	public:
		RenderMesh(std::string _name);
		RenderMesh(std::string _name, void* data);

		std::string& getName() { return name; };

		virtual void BindArrayBufferData(size_t verticesNum, size_t dataSize, void* data);
		virtual void BindElementBufferData(size_t dataSize, void* data) {};
		virtual void VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);

		virtual void SetImage(std::vector<Texture>& images) {};
		virtual void Render(ShaderProgram* program) {};
	protected:
		std::string name;
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