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
	class RenderObjMesh : public RenderBaseMesh
	{
	public:
		RenderObjMesh(std::string name);
		~RenderObjMesh();

		virtual void Render(Render::ShaderProgram* program, Render::Material* material);
	protected:
		
	};

}