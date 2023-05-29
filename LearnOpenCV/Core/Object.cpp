#include "Object.h"
#include "ObjectManager.h"

using namespace Core;

Object* Core::Object::clone()
{
    Object* object = ObjectManager::createNewObject();

	for (Component* component : *componentList)
	{
		object->AddComponent(component->clone());
	}

    return nullptr;
}
