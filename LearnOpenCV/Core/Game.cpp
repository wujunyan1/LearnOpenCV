#include "Game.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "Transform.h"
#include "Mesh.h"
#include "SceneManager.h"

#include <stdio.h>

#include "TestComponent.h"
#include "../render/RenderMain.h"

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
	Mesh* mesh = o->AddComponent<Mesh>();

	root->AddChild(t);
	t->SetPosition(Math::Vector3(0.0f, -0.2f, 1.0f));
	t->SetScale(Vector3(0.2f, 0.2f, 0.2f));

	mesh->addTriangle(
		Math::Triangle<Math::Vector3>(
			Math::Vector3(-0.3f, 0, 0),
			Math::Vector3(0.3f, 0.1f, 0),
			Math::Vector3(0.0, 0.6f, 0)
			),
		Math::Triangle<Math::Vector4>(
			Math::Vector4(0, 0, 1, 1),
			Math::Vector4(1, 0, 0, 1),
			Math::Vector4(0, 1, 0, 1)
			)
	);
	mesh->bindRender();

	o->AddComponent<TestComponent>();


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