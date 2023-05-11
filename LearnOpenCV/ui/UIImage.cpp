#include "UIImage.h"
#include "UITransform.h"
#include "../meshModel/AUIMesh.h"
#include "../render/font/FontManager.h"

using namespace Core;
namespace UI
{
	UIImage::UIImage() : GameComponent() {

		renderProgram = Render::CreateRenderProgram("test");
		renderProgram->setShader("uiShader");
		renderProgram->setRenderQueueName("RenderUIQueue");
		renderProgram->setRenderStage(20000);

		renderProgram->setDepthTest(true);
		renderProgram->setBlend(true);
		renderProgram->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);

		initModel();
	}

	void UI::UIImage::setImage(std::string& name)
	{
		imageName = name;

		if (image)
		{
			ImageLoad::DestroyImage(image);
			image = nullptr;
		}
		image = ImageLoad::LoadImage(name);

		texture.image = image;
		texture.imageName = name;
		texture.uniformName = "texture2d";
		renderProgram->getMaterial()->setTexture("texture2d", texture);
	}

	void UI::UIImage::setBlendFunc(Render::BlendFunc src, Render::BlendFunc target)
	{
		renderProgram->setBlendFunc(src, target);
	}

	void UI::UIImage::Render()
	{
		if (!b_isActive)
			return;

		UITransform* transform = this->getObject()->GetComponent<UITransform>();

		Render::Material* material = renderProgram->getMaterial();

		Math::Vector3 color = Math::Vector3(0.0f, 0.3f, 0.6f);

		Math::Matrix4& mat4 = transform->GetRenderModelMat4();
		//renderProgram->setLocalToWorldMat4(mat4);
		material->setMat4("model", mat4);

		//Math::Vector4 showpos1 = Math::Vector4(1, 1, 1, 1);
		//printf("========uiimage::render========");
		//printf("%s \n", showpos1.toString().c_str());

		//float left = 0.0f;
		//float right = 1280.0f;
		//float top = 720.0f;
		//float bottom = 0.0f;
		//float near = -1.0f;
		//float far = 1.0f;

		//glm::ortho(left, right, bottom, top, near, far);

		//Mat4 ortho = Mat4(1);
		//ortho.m00 = (1.0f) / (right - left);
		//ortho.m11 = (1.0f) / (top - bottom);
		//ortho.m22 = -(2.0f) / (far - near);
		///*ortho.m30 = -(right + left) / (right - left);
		//ortho.m31 = -(top + bottom) / (top - bottom);
		//ortho.m32 = -(far + near) / (far - near);*/

		//mat4.printMat4();


		//showpos1 = mat4 * Math::Vector4(0.5, 0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());
		//showpos1 = mat4 * Math::Vector4(-0.5, 0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());
		//showpos1 = mat4 * Math::Vector4(-0.5, -0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());
		//showpos1 = mat4 * Math::Vector4(0.5, -0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());
		//printf("================= \n");

		//showpos1 = ortho * mat4 * Math::Vector4(0.5, 0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());
		//showpos1 = ortho * mat4 * Math::Vector4(-0.5, 0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());
		//showpos1 = ortho * mat4 * Math::Vector4(-0.5, -0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());
		//showpos1 = ortho * mat4 * Math::Vector4(0.5, -0.5, 0, 1);
		//printf("%s \n", showpos1.toString().c_str());

		Render::AddRender(renderProgram);
	}

	void UIImage::initModel()
	{
		//std::vector<AUIMesh::Vertex> vertices;
		//std::vector<unsigned int> indices;

		//AUIMesh::Vertex vertex1;
		////vertex1.Position = Math::Vector3(-0.5f, -0.5f, 0);
		//vertex1.Position = Math::Vector3(0.0f, 0.0f, 0);
		//vertex1.TexCoords = Math::Vector2(0, 0);
		//vertices.push_back(vertex1);

		//AUIMesh::Vertex vertex2;
		//vertex2.Position = Math::Vector3(1.0f, 0.0f, 0);
		//vertex2.TexCoords = Math::Vector2(1, 0);
		//vertices.push_back(vertex2);

		//AUIMesh::Vertex vertex3;
		//vertex3.Position = Math::Vector3(0.0f, 1.0f, 0);
		//vertex3.TexCoords = Math::Vector2(0, 1);
		//vertices.push_back(vertex3);

		//AUIMesh::Vertex vertex4;
		//vertex4.Position = Math::Vector3(1.0f, 1.0f, 0);
		//vertex4.TexCoords = Math::Vector2(1, 1);
		//vertices.push_back(vertex4);

		//indices.push_back(0);
		//indices.push_back(1);
		//indices.push_back(2);
		//indices.push_back(2);
		//indices.push_back(1);
		//indices.push_back(3);

		//AUIMesh& mesh = AUIMesh::getBaseAUIMesh("base"); // AUIMesh("texture2d", vertices, indices);

		Render::FontSource* source = Render::FontManager::getFontSource("/asserts/fonts/DroidSans.ttf");

		texture.image = source->getImage(); // ImageLoad::LoadImage("/asserts/images/blending_transparent_window.png");
		texture.imageName = "blending_transparent_window.png";
		texture.uniformName = "texture2d";
		renderProgram->getMaterial()->setTexture("texture2d", texture);

		model = AModelFactory::createCustomModel();
		model->addBaseUIMesh("base");

		renderProgram->setModel(model);
	}

}
