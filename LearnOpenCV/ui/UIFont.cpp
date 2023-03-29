#include "UIFont.h"
#include "UITransform.h"
#include "../meshModel/AUIMesh.h"

using namespace Core;
namespace UI
{
	UIFont::UIFont() : Component() {

		renderProgram = Render::CreateRenderProgram("test");
		renderProgram->setShader("uiShader");
		renderProgram->setRenderQueueName("RenderUIQueue");
		renderProgram->setRenderStage(2000);

		initModel();
	}

	void UI::UIFont::setText(std::string& text)
	{
		m_text = text;
		needUpdateMesh = true;
	}

	void UI::UIFont::setBlendFunc(Render::BlendFunc src, Render::BlendFunc target)
	{
		renderProgram->setBlendFunc(src, target);
	}

	void UI::UIFont::Render()
	{
		if (!b_isActive)
			return;

		if (needUpdateMesh)
		{
			updateMesh();
		}

		UITransform* transform = this->getObject()->GetComponent<UITransform>();

		Render::Material* material = renderProgram->getMaterial();

		Math::Vector3 color = Math::Vector3(0.0f, 0.3f, 0.6f);

		Math::Matrix4& mat4 = transform->GetRenderModelMat4();
		//renderProgram->setLocalToWorldMat4(mat4);
		material->setMat4("model", mat4);
		Render::AddRender(renderProgram);
	}


	void UIFont::initModel()
	{
		model = AModelFactory::createCustomModel();
		mesh = model->addBaseUIMesh("base");

		renderProgram->setModel(model);
	}

	void UIFont::updateMesh()
	{
		needUpdateMesh = false;


	}

}
