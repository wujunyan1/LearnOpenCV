#include "RenderSkyBox.h"
#include "../opengl/GLShaderManager.h"

#include "../opengl/OpenGLCore.h"

using namespace Render;



Render::RenderSkyBox::RenderSkyBox()
{
	skyboxShader = Render::GLShaderManager::Instance()->GetShaderObj("skyBoxShader");

	GL_GET_ERROR(glGenVertexArrays(1, &skyboxVAO));
	GL_GET_ERROR(glGenBuffers(1, &skyboxVBO));
	GL_GET_ERROR(glGenBuffers(1, &skyboxEBO));

	GL_GET_ERROR(glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO));
	GL_GET_ERROR(glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), skyboxVertices, GL_STATIC_DRAW));

	GL_GET_ERROR(glBindVertexArray(skyboxVAO));
	GL_GET_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO));
	GL_GET_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), skyboxIndices, GL_STATIC_DRAW));

	GL_GET_ERROR(glEnableVertexAttribArray(0));
	GL_GET_ERROR(glVertexAttribPointer(0, 3, Render::GET_OPENGL_TYPE(Render::ShaderParamType::SPT_VEC3), GL_FALSE, 3 * sizeof(float), (void*)0));
}

RenderSkyBox::~RenderSkyBox()
{
}

void Render::RenderSkyBox::render(Core::Camera* renderCamera)
{
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	skyboxShader->use();

	Math::Matrix4 view = Math::Matrix4(Math::Matrix3(renderCamera->getViewMat4()));
	skyboxShader->setMat4("view", view);
	skyboxShader->setMat4("proj", renderCamera->getPerspectiveMat4());


	// ... 设置观察和投影矩阵
	glBindVertexArray(skyboxVAO);
	m_image->use(0);
	skyboxShader->setTexture("skybox", 0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);
}
