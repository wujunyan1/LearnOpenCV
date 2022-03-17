#include "Game.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "Transform.h"
#include "Model.h"
#include "SceneManager.h"

#include <stdio.h>

#include "TestComponent.h"
#include "../render/RenderMain.h"
#include "../meshModel/AModel.h"

using namespace Core;

Game* Game::instance = nullptr;

void Game::Tick(long time)
{
	delay = time;

	Scene* currScene = SceneManager::GetInstance()->GetCurrScene();
	Object* o = currScene->getObject();

	o->PreUpdate();
	o->Update();
	o->LaterUpdate();
}


void Game::Render(long time)
{
	Scene* currScene = SceneManager::GetInstance()->GetCurrScene();
	Object* o = currScene->getObject();

	o->Render();
}

void Game::LoadMainScene()
{
	Render::CreateShader("defaultShader", "/asserts/shaders/shader.vert", "/asserts/shaders/shader.frag");
	Render::CreateShader("testShader", "/asserts/shaders/testShader.vert", "/asserts/shaders/testShader.frag");

	Scene* scene = SceneManager::GetInstance()->GetCurrScene();
	scene->PreUpdate();
	scene->Update();
	scene->LaterUpdate();

	Core::Transform* root = scene->getObject()->GetComponent<Core::Transform>();



	Object* o = ObjectManager::createNewObject();
	Transform* t = o->AddComponent<Transform>();
	Model* model = o->AddComponent<Model>();

	root->AddChild(t);
	t->SetPosition(Math::Vector3(0.0f, 0.0f, -0.9f));
	// t->SetScale(Vector3(0.8f, 0.2f, 0.2f));

	/*model->addTriangle(
		Math::Triangle<Math::Vector3>(
			Math::Vector3(0.0f, 0, 0),
			Math::Vector3(0.5f, 0.0f, 0),
			Math::Vector3(0.0, 0.5f, 0)
			),
		Math::Triangle<Math::Vector4>(
			Math::Vector4(0, 0, 1, 1),
			Math::Vector4(1, 0, 0, 1),
			Math::Vector4(0, 1, 0, 1)
			)
	);
	model->bindRender();*/

	Transform* camerat = root->GetChildByIndex(0);
	//camerat->getObject()->AddComponent<TestComponent>();

	o->AddComponent<TestComponent>();

	// AModel* amodel = new AModel("/asserts/mesh/juren/nanosuit.obj");
	Core::AModel* amodel = AModelFactory::createModel("/asserts/mesh/juren/nanosuit.obj");
	model->setModel(amodel);


	for (size_t i = 0; i < 1000; i++)
	{
		Object* ro = ObjectManager::createNewObject();
		Transform* rt = ro->AddComponent<Transform>();
		Model* model = ro->AddComponent<Model>();
		model->setModel(amodel);
		root->AddChild(rt);

		int x = rand() % 20 + 1;
		int y = rand() % 20 + 1;
		int z = rand() % 20 + 1;
		rt->SetPosition(Math::Vector3(x, y, -z));

		int roll = rand() % 6;
		int yaw = rand() % 6;
		int pitch = rand() % 6;
		rt->SetRotate(Vector3(pitch, yaw, roll));

		ro->AddComponent<TestComponent>();
	}

	/*Object* o2 = ObjectManager::createNewObject();
	Transform* t2 = o2->AddComponent<Transform>();
	Mesh* mesh2 = o2->AddComponent<Mesh>();

	root->AddChild(t2);
	t2->SetPosition(Math::Vector3(0.0f, -0.2f, 1.1f));

	mesh2->addTriangle(
		Math::Triangle<Math::Vector3>(
			Math::Vector3(-0.3f, 0, 0),
			Math::Vector3(0.3f, 0, 0),
			Math::Vector3(0.0, 0.6f, 0)
			),
		Math::Triangle<Math::Vector4>(
			Math::Vector4(1, 1, 0, 1),
			Math::Vector4(1, 1, 0, 1),
			Math::Vector4(1, 1, 0, 1)
			)
	);
	mesh2->bindRender();*/
}