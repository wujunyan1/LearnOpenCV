#pragma once

#include <map>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderQueue.h"

namespace Render
{
	int CreateVBO();
	int CreateVAO();
	int CreateShader();

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);


	void RenderVBO(int vbo);

	RenderProgram* CreateRenderProgram(std::string materialName);

	Material* CreateMaterial(std::string materialName);

	// 添加到渲染队列
	void AddRenderQueue(Material* material);

}