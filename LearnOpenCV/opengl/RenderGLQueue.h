#pragma once

#include "OpenGLCore.h"
#include "../render/RenderQueue.h"
#include "ShaderGLProgram.h"

#include "MaterialGL.h"
#include "../render/RenderMesh.h"

namespace OpenGL
{
	class RenderGLProgram : public Render::RenderProgram
	{
	public:
		RenderGLProgram();

		Render::RenderMesh* createNewRenderMesh(std::string name = Math::stringFormat("renderMesh|%d",Math::getUid()));
		Render::RenderMesh* loadRenderMesh(std::string name, std::string path);
		
		void setShader(const std::string& shaderName);

		void Render();
		void RenderMesh(Render::RenderMesh* mesh);
	};

	class RenderGLQueue
	{
	public:
		RenderGLQueue(ShaderGLProgram* program);
		~RenderGLQueue();

		void Render();

		void addRenderProgram(RenderGLProgram* renderProgram);

		void clear();

	private:

		unsigned int index;

		// 这个队列的shader
		ShaderGLProgram* shaderProgram;

		// 激活的需要渲染的
		std::vector<RenderGLProgram*>* activeRenderProgram;
	};

}