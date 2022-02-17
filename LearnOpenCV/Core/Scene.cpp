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
	camera->init(45, 1.2f, 0.1f, 100);
	transform->AddChild(cameraT);

	//o2->AddComponent<TestComponent>();
}