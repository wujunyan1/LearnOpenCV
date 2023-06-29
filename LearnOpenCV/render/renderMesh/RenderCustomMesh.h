#pragma once

#include <map>
#include "../math/Math.h"
#include "RenderBaseMesh.h"

namespace Render
{
	/*
		mesh ���ݣ���Ӧһ��vbo
		���㣬uv��������ͼ �ȵ�
	*/
	class RenderCustomMesh : public RenderBaseMesh
	{
	public:
		RenderCustomMesh(std::string name);
		~RenderCustomMesh();

		virtual void Render(Render::ShaderProgram* program, Render::Material* material);
		virtual void RenderInstances(Render::ShaderProgram* program, Render::Material* material, unsigned int count);

	protected:

	};

}