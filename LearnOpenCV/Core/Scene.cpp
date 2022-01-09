#include "Scene.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"

#include "../math/Math.h"

using namespace Core;

Scene::Scene() 
{
	
}

void Scene::Bind()
{
	Object* o = ObjectManager::createNewObject();

	Transform* t = o->AddComponent<Transform>();
	o->AddComponent<Camera>();
	Mesh* mesh = o->AddComponent<Mesh>();

	Transform* transform = this->getObject()->GetComponent<Transform>();
	transform->AddChild(t);

	mesh->addTriangle(
		Math::Triangle(
			Math::Vector3(0, 0, 0),
			Math::Vector3(10, 0, 0),
			Math::Vector3(0, 10, 0)
		)
	);
}