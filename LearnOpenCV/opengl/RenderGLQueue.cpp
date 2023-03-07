#include "RenderGLQueue.h"
#include "../render/RenderMesh.h"
#include "MaterialGL.h"

#include "OpenGLMain.h"

namespace OpenGL
{
	RenderGLProgram::RenderGLProgram(): Render::RenderProgram()
	{
		material = new MaterialGL();
	}

	Render::RenderMesh* RenderGLProgram::createNewRenderMesh(std::string name)
	{
		Render::RenderMesh* mesh = Render::RenderMeshManager::createNewRenderMesh(name);
		return mesh;
	}

	Render::RenderMesh* RenderGLProgram::loadRenderMesh(std::string name, std::string path)
	{
		Render::RenderMesh* mesh = Render::RenderMeshManager::loadMeshFile(name, path);
		return mesh;
	}

	void RenderGLProgram::setShader(const std::string& shaderName)
	{
		shaderProgram = ShaderGLProgram::GetShaderGLProgram(shaderName);
	}

	void RenderGLProgram::Render()
	{
		if (_model == nullptr)
		{
			return;
		}

		GL_GET_ERROR(glDepthMask(depthTest ? GL_TRUE : GL_FALSE));                                                       //�ص���Ȳ���
		
		if (blend) {
			GL_GET_ERROR(glEnable(GL_BLEND));	//�����ģʽ��ͼ 
		}
		else{
			GL_GET_ERROR(glDisable(GL_BLEND));
		} 
		GL_GET_ERROR(glBlendFunc((int)srcBlendFunc, (int)targetBlendFunc));                           //���û�Ϸ�ʽ 

		// ����shader ����
		shaderProgram->RenderMaterial(material);
		// ��Ⱦvao
		std::vector<Core::AMesh>& ameshs = _model->getMeshs();

		for (size_t i = 0; i < ameshs.size(); i++)
		{
			Core::AMesh& mesh = ameshs[i];
			mesh.getRenderMesh()->Render(shaderProgram);
		}
	}

	void RenderGLProgram::RenderMesh(Render::RenderMesh* mesh)
	{
		// ����shader ����
		shaderProgram->RenderMaterial(material);
		mesh->Render(shaderProgram);
	}


	RenderGLQueue::RenderGLQueue(ShaderGLProgram* program)
	{
		index = 0;
		shaderProgram = program;
		activeRenderProgram = new std::vector<RenderGLProgram*>();
	}

	RenderGLQueue::~RenderGLQueue()
	{
		delete activeRenderProgram;
	}

	void RenderGLQueue::Render()
	{
		// ʹ��ĳShader
		shaderProgram->Use();

		for (size_t i = 0; i < index; i++)
		{
			RenderGLProgram* program = (RenderGLProgram*)activeRenderProgram->at(i);
			program->Render();
		}
	}

	void RenderGLQueue::addRenderProgram(RenderGLProgram* renderProgram)
	{
		if (activeRenderProgram->size() <= index)
		{
			activeRenderProgram->push_back(renderProgram);
			index++;
		}
		else
		{
			activeRenderProgram->at(index) = renderProgram;
			index++;
		}
	}

	void RenderGLQueue::clear()
	{
		index = 0;
	}
}