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

		AMesh& mesh = model->getMesh("texture2d");

		std::vector<Render::Texture> textures;
		Render::Texture texture;
		texture.image = image;
		texture.imageName = "blending_transparent_window.png";
		texture.uniformName = "texture2d";
		textures.push_back(texture);
		mesh.updateTexture(textures);
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

	void UIImage::initModel()
	{
		std::vector<AMesh::Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Render::Texture> textures;

		AMesh::Vertex vertex1;
		vertex1.Position = Math::Vector3(-0.5f, -0.5f, 0);
		vertex1.TexCoords = Math::Vector2(0, 0);
		vertex1.Normal = Math::Vector3(0, 0, 1.0f);
		vertex1.Tangent = Math::Vector3(0, 0, 0);
		vertex1.Bitangent = Math::Vector3(0, 0, 0);
		vertices.push_back(vertex1);

		AMesh::Vertex vertex2;
		vertex2.Position = Math::Vector3(0.5f, -0.5f, 0);
		vertex2.TexCoords = Math::Vector2(1, 0);
		vertex2.Normal = Math::Vector3(0, 0, 1.0f);
		vertex2.Tangent = Math::Vector3(0, 0, 0);
		vertex2.Bitangent = Math::Vector3(0, 0, 0);
		vertices.push_back(vertex2);

		AMesh::Vertex vertex3;
		vertex3.Position = Math::Vector3(-0.5f, 0.5f, 0);
		vertex3.TexCoords = Math::Vector2(0, 1);
		vertex3.Normal = Math::Vector3(0, 0, 1.0f);
		vertex3.Tangent = Math::Vector3(0, 0, 0);
		vertex3.Bitangent = Math::Vector3(0, 0, 0);
		vertices.push_back(vertex3);

		AMesh::Vertex vertex4;
		vertex4.Position = Math::Vector3(0.5f, 0.5f, 0);
		vertex4.TexCoords = Math::Vector2(1, 1);
		vertex4.Normal = Math::Vector3(0, 0, 1.0f);
		vertex4.Tangent = Math::Vector3(0, 0, 0);
		vertex4.Bitangent = Math::Vector3(0, 0, 0);
		vertices.push_back(vertex4);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(2);
		indices.push_back(1);
		indices.push_back(3);

		Render::Texture texture;
		texture.image = ImageLoad::LoadImage("/asserts/images/blending_transparent_window.png");
		texture.imageName = "blending_transparent_window.png";
		texture.uniformName = "texture2d";
		textures.push_back(texture);

		model = AModelFactory::createCustomModel();
		model->addMesh("texture2d", vertices, indices, textures);

		renderProgram->setModel(model);
	}

}
