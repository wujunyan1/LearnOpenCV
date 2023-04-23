#include "RenderMain.h"
#include "RenderStage.h"
#include "../file/Image.h"

#include "../Core/Scene.h"
#include "../opengl/GLShaderManager.h"

#include "../render/RenderStage.h"
#include "../input/Input.h"

#include "../Core/GlobalDictionary.h"

#include "font/FontManager.h"

namespace Render 
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

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Math::Vector2T<int> size = { width, height };
		glViewport(0, 0, size.x, size.y);
		Core::GlobalDictionary::setRealWindowSize(size);
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


	long getCurrentRenderTime() {
		return clock();
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

	void BindArrayBufferData(unsigned int vbo, size_t dataSize, void* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	}

	void VertexAttribPointer(unsigned int passageway, size_t dataSize, ShaderParamType dataType, bool b, size_t delaySize, size_t startIndex)
	{
		glVertexAttribPointer(passageway, dataSize, GL_FLOAT, GL_FALSE, delaySize, (void*)startIndex);
		glEnableVertexAttribArray(passageway);
	}


	RenderProgram* CreateRenderProgram(std::string materialName)
	{
		RenderProgram* program = new RenderProgram();
		program->setMaterialName(materialName);
		return program;
	}

	Material* CreateMaterial(std::string materialName)
	{
		return new Material();
	}

	RenderMesh* CreateRenderMesh(std::string name)
	{
		return RenderMesh::createNewRenderMesh(name);
	}

	RenderMesh* GetRenderMesh(std::string name)
	{
		return RenderMesh::getRenderMesh(name);
	}

	unsigned int CreateShader(const std::string& shaderName, const std::string& vsPath, const std::string& fsPath)
	{
		return GLShaderManager::Instance()->GetShader(shaderName, vsPath, fsPath);
	}

	void AddCustomRenderQueue(const std::string& type, Render::RenderQueueManager::RenderCreator creator)
	{
		Render::RenderQueueManager::registerRenderQueueCreator(type, creator);
	}

	void RenderScene(Core::Scene* scene)
	{
		RenderStageManager::RenderScene(scene);
	}

	// 添加到渲染队列
	void AddRender(RenderProgram* renderProgram)
	{
		RenderStageManager::AddRenderProgram(renderProgram);
	}

	void AddUICanvas(UI::UICanvas* canvas)
	{
		RenderStageManager::AddRenderUI(canvas);
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

		glfwSetWindowSizeCallback(window, window_size_callback);

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

	bool ShouldCloseWindow()
	{
		return glfwWindowShouldClose(window);
	}

	void SetBackgroundColor(Math::Vector3 color)
	{
		GL_GET_ERROR(glDepthMask(GL_TRUE));
		GL_GET_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		//processInput(window);

		GL_GET_ERROR(glClearColor(color.x, color.y, color.z, 0.0));
		GL_GET_ERROR(glClear(GL_COLOR_BUFFER_BIT));
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

	void updateTextures(float delay)
	{
		FontManager::GetInstance()->checkCharacterTexture();
	}

	void BeforeRender()
	{
		return Render::RenderStageManager::beforeRender();
	}

	void Render()
	{
		Core::Scene* scene = Core::Scene::getCurrScene();

		std::vector<Core::Camera*>& cameras = scene->getRenderCameras();

		// 先渲染其他摄像机，在渲染主摄像机
		for (auto it = cameras.begin(); it != cameras.end(); it++)
		{
			Render::RenderStageManager::render(*it);
		}

		Render::RenderStageManager::render(scene->getMainCamera());
		return;
	}

	void RenderEnd()
	{
		Render::RenderStageManager::renderEnd();
		Render::RenderQueueManager::ClearRenderQueue();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}