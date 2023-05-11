#include "UIFont.h"
#include "UITransform.h"
#include "../meshModel/AUIMesh.h"
#include "../render/font/FontManager.h"

using namespace Core;
namespace UI
{
	UIFont::UIFont() : GameComponent() {

		renderProgram = Render::CreateRenderProgram("test");
		renderProgram->setShader("fontShader");
		renderProgram->setRenderQueueName("RenderUIQueue");
		renderProgram->setRenderStage(20000);

		renderProgram->setDepthTest(true);
		renderProgram->setBlend(true);
		renderProgram->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);

		initModel();
	}

	void UI::UIFont::setText(std::string text)
	{
		m_text = text;

		Render::FontSource* source = Render::FontManager::getFontSource(m_font);

		for (size_t i = 0; i < m_text.size(); ++i)
		{
			char c = m_text[i];
			source->getChar(c);
		}

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

		// 字体 默认 不受uisize影响
		Math::Matrix4& mat4 = transform->GetLocalToWorldMat4();
		//renderProgram->setLocalToWorldMat4(mat4);
		material->setMat4("model", mat4);
		material->setVec3("textColor", m_color);

		Render::FontSource* source = Render::FontManager::getFontSource(m_font);
		unsigned int uvx = source->getImageWidth();
		unsigned int uvy = 3 * source->getFontSize();

		material->setVec2("imageUV", 1.0f, 1.0f);

		Render::AddRender(renderProgram);
	}


	void UIFont::initModel()
	{
		model = AModelFactory::createCustomModel();
		mesh = model->addBaseUIMesh("base");

		renderProgram->setModel(model);

		Render::Material* material = renderProgram->getMaterial();

		Render::FontSource* source = Render::FontManager::getFontSource(m_font);
		material->clearTexture();
		texture.image = source->getImage();  //ImageLoad::LoadImage("/asserts/images/blending_transparent_window.png"); // source->getImage();
		texture.imageName = "screenTexture";
		texture.uniformName = "screenTexture";
		material->setTexture("screenTexture", texture);
	}

	void UIFont::updateMesh()
	{
		needUpdateMesh = false;

		Render::FontSource* source = Render::FontManager::getFontSource(m_font);

		std::vector<Core::AUIMesh::Vertex> vertices;
		std::vector<unsigned int> indices;

		float scale = m_fontSize / 48.0f;
		float x = 0;

		float uvx = 1.0f / source->getImageWidth();
		float uvy = 1.0f / (3 * source->getFontSize());

		for (size_t i = 0; i < m_text.size(); ++i)
		{
			char c = m_text[i];
			Render::FontSource::Character ch = source->getChar(c);
			unsigned int charInterval = source->getFontSize();

			float xpos = x + ch.Bearing.x * scale;
			float ypos = (ch.Size.y - ch.Bearing.y) * scale;

			float uvw = ch.uv;
			float uvwx = (ch.uv + ch.Size.x );
			float uvwy = ch.Size.y;

			//printf("char mesh %c uv %f y %f \n", c, ch.uv * uvx, (ch.uv + ch.Size.x) * uvx);

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// 对每个字符更新VBO
			Core::AUIMesh::Vertex vertex1;
			vertex1.Position = Math::Vector3(xpos, -ypos + h, 0);
			vertex1.TexCoords = Math::Vector2(uvw * uvx, 0);
			vertices.push_back(vertex1);

			Core::AUIMesh::Vertex vertex2;
			vertex2.Position = Math::Vector3(xpos, -ypos, 0);
			vertex2.TexCoords = Math::Vector2(uvw * uvx, uvwy * uvy);
			vertices.push_back(vertex2);

			Core::AUIMesh::Vertex vertex3;
			vertex3.Position = Math::Vector3(xpos + w, -ypos, 0);
			vertex3.TexCoords = Math::Vector2(uvwx * uvx, uvwy * uvy);
			vertices.push_back(vertex3);

			Core::AUIMesh::Vertex vertex4;
			vertex4.Position = Math::Vector3(xpos + w, -ypos + h, 0);
			vertex4.TexCoords = Math::Vector2(uvwx * uvx, 0);
			vertices.push_back(vertex4);

			int index = i * 4;
			indices.push_back(index + 0);
			indices.push_back(index + 1);
			indices.push_back(index + 2);
			indices.push_back(index + 0);
			indices.push_back(index + 2);
			indices.push_back(index + 3);

			/*float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};*/

			x += (ch.Advance >> 6) * scale;
		}

		mesh->updateMesh(vertices, indices);
	}

}
