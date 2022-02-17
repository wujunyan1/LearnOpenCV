#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderMesh.h"

namespace Render
{
	class RenderProgram
	{
	public:
		RenderProgram();

		void setVBO(unsigned int _vbo) { vbo = _vbo; }
		unsigned int getVBO() { return vbo; }

		RenderMesh* createNewRenderMesh(std::string name);
		RenderMesh* loadRenderMesh(std::string name, std::string path = "");

		RenderMesh* getMesh() { return mesh; }

		ShaderProgram* getShaderProgram() { return shaderProgram; }
		Material* getMaterial() { return material; }

		virtual void Render() {};
	protected:
		unsigned int vbo;

		ShaderProgram* shaderProgram;

		Material* material;

		RenderMesh* mesh;
	};


	class RenderQueue
	{
	public:
		RenderQueue() {
			shaderProgram = NULL;
			activeRenderProgram = new std::vector<RenderProgram*>();
		}

		virtual void Render() {};

		void addRenderProgram(RenderProgram* renderProgram) 
		{
			activeRenderProgram->push_back(renderProgram);
		}
	protected:

		// 这个队列的shader
		ShaderProgram* shaderProgram;

		// 激活的需要渲染的
		std::vector<RenderProgram*>*	activeRenderProgram;
	};

	class RenderQueueManager
	{
	public:
		static void AddRenderQueue(RenderProgram* renderProgram);

	private:
		static std::map<unsigned int, RenderQueue*>* queues;
	};
}