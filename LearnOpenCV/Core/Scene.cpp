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
	t->SetPosition(Math::Vector3(1.0f, 0.2f, 3.0f));

	mesh->addTriangle(
		Math::Triangle<Math::Vector3>(
			Math::Vector3(0.0, 0, 0),
			Math::Vector3(0.3, 0, 0),
			Math::Vector3(0.0, 0.6, 0)
		),
		Math::Triangle<Math::Vector4>(
			Math::Vector4(0, 0, 1, 1),
			Math::Vector4(1, 0, 0, 1),
			Math::Vector4(0, 1, 0, 1)
		)
	);

	o->AddComponent<TestComponent>();


	Object* o2 = ObjectManager::createNewObject();
	Transform* t2 = o2->AddComponent<Transform>();
	Mesh* mesh2 = o2->AddComponent<Mesh>();

	transform->AddChild(t2);
	t2->SetPosition(Math::Vector3(0.8f, 0.2f, 2.0f));

	mesh2->addTriangle(
		Math::Triangle<Math::Vector3>(
			Math::Vector3(0.0, 0, 0),
			Math::Vector3(0.3, 0, 0),
			Math::Vector3(0.0, 0.6, 0)
			),
		Math::Triangle<Math::Vector4>(
			Math::Vector4(1, 1, 1, 1),
			Math::Vector4(1, 1, 0, 1),
			Math::Vector4(1, 1, 0, 1)
			)
	);

	o2->AddComponent<TestComponent>();
}