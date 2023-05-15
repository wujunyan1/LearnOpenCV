#include "Game.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "Transform.h"
#include "Model.h"
#include "SceneManager.h"

#include <stdio.h>

#include "TestComponent.h"
#include "ShowFpsComponent.h"

#include "../render/RenderMain.h"
#include "../meshModel/AModel.h"
#include "../logic/renderQueue/RenderOpaqueQueue.h"

#include "../file/ImageLoad.h"

#include "../Core/AutoreleasePool.h"
#include "GlobalDictionary.h"

#include "../ui/UICanvas.h"
#include "../ui/UIImage.h"
#include "../ui/UIFont.h"
#include "../ui/UITransform.h"
#include "../render/RenderUIQueue.h"

#include "../meshModel/AUIMesh.h"

#include "../lua/LuaRegister.h"

using namespace Core;

Game* Game::instance = nullptr;

Game::Game()
{
	delay = 0.0f;
	GlobalDictionary::initGame();
	LuaRegister::GetInstance();
}

Game::~Game()
{
	ImageLoad::Destroy();
	GlobalDictionary::destroyGame();
	LuaRegister::DestroyInstance();
}

void Game::Tick(long time)
{
	delay = time;

	PoolManager::getInstance()->getCurrentPool()->clear();

	Scene* currScene = SceneManager::GetInstance()->GetCurrScene();

	currScene->PreUpdate();
	currScene->Update();
	currScene->LaterUpdate();
}


void Game::LoadMainScene()
{
	Render::CreateShader("defaultShader", "/asserts/shaders/shader.vert", "/asserts/shaders/shader.frag");
	Render::CreateShader("testShader", "/asserts/shaders/testShader.vert", "/asserts/shaders/testShader.frag");
	Render::CreateShader("testBlendShader", "/asserts/shaders/testBlendShader.vert", "/asserts/shaders/testBlendShader.frag");
	Render::CreateShader("skyBoxShader", "/asserts/shaders/skyBoxShader.vert", "/asserts/shaders/skyBoxShader.frag");
	Render::CreateShader("uiShader", "/asserts/shaders/uiShader.vert", "/asserts/shaders/uiShader.frag");
	Render::CreateShader("fontShader", "/asserts/shaders/fontShader.vert", "/asserts/shaders/fontShader.frag");

	Render::AddCustomRenderQueue("RenderOpaqueQueue", Core::new_class<Logic::RenderOpaqueQueue>());
	Render::AddCustomRenderQueue("DefaultRenderQueue", Core::new_class<Render::RenderQueue>());
	Render::AddCustomRenderQueue("RenderUIQueue", Core::new_class<Render::RenderUIQueue>());

	Scene* root = SceneManager::GetInstance()->GetCurrScene();
	/*scene->PreUpdate();
	scene->Update();
	scene->LaterUpdate();*/


	GameObject* o = ObjectManager::createNewGameObject();
	root->AddChild(o);
	Transform* t = o->AddComponent<Transform>();
	Model* model = o->AddComponent<Model>();
	t->SetPosition(Math::Vector3(0.0f, 0.0f, -0.9f));
	Core::AModel* amodel = AModelFactory::createModel("/asserts/mesh/juren/nanosuit.obj");
	model->setModel(amodel);
	model->setDepthTest(true);
	model->setBlend(false);


	GameObject* eggObj = ObjectManager::createNewGameObject();
	root->AddChild(eggObj);

	Transform* eggTransform = eggObj->AddComponent<Transform>();
	Model* eggModel = eggObj->AddComponent<Model>();
	eggTransform->SetPosition(Math::Vector3(0.0f, 0.0f, -6.9f));
	eggTransform->SetScale(Math::Vector3(0.03f, 0.03f, 0.03f));
	Core::AModel* eggAModel = AModelFactory::createModel("/asserts/mesh/unicorn/unicorn.glb");
	eggModel->setModel(eggAModel);
	eggModel->setDepthTest(true);
	eggModel->setBlend(false);


	for (size_t i = 0; i < 0; i++)
	{
		GameObject* o2 = ObjectManager::createNewGameObject();
		Transform* t2 = o2->AddComponent<Transform>();
		Model* mesh2 = o2->AddComponent<Model>();

		root->AddChild(o2);

		int x = rand() % 10 + 1;
		int y = rand() % 10 + 1;
		int z = rand() % 10 + 1;
		t2->SetPosition(Math::Vector3(x, y, -z));

		int roll = rand() % 6;
		int yaw = rand() % 6;
		int pitch = rand() % 6;
		t2->SetRotate(Vector3(pitch, yaw, roll));

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

		// TextureFromFile(str.C_Str(), this->directory);

		Render::Texture texture;
		texture.image = ImageLoad::LoadImage("/asserts/images/blending_transparent_window.png");
		texture.imageName = "blending_transparent_window.png";
		texture.uniformName = "material.ambient";
		textures.push_back(texture);

		Render::Texture texture2;
		texture2.image = ImageLoad::LoadImage("/asserts/images/blending_transparent_window.png");
		texture2.imageName = "blending_transparent_window.png";
		texture2.uniformName = "material.diffuse";
		textures.push_back(texture2);

		Core::AModel* acustommodel = AModelFactory::createCustomModel();
		acustommodel->addMesh(vertices, indices, textures);

		mesh2->setShader("testBlendShader");  //testBlendShader
		mesh2->setRenderQueue("DefaultRenderQueue");
		mesh2->setModel(acustommodel);
		mesh2->setDepthTest(false);
		mesh2->setBlend(true);
		mesh2->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
		//mesh2->setBlendFunc(Render::BlendFunc::ONE, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
	}

	for (size_t i = 0; i < 0; i++)
	{
		GameObject* o2 = ObjectManager::createNewGameObject();
		Transform* t2 = o2->AddComponent<Transform>();
		Model* mesh2 = o2->AddComponent<Model>();

		root->AddChild(o2);

		int x = rand() % 10 + 1;
		int y = rand() % 10 + 1;
		int z = rand() % 10 + 1;
		t2->SetPosition(Math::Vector3(x, y, -z));

		int roll = rand() % 6;
		int yaw = rand() % 6;
		int pitch = rand() % 6;
		t2->SetRotate(Vector3(pitch, yaw, roll));

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

		// TextureFromFile(str.C_Str(), this->directory);

		Render::Texture texture;
		texture.image = ImageLoad::LoadImage("/asserts/images/img_0_eff_bd.png");
		texture.imageName = "img_0_eff_bd.png";
		texture.uniformName = "material.ambient";
		textures.push_back(texture);

		Render::Texture texture2;
		texture2.image = ImageLoad::LoadImage("/asserts/images/img_0_eff_bd.png");
		texture2.imageName = "img_0_eff_bd.png";
		texture2.uniformName = "material.diffuse";
		textures.push_back(texture2);

		Core::AModel* acustommodel = AModelFactory::createCustomModel();
		acustommodel->addMesh(vertices, indices, textures);

		mesh2->setShader("testBlendShader");  //testBlendShader
		mesh2->setRenderQueue("DefaultRenderQueue");
		mesh2->setRenderStageIndex(20000);
		mesh2->setModel(acustommodel);
		mesh2->setDepthTest(false);
		mesh2->setBlend(true);
		mesh2->setBlendFunc(Render::BlendFunc::SRC_ALPHA, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
		//mesh2->setBlendFunc(Render::BlendFunc::ONE, Render::BlendFunc::ONE_MINUS_SRC_ALPHA);
	}


	GameObject* uiBase = ObjectManager::createNewGameObject();
	UI::UITransform* baseTransform = uiBase->AddComponent<UI::UITransform>();
	uiBase->AddComponent<UI::UICanvas>();
	root->AddChild(uiBase);
	//uiBase->AddComponent<UI::UIImage>();

	GameObject* showUI = ObjectManager::createNewGameObject();
	UI::UITransform* uiTransform = showUI->AddComponent<UI::UITransform>();
	UI::UIImage* uiImage = showUI->AddComponent<UI::UIImage>();

	uiTransform->SetPosition({ {1, -400} ,{1, 0} });
	uiTransform->SetSize({ {0, 800}, {0, 100} });
	uiBase->AddChild(showUI);

	GameObject* showFont = ObjectManager::createNewGameObject();
	UI::UITransform* uiFontTransform = showFont->AddComponent<UI::UITransform>();
	UI::UIFont* uiFont = showFont->AddComponent<UI::UIFont>();
	uiFont->setText("fps : 60");
	uiFont->setColor({ 1.0, 0.0, 0.0 });

	uiFontTransform->SetPosition({ {0, 0} ,{0, 0} });
	uiFontTransform->SetPivot({ 0, 0 });
	uiFontTransform->SetSize({ {0, 200}, {0, 100} });

	showFont->AddComponent<Core::ShowFpsComponent>();

	uiBase->AddChild(showFont);
}

void Core::Game::InitEngine()
{
	AUIMesh::initEngine();
}
