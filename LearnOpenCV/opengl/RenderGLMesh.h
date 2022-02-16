#pragma once

#include "OpenGLCore.h"
#include "../render/RenderMesh.h"

namespace OpenGL
{
	class RenderGLMesh: public Render::RenderMesh
	{
	public:
		RenderGLMesh(std::string name);
		~RenderGLMesh();


		void BindArrayBufferData(size_t dataSize, void* data);
		void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);
	private:

	};
}