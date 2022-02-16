#include "OpenGLMain.h"
#include "../render/RenderMain.h"
#include "OpenGLCore.h"
#include <GL/glew.h>

using namespace Render;

namespace OpenGL
{

	unsigned int CreateVBO()
	{
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		return VBO;
	}

	unsigned int CreateVAO()
	{
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		return VAO;
	}
	unsigned int CreateShader()
	{
		return 0;
	}

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		glVertexAttribPointer(passageway, dataSize, GL_FLOAT, GL_FALSE, delaySize, (void*)startIndex);
		glEnableVertexAttribArray(passageway);
	}

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}


	void RenderVBO(int vbo)
	{

	}

	RenderGLProgram * CreateRenderProgram(std::string materialName)
	{
		return new RenderGLProgram();
	}

	MaterialGL* CreateMaterial(std::string materialName)
	{
		return NULL;
	}

	// 添加到渲染队列
	void AddRenderQueue(RenderGLProgram* renderProgram)
	{

	}
}
