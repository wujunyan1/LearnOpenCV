#pragma once

#include <map>
#include <time.h>
#include "../math/Math.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "RenderQueue.h"
#include "../file/Image.h"
#include "RenderSkyBox.h"
#include "../ui/UICanvas.h"

#include "../opengl/OpenGLCore.h"

#define SHADER_PLAFORM_GL 1
#define SHADER_PLAFORM SHADER_PLAFORM_GL
#define SHADER_FLOAT GL_FLOAT



namespace Render
{

	unsigned int CreateVBO();
	unsigned int CreateVAO();

	// vbo  通道  数据大小  单个数据大小  数据个数 数据

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data);
	void VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex);

	RenderProgram* CreateRenderProgram(std::string materialName);

	Material* CreateMaterial(std::string materialName);
	RenderMesh* CreateRenderMesh(std::string name = Math::stringFormat("renderMesh|%d", Math::getUid()));
	RenderMesh* GetRenderMesh(std::string name);

	unsigned int CreateShader(const std::string& shaderName, const std::string& vsPath, const std::string& fsPath);

	void AddCustomRenderQueue(const std::string& type, Render::RenderQueueManager::RenderCreator creator);

	// 添加到渲染队列
	void RenderScene(Core::Scene* scene);
	void AddRender(RenderProgram* renderProgram);
	void AddUICanvas(UI::UICanvas* canvas);
	void AddLight();

	long getCurrentRenderTime();

	void InitEngine();
	int CreateWindow(int w, int h, std::string title);
	Math::Vector2T<int> GetWindowSize();
	void ClearBuffer();

	bool ShouldCloseWindow();
	void SetBackgroundColor(Math::Vector3 color);

	unsigned int CreateNewFramebuffer();
	void BindFramebuffer(unsigned int fbo);

	void updateTextures(float delay);
	void BeforeRender();
	void Render();
	void RenderEnd();

	template<typename T>
	void AddCustomRenderQueue(std::string& name)
	{
		RenderQueueManager::registerRenderQueueCreator(name, T);
	}


	static GLFWwindow* window = NULL;
}