#pragma once

#include <map>
#include <time.h>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderQueue.h"
#include "../file/Image.h"


#define SHADER_PLAFORM_CV 1
#define SHADER_PLAFORM_GL 2

#ifndef SHADER_PLAFORM
#define SHADER_PLAFORM SHADER_PLAFORM_GL
#endif

#if SHADER_PLAFORM==SHADER_PLAFORM_GL
#define SHADER_FLOAT GL_FLOAT
#endif

namespace Render
{
	unsigned int CreateVBO();
	unsigned int CreateVAO();

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data);
	void VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);


	void RenderVBO(int vbo);

	RenderProgram* CreateRenderProgram(std::string materialName);

	Material* CreateMaterial(std::string materialName);
	RenderMesh* CreateRenderMesh(std::string name = Math::getUid());

	unsigned int CreateShader(const std::string& shaderName, const std::string& vsPath, const std::string& fsPath);

	// 添加到渲染队列
	void AddRenderQueue(RenderProgram* renderProgram);

	long getCurrentRenderTime();

	void InitEngine();
	int CreateWindow(int w, int h, std::string title);
	Math::Vector2T<int> GetWindowSize();
	void ClearBuffer();

	Core::Image* CreateImage(int width, int height, int nrChannels, unsigned char* data);

	bool ShouldCloseWindow();
	void SetBackgroundColor(Math::Vector3 color);

	void Render(float delay);
	void RenderEnd();
}