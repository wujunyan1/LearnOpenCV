#pragma once

#include "OpenGLCore.h"
#include "RenderGLMesh.h"
#include "MaterialGL.h"
#include "RenderGLQueue.h"


namespace OpenGL
{
	void checkGLError(const char* message);
	void checkGLError(const char* file, int line);
	const char* toGLErrorString(GLenum error);

	#define GL_GET_ERROR(x)do {x; OpenGL::checkGLError(__FILE__, __LINE__);}while(false)

	unsigned int CreateVBO();
	unsigned int CreateVAO();

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data);
	void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);


	void RenderVBO(int vbo);

	RenderGLProgram* CreateRenderProgram(std::string materialName);

	MaterialGL* CreateMaterial(std::string materialName);

	unsigned int CreateShader(const std::string& shaderName, const std::string& vsPath, const std::string& fsPath);


	// 添加到渲染队列
	void AddRenderQueue(RenderGLProgram* renderProgram);

	void InitEngine();
	int CreateWindow(int w, int h, std::string title);
	void ClearBuffer();

	bool ShouldCloseWindow();

	void SetBackgroundColor(Math::Vector3 color);
	void Render(float delay);
	void RenderEnd();

	static GLFWwindow* window = NULL;
}