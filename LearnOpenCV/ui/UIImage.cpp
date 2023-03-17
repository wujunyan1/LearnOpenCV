#include "UIImage.h"
#include "UITransform.h"

using namespace Core;
namespace UI
{
	UIImage::UIImage() : Component() {

		renderProgram = Render::CreateRenderProgram("test");
		renderProgram->setShader("testShader");
		renderProgram->setRenderQueueName("RenderUIQueue");
		renderProgram->setRenderStage(2000);
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

		Math::Matrix4& mat4 = transform->GetLocalToWorldMat4();
		renderProgram->setLocalToWorldMat4(mat4);
		material->setMat4("model", mat4);


		Render::AddRender(renderProgram);
	}

}
