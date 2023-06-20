#include "RenderObjMesh.h"
#include "../render/Material.h"

namespace Render
{
	RenderObjMesh::RenderObjMesh(std::string name):RenderBaseMesh(name)
	{
	}

	RenderObjMesh::~RenderObjMesh()
	{
	}

	void RenderObjMesh::Render(Render::ShaderProgram* program, Render::Material* material)
	{
		/*if (m_name != "0|Visor")
		{
			return;
		}*/

		glBindVertexArray(tvao);

		unsigned int diffuseIndex = 0;
		unsigned int ambientIndex = 0;
		unsigned int specularIndex = 0;
		unsigned int normalIndex = 0;
		unsigned int heightIndex = 0;

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

		for (unsigned int i = 0; i < images.size(); i++)
		{
			Render::Texture& texture = images[i];

			//glActiveTexture(Core::Image::textureIndex[i]);
			int num = 0;
			if (texture.uniformName == "material.diffuse")
				num = diffuseIndex++;
			else if (texture.uniformName == "material.ambient")
				num = ambientIndex++;
			else if (texture.uniformName == "material.specular")
				num = specularIndex++;
			else if (texture.uniformName == "material.normal")
				num = normalIndex++;
			else if (texture.uniformName == "material.height")
				num = heightIndex++;

			std::string uniformName = texture.uniformName; // Math::stringFormat(texture.uniformName, num);
			//printf("RenderGLMesh::Render %d %s %s \n", i, uniformName.c_str(), texture.image->getName().c_str());

			glActiveTexture(Core::Image::textureIndex[i + index]);
			glBindTexture(GL_TEXTURE_2D, texture.image->getTextureId());
			shader->setTexture(uniformName, i + index);
			//glActiveTexture(Core::Image::textureIndex[i]);
			//texture.image->use(i);
			//glBindTexture(GL_TEXTURE_2D, texture.image->getTextureId());
			//printf("glBindTexture %s %d %u %s %s  \n", m_name.c_str(), i, texture.image->getTextureId(), uniformName.c_str(), texture.image->getName().c_str());
		}
		//printf(" draw mesh %s \n", m_name.c_str());
		glDrawElements(GL_TRIANGLES, verticesNum, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}