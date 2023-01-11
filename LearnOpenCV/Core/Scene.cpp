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
	cameras = std::vector<Camera*>();
}

void Scene::Bind()
{
	Transform* transform = this->getObject()->GetComponent<Transform>();

	Object* cameraObj = ObjectManager::createNewObject();
	Transform* cameraT = cameraObj->AddComponent<Transform>();
	mainCamera = cameraObj->AddComponent<Camera>();

	Math::Vector2T<int> size = Render::GetWindowSize();

	mainCamera->init(Math::radians(45.0f), size.x * 1.0f / size.y, 0.1f, 100.0f);
	transform->AddChild(cameraT);
	cameraT->SetPosition({0, 0, 0});

	cameraObj->AddComponent<CameraMoveComponent>();

	cameras.push_back(mainCamera);

	//o2->AddComponent<TestComponent>();
}