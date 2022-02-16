#include "RenderGLMesh.h"

namespace OpenGL
{
	RenderGLMesh::RenderGLMesh(std::string name) : Render::RenderMesh(name)
	{
		glGenBuffers(1, &vbo);
	}
	RenderGLMesh::~RenderGLMesh()
	{
	}
	void RenderGLMesh::BindArrayBufferData(size_t dataSize, void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void RenderGLMesh::VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(passageway, dataSize, GL_FLOAT, GL_FALSE, delaySize, (void*)startIndex);
		glEnableVertexAttribArray(passageway);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}