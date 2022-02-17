#pragma once

#include "OpenGLCore.h"
#include "RenderGLMesh.h"
#include "MaterialGL.h"
#include "RenderGLQueue.h"

namespace OpenGL
{

	unsigned int CreateVBO();
	unsigned int CreateVAO();
	unsigned int CreateShader();

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data);
	void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);


	void RenderVBO(int vbo);

	RenderGLProgram* CreateRenderProgram(std::string materialName);

	MaterialGL* CreateMaterial(std::string materialName);

	// 添加到渲染队列
	void AddRenderQueue(RenderGLProgram* renderProgram);

	void InitEngine();
	int CreateWindow(int w, int h, std::string title);
	void ClearBuffer();

	void SetBackgroundColor(Math::Vector3 color);
	void Render(float delay);
	void RenderEnd();

	static GLFWwindow* window = NULL;
}