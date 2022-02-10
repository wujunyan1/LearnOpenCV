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

	// vbo  ͨ��  ���ݴ�С  �������ݴ�С  ���ݸ��� ����
	void SetVertexAttribPointer(int vbo, int passageway, ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data);


	void RenderVBO(int vbo);

	RenderProgram* CreateRenderProgram(std::string materialName);

	Material* CreateMaterial(std::string materialName);

	// ��ӵ���Ⱦ����
	void AddRenderQueue(Material* material);

}