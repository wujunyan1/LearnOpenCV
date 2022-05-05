#include "RenderGLQueue.h"
#include "RenderGLMesh.h"
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
		RenderGLMesh* mesh = RenderGLMeshManager::createNewRenderMesh(name);
		addMesh(mesh);
		return mesh;
	}

	Render::RenderMesh* RenderGLProgram::loadRenderMesh(std::string name, std::string path)
	{
		RenderGLMesh* mesh = RenderGLMeshManager::loadMeshFile(name, path);
		addMesh(mesh);
		return mesh;
	}

	void RenderGLProgram::addModel(Core::AModel* model)
	{
		std::vector<Core::AMesh>& ameshs = model->getMeshs();

		for (auto mesh : ameshs)
		{
			addMesh(mesh.getRenderMesh());
		}
	}

	void RenderGLProgram::setShader(const std::string& shaderName)
	{
		shaderProgram = ShaderGLProgram::GetShaderGLProgram(shaderName);
	}

	void RenderGLProgram::Render()
	{
		if (meshs == nullptr)
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
		for (auto mesh : *meshs)
		{
			mesh->Render(shaderProgram);
		}
	}

	void RenderGLProgram::RenderMesh(RenderGLMesh* mesh)
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