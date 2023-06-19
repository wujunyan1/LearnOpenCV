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

		GLShader* shader = program->GetShaderObj();

		std::vector<Render::Texture>& textures = material->getShaderTextures();
		int index = 0;
		for (Render::Texture texture : textures)
		{
			int textureIndex = index++;
			//texture.image->use(textureIndex);
			glActiveTexture(Core::Image::textureIndex[textureIndex]);
			glBindTexture(GL_TEXTURE_2D, texture.image->getTextureId());
			shader->setTexture(texture.uniformName, textureIndex);
		}

		
		//printf(" draw mesh %s \n", m_name.c_str());
		glDrawElements(GL_TRIANGLES, verticesNum, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}