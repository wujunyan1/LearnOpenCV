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

Component* Core::Component::clone()
{
	return new Component();
}


GameObject* GameComponent::getGameObject() {
	return dynamic_cast<GameObject*>(object);
}

Component* Core::GameComponent::clone()
{
	return new GameComponent();
}
