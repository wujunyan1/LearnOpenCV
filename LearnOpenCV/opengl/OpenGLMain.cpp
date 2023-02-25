#include "OpenGLMain.h"
#include "../render/RenderMain.h"
#include "OpenGLCore.h"
#include <GL/glew.h>
#include <direct.h>
#include "../file/FilePathManager.h"

#include "GLShaderManager.h"
#include "GLImage.h"

#include "../render/RenderStage.h"
#include "../input/Input.h"

#include "../Core/Scene.h"

using namespace Render;

namespace OpenGL
{

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		/*if (action != GLFW_PRESS)
			return;
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		default:
			break;
		}*/

		if (action == GLFW_PRESS)
			Core::Input::PressKey((Core::Input::Key)key);
		else if (action == GLFW_RELEASE)
			Core::Input::ReleaseKey((Core::Input::Key)key);
	}

	void mouse_enter_callback(GLFWwindow* window, int index)
	{

	}

	void mouse_pos_callback(GLFWwindow* window, double x, double y)
	{
		Core::Input::UpdateMousePosition(Math::Vector2(x, y));
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
			Core::Input::PressKey((Core::Input::Key)button);
		else if (action == GLFW_RELEASE)
			Core::Input::ReleaseKey((Core::Input::Key)button);
	}


	void checkGLError(const char* message)
	{
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			const char* errorName = toGLErrorString(error);
			printf("GLError [%x] %s: %s", error, errorName, message);
		}
	}

	void checkGLError(const char* file, int line)
	{
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			const char* errorName = toGLErrorString(error);
			printf("GLError [%x] %s %s, line %d \n", error, errorName, file, line);
		}
	}

	const char* toGLErrorString(GLenum error)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:                  return "INVALID_ENUM";
		case GL_INVALID_VALUE:                 return "INVALID_VALUE";
		case GL_INVALID_OPERATION:             return "INVALID_OPERATION";
		case GL_STACK_OVERFLOW:                return "STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW:               return "STACK_UNDERFLOW";
		case GL_OUT_OF_MEMORY:                 return "OUT_OF_MEMORY";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
		default:                               return "UNKNOWN_ERR";
		}
	}



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
		RenderGLProgram* program = new RenderGLProgram();
		program->setMaterialName(materialName);
		return program;
	}

	MaterialGL* CreateMaterial(std::string materialName)
	{
		return new MaterialGL();
	}

	RenderGLMesh* CreateRenderMesh(std::string& name)
	{
		return RenderGLMeshManager::createNewRenderMesh(name);;
	}

	RenderGLMesh* GetRenderMesh(std::string& name)
	{
		return RenderGLMeshManager::getRenderMesh(name);
	}

	unsigned int CreateShader(const std::string& shaderName, const std::string& vsPath, const std::string& fsPath)
	{
		return GLShaderManager::Instance()->GetShader(shaderName, vsPath, fsPath);
	}

	void InitEngine()
	{
		GLShaderManager::NewInstance();

		glfwInit();
		glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSwapInterval(0);
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

		glViewport(0, 0, w, h);
		//glEnable(GL_CULL_FACE);    // 剔除面
		//glCullFace(GL_BACK);       // 剔除背面
		glEnable(GL_DEPTH_TEST);

		// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    // 鼠标箭头隐藏

		glfwSetCursorEnterCallback(window, mouse_enter_callback);
		glfwSetCursorPosCallback(window, mouse_pos_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetKeyCallback(window, key_callback);


		return 0;
	}

	Math::Vector2T<int> GetWindowSize()
	{
		int w, h;
		glfwGetWindowSize(window, &w, &h);

		return Math::Vector2T<int>(w, h);
	}

	void ClearBuffer()
	{
		/*glfwPollEvents();
		glfwSwapBuffers(window);*/
	}

	Core::Image* CreateImage(int width, int height, int nrChannels, unsigned char* data)
	{
		return new GLImage(width, height, nrChannels, data);
	}

	bool ShouldCloseWindow()
	{
		return glfwWindowShouldClose(window);
	}

	void SetBackgroundColor(Math::Vector3 color)
	{
		GL_GET_ERROR(glDepthMask(GL_TRUE));
		GL_GET_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		//processInput(window);

		GL_GET_ERROR(glClearColor(color.x, color.y, color.z, 1.0));
		GL_GET_ERROR(glClear(GL_COLOR_BUFFER_BIT));
	}

	void BeforeRender(float delay)
	{
		Render::RenderStageManager::beforeRender();
	}

	void Render(float delay)
	{
		// Render::RenderStageManager::render();

		Core::Scene* scene = Core::Scene::getCurrScene();
		Render::RenderStageManager::render(scene->getMainCamera());

		//Render::RenderQueueManager::RenderQueue();
	}

	void RenderEnd()
	{
		Render::RenderStageManager::renderEnd();

		Render::RenderQueueManager::ClearRenderQueue();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void BindFramebuffer(unsigned int fbo)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}
}
