#include "RenderMain.h"
#include "RenderStage.h"


#if SHADER_PLAFORM==SHADER_PLAFORM_GL
#include "../opengl/OpenGLMain.h"
#endif

namespace Render 
{
	long getCurrentRenderTime() {
		return clock();
	}

	unsigned int CreateVBO()
	{
	return OpenGL::CreateVBO();
	}

	unsigned int CreateVAO()
	{
	return OpenGL::CreateVAO();
	}

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
	{
		return OpenGL::SetVertexAttribPointer(vbo, passageway, typeSize, dataSize, dataLength, data);
	}

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data)
	{
		return OpenGL::BindArrayBufferData(vbo, dataSize, data);
	}

	void VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		return OpenGL::VertexAttribPointer(passageway, dataSize, dataType, b, delaySize, startIndex);
	}


	void RenderVBO(int vbo)
	{
		return OpenGL::RenderVBO(vbo);
	}

	RenderProgram* CreateRenderProgram(std::string materialName)
	{
		return OpenGL::CreateRenderProgram(materialName);
	}

	Material* CreateMaterial(std::string materialName)
	{
		return OpenGL::CreateMaterial(materialName);
	}

	RenderMesh* CreateRenderMesh(std::string name)
	{
		return OpenGL::CreateRenderMesh(name);
	}

	RenderMesh* GetRenderMesh(std::string name)
	{
		return OpenGL::GetRenderMesh(name);
	}

	unsigned int CreateShader(const std::string& shaderName, const std::string& vsPath, const std::string& fsPath)
	{
		return OpenGL::CreateShader(shaderName, vsPath, fsPath);
	}

	void AddCustomRenderQueue(const std::string& type, Render::RenderQueueManager::RenderCreator creator)
	{
		Render::RenderQueueManager::registerRenderQueueCreator(type, creator);
	}

	// 添加到渲染队列
	void AddRender(RenderProgram* renderProgram)
	{
		RenderStageManager::AddRenderProgram(renderProgram);
		// RenderQueueManager::AddRenderQueue(renderProgram);
	}

	void InitEngine()
	{
		return OpenGL::InitEngine();
	}

	int CreateWindow(int w, int h, std::string title)
	{
		return OpenGL::CreateWindow(w, h, title);
	}

	Math::Vector2T<int> GetWindowSize()
	{
		return OpenGL::GetWindowSize();
	}

	void ClearBuffer()
	{
		return OpenGL::ClearBuffer();
	}

	Core::Image* CreateImage(int width, int height, int nrChannels, unsigned char* data)
	{
		return OpenGL::CreateImage(width, height, nrChannels, data);
	}

	bool ShouldCloseWindow()
	{
		return OpenGL::ShouldCloseWindow();
	}

	void SetBackgroundColor(Math::Vector3 color)
	{
		return OpenGL::SetBackgroundColor(color);
	}

	unsigned int CreateNewFramebuffer()
	{
		unsigned int fbo;
		glGenFramebuffers(1, &fbo);
		return fbo;
	}

	void BindFramebuffer(unsigned int fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	void BeforeRender(float delay)
	{
		return OpenGL::BeforeRender(delay);
	}

	void Render(float delay)
	{
		return OpenGL::Render(delay);
	}

	void RenderEnd()
	{
		return OpenGL::RenderEnd();
	}
}