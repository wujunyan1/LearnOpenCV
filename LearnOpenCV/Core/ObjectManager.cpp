#include "ObjectManager.h"

using namespace Core;

ObjectManager* ObjectManager::instance = nullptr;
unsigned int ObjectManager::_oid = 0;

GameObject* ObjectManager::createNewGameObject() {
	GameObject* obj = new GameObject();
	obj->id = _oid++;
	obj->autorelease();

	GetInstance()->AddObject(obj);

	return obj;
}

Object* ObjectManager::createNewObject() {
	Object* obj = new Object();
	obj->id = _oid++;
	obj->autorelease();

	GetInstance()->AddObject(obj);

	return obj;
}

Object* ObjectManager::createRootObject() {
	Object* obj = new Object();
	obj->id = _oid++;

	GetInstance()->AddRootObject(obj);

	return obj;
}

void ObjectManager::AddObject(Object* o)
{
	// o1->insert(std::pair<unsigned int, Object*>(o->GetId(), o));
}

void ObjectManager::AddRootObject(Object* o)
{
	roots->push_back(o);
}