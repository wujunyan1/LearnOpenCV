#include "Component.h"
#include "Object.h"

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