#include "OpenGLMain.h"
#include "../render/RenderMain.h"
#include "OpenGLCore.h"
#include <GL/glew.h>
#include <direct.h>
#include "../file/FilePathManager.h"

#include "GLShaderManager.h"

using namespace Render;

namespace OpenGL
{
	unsigned int CreateVBO()
	{
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		return VBO;
	}

	unsigned int CreateVAO()
	{
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		return VAO;
	}
	unsigned int CreateShader()
	{
		return 0;
	}

	// vbo  通道  数据大小  单个数据大小  数据个数 数据
	void SetVertexAttribPointer(int vbo, int passageway, Render::ShaderParamType typeSize, size_t dataSize, size_t dataLength, void* data)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void VertexAttribPointer(unsigned int passageway, size_t dataSize, Render::ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		glVertexAttribPointer(passageway, dataSize, GL_FLOAT, GL_FALSE, delaySize, (void*)startIndex);
		glEnableVertexAttribArray(passageway);
	}

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}


	void RenderVBO(int vbo)
	{

	}

	RenderGLProgram * CreateRenderProgram(std::string materialName)
	{
		return new RenderGLProgram();
	}

	MaterialGL* CreateMaterial(std::string materialName)
	{
		return NULL;
	}

	// 添加到渲染队列
	void AddRenderQueue(RenderGLProgram* renderProgram)
	{
		RenderGLQueueManager::AddRenderQueue(renderProgram);
	}

	void InitEngine()
	{
		GLShaderManager::NewInstance();

		char buffer[64];
		char* c = _getcwd(buffer, 64);

		printf(c);
		FilePathManager::setRootPath(buffer);

		glfwInit();
		glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	int CreateWindow(int w, int h, std::string title)
	{
		window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
		if (window == NULL) {
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);

		glewExperimental = true;

		if (glewInit() != GLEW_OK) {
			glfwTerminate();
			return -1;
		}

		glViewport(0, 0, 1280, 720);
		//glEnable(GL_CULL_FACE);    // 剔除面
		//glCullFace(GL_BACK);       // 剔除背面
		glEnable(GL_DEPTH_TEST);

		return 0;
	}

	void ClearBuffer()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void SetBackgroundColor(Math::Vector3 color)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//processInput(window);

		glClearColor(color.x, color.y, color.z, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Render(float delay)
	{

	}

	void RenderEnd()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}
