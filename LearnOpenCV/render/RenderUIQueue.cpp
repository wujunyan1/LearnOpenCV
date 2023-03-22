#include "RenderUIQueue.h"
#include "../ui/UICanvas.h"

namespace Render
{
	RenderUIQueue::RenderUIQueue() : Render::RenderQueue()
	{
		activeRenderUI = new std::vector<UI::UICanvas*>();

		float left = 0.0f;
		float right = 1280.0f;
		float top = 0.0f;
		float bottom = 720.0f;
		float near = -1.0f;
		float far = 1.0f;

		ortho = Mat4(1);
		ortho.m00 = (2.0f) / (right - left);
		ortho.m11 = (2.0f) / (top - bottom);
		ortho.m22 = -(2.0f) / (far - near);
		/*ortho.m30 = -(right + left) / (right - left);
		ortho.m31 = -(top + bottom) / (top - bottom);
		ortho.m32 = -(far + near) / (far - near);*/
	}

	RenderUIQueue::~RenderUIQueue()
	{
		delete activeRenderUI;
		activeRenderUI = nullptr;
	}

	void RenderUIQueue::Render(Core::Camera* camera)
	{
		// Ê¹ÓÃÄ³Shader
		shaderProgram->Use();
		shaderProgram->setMat4("VP", ortho); //camera->getOrthogonalMat4()

		Mat4 VP = camera->getOrthogonalMat4();

		for (size_t i = 0; i < index; i++)
		{
			Render::RenderProgram* program = activeRenderProgram->at(i);
			program->Render();

			Render::Material* material = program->getMaterial();
			const void* data = material->getData("model");
			Mat4 model = *(Mat4*)data;

			Vector4 showPos1 = model * Vector4(1, 1, 1, 1);
			Vector4 showPos2 = ortho * model * Vector4(1, 1, 0, 1);
			printf("================");
			ortho.printMat4();

			glm::mat4 ortho = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
			printf("|-------------|\n");
			printf("| %f %f %f %f |\n", ortho[0][0], ortho[0][1], ortho[0][2], ortho[0][3]);
			printf("| %f %f %f %f |\n", ortho[1][0], ortho[1][1], ortho[1][2], ortho[1][3]);
			printf("| %f %f %f %f |\n", ortho[2][0], ortho[2][1], ortho[2][2], ortho[2][3]);
			printf("| %f %f %f %f |\n", ortho[3][0], ortho[3][1], ortho[3][2], ortho[3][3]);
			printf("|-------------|\n");

			printf("%s \n", showPos1.toString().c_str());
			printf("%s \n", showPos2.toString().c_str());
		}
	}

	void RenderUIQueue::addRenderCanvas(UI::UICanvas* canvas)
	{
		if (activeRenderUI->size() <= index)
		{
			activeRenderUI->push_back(canvas);
			index++;
		}
		else
		{
			activeRenderUI->at(index) = canvas;
			index++;
		}
	}

	void RenderUIQueue::clear()
	{
		index = 0;
	}
}