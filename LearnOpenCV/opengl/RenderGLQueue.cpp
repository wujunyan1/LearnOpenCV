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

		GL_GET_ERROR(glDepthMask(depthTest ? GL_TRUE : GL_FALSE));                                                       //关掉深度测试
		
		if (blend) {
			GL_GET_ERROR(glEnable(GL_BLEND));	//开混合模式贴图 
		}
		else{
			GL_GET_ERROR(glDisable(GL_BLEND));
		} 
		GL_GET_ERROR(glBlendFunc((int)srcBlendFunc, (int)targetBlendFunc));                           //设置混合方式 

		// 设置shader 属性
		shaderProgram->RenderMaterial(material);
		// 渲染vao
		std::vector<Core::AMesh>& ameshs = _model->getMeshs();

		for (size_t i = 0; i < ameshs.size(); i++)
		{
			Core::AMesh& mesh = ameshs[i];
			mesh.getRenderMesh()->Render(shaderProgram);
		}
	}

	void RenderGLProgram::RenderMesh(Render::RenderMesh* mesh)
	{
		// 设置shader 属性
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
		// 使用某Shader
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