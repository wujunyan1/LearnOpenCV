#include "ObjectManager.h"

using namespace Core;

ObjectManager* ObjectManager::instance = nullptr;
unsigned int ObjectManager::_oid = 0;

Object* ObjectManager::createNewObject() {
	Object* obj = new Object(_oid++);

	GetInstance()->AddObject(obj);

	return obj;
}

Object* ObjectManager::createRootObject() {
	Object* obj = new Object(_oid++);

	GetInstance()->AddObject(obj);

	return obj;
}

void ObjectManager::AddObject(Object* o)
{
	o1->insert(std::pair<unsigned int, Object*>(o->GetId(), o));
}

void ObjectManager::AddRootObject(Object* o)
{
	roots->push_back(o);
}