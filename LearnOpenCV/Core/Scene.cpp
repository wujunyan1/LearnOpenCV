#include "Scene.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"
#include "TestComponent.h"
#include "CameraMoveComponent.h"

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

	Math::Vector2T<int> size = Render::GetWindowSize();

	camera->init(Math::radians(45.0f), size.x * 1.0f / size.y, 0.1f, 100.0f);
	transform->AddChild(cameraT);
	cameraT->SetPosition({0, 0, 0});

	cameraObj->AddComponent<CameraMoveComponent>();

	//o2->AddComponent<TestComponent>();
}