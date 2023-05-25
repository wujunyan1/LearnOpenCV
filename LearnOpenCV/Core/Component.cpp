#include "Component.h"
#include "Object.h"
#include "GameObject.h"

using namespace Core;

void Component::Init()
{
}

void Component::OnDestroy()
{
}


void Component::setObject(Object* o) {
	object = o;
}

Object* Component::getObject() {
	return object;
}

GameObject* GameComponent::getGameObject() {
	return dynamic_cast<GameObject*>(object);
}