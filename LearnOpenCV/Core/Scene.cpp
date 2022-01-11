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


	Object* o = ObjectManager::createNewObject();
	Transform* t = o->AddComponent<Transform>();
	Mesh* mesh = o->AddComponent<Mesh>();

	transform->AddChild(t);
	t->SetPosition(Math::Vector3(0.0, 0, 3.0f));

	mesh->addTriangle(
		Math::Triangle(
			Math::Vector3(0.0, 0, 0),
			Math::Vector3(0.1, 0, 0),
			Math::Vector3(0.0, 0.3, 0)
		),
		Math::Triangle(
			Math::Vector3(0, 0, 1),
			Math::Vector3(1, 0, 0),
			Math::Vector3(0, 1, 0)
		)
	);

	o->AddComponent<TestComponent>();
}