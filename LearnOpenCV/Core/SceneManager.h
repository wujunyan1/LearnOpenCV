#pragma once
#include "Core.h"
#include "Scene.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"

namespace Core 
{
	class SceneManager
	{
	public:
		static SceneManager* GetInstance() {
			if (instance == nullptr) {
				instance = new SceneManager();
			}
			return instance;
		}

		Scene* GetCurrScene() { return currScene; }
	private:
		SceneManager() {
			root = ObjectManager::createRootObject();
			transform = root->AddComponent<Transform>();
			
			Object* o = ObjectManager::createNewObject();
			Transform* t = o->AddComponent<Transform>();
			transform->AddChild(t);

			currScene = o->AddComponent<Scene>();
		}

	private:
		static SceneManager* instance;

		Object* root;
		Transform* transform;
		Scene* currScene;
	};

}

