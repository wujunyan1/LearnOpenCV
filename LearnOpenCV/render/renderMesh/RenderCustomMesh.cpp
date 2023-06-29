#include "RenderCustomMesh.h"
#include "../render/Material.h"

namespace Render
{
	RenderCustomMesh::RenderCustomMesh(std::string name):RenderBaseMesh(name)
	{
	}

	RenderCustomMesh::~RenderCustomMesh()
	{
	}

	void RenderCustomMesh::Render(Render::ShaderProgram* program, Render::Material* material)
	{
		/*if (m_name != "0|Visor")
		{
			return;

			glGetProgramiv(m_hProgram, GL_ACTIVE_UNIFORMS, &activeUniformLength);
			glGetActiveUniform(m_hProgram, i, 512, &uniformLength, &uniformSize, &uniformType, unifromName)

		}*/

		glBindVertexArray(tvao);

		//printf(" draw mesh %s \n", m_name.c_str());
		GL_GET_ERROR(glDrawElements(GL_TRIANGLES, verticesNum, GL_UNSIGNED_INT, 0));
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	void RenderCustomMesh::RenderInstances(Render::ShaderProgram* program, Render::Material* material, unsigned int count)
	{
		glBindVertexArray(tvao);
		GL_GET_ERROR(glDrawElementsInstanced(GL_TRIANGLES, verticesNum, GL_UNSIGNED_INT, 0, count));
		glBindVertexArray(0);
	}
}