#include "Scene.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "TestComponent.h"

#include "../math/Math.h"

using namespace Core;

Scene* Scene::currScene = nullptr;

Scene::Scene() 
{
	currScene = this;
}

void Scene::Bind()
{
	Transform* transform = this->getObject()->GetComponent<Transform>();

	Object* cameraObj = ObjectManager::createNewObject();
	Transform* cameraT = cameraObj->AddComponent<Transform>();
	camera = cameraObj->AddComponent<Camera>();
	camera->init(Math::radians(45.0f), 1280.0f / 720, 0.1f, 100.0f);
	transform->AddChild(cameraT);
	cameraT->SetPosition({0, 0, 0});

	//o2->AddComponent<TestComponent>();
}