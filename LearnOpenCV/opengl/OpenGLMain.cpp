#include "OpenGLMain.h"
#include "../render/RenderMain.h"
#include "OpenGLCore.h"

using namespace Render;

namespace OpenGL
{
	
}

unsigned int Render::CreateVBO()
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	return VBO;
}

unsigned int Render::CreateVAO()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	return VAO;
}
unsigned int Render::CreateShader()
{
	return 0;
}

// vbo  通道  数据大小  单个数据大小  数据个数 数据
void Render::SetVertexAttribPointer(int vbo, int passageway, ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Render::VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
{
	glVertexAttribPointer(passageway, dataSize, GL_FLOAT, GL_FALSE, delaySize, (void*)startIndex);
	glEnableVertexAttribArray(passageway);
}

void Render::BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}


void Render::RenderVBO(int vbo)
{

}

RenderProgram* Render::CreateRenderProgram(std::string materialName)
{

}

Material* Render::CreateMaterial(std::string materialName)
{

}

// 添加到渲染队列
void Render::AddRenderQueue(Material* material)
{

}