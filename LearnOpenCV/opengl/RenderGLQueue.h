#pragma once

#include "OpenGLCore.h"
#include "../render/RenderQueue.h"
#include "ShaderGLProgram.h"

namespace OpenGL
{
	class RenderGLProgram : public Render::RenderProgram
	{
	public:
		RenderGLProgram();

		Render::RenderMesh* createNewRenderMesh(std::string name);
		Render::RenderMesh* loadRenderMesh(std::string name, std::string path);

		void setShader(const std::string& shaderName);

		void Render();
	};

	class RenderGLQueue
	{
	public:
		RenderGLQueue(ShaderGLProgram* program);
		~RenderGLQueue();

		void Render();

		void addRenderProgram(RenderGLProgram* renderProgram)
		{

			if (activeRenderProgram->size() <= index)
			{
				activeRenderProgram->push_back(renderProgram);
				index++;
			}
			else
			{
				//activeRenderProgram->at(index) = renderProgram;
				activeRenderProgram->assign(index, renderProgram);
				index++;
			}
		}

		void clear()
		{
			index = 0;
		}

	private:

		unsigned int index;

		// 这个队列的shader
		ShaderGLProgram* shaderProgram;

		// 激活的需要渲染的
		std::vector<RenderGLProgram*>* activeRenderProgram;
	};

	class RenderGLQueueManager
	{
	public:
		static void AddRenderQueue(RenderGLProgram* renderProgram);

		static void RenderQueue();

	private:
		static std::map<unsigned int, RenderGLQueue*>* queues;
	};

}