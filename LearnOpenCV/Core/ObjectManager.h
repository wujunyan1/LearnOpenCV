#pragma once
#include "Core.h"
#include "Object.h"
#include "GameObject.h"

namespace Core 
{
	class ObjectManager
	{
	public:
		static ObjectManager* GetInstance() {
			if (instance == nullptr) {
				instance = new ObjectManager();
			}
			return instance;
		}

		static GameObject* createNewGameObject();
		static Object* createNewObject();
		static Object* createRootObject();

	private:
		ObjectManager() {
			o1 = new std::map<unsigned int, Object*>();
			d1 = new std::map<unsigned int, Object*>();

			roots = new std::vector<Object*>();
		}

		void AddObject(Object* o);
		void AddRootObject(Object* o);

	private:
		static ObjectManager* instance;
		static unsigned int _oid;

		std::map<unsigned int, Object*>* o1;
		std::map<unsigned int, Object*>* d1;

		std::vector<Object*>* roots;
	};
}

