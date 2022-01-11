#pragma once
#include "Core.h"
#include "Component.h"
#include "Camera.h"

namespace Core
{
	class Scene : public Component
	{
	public:
		Scene();

		void Bind();

		Camera* getMainCamera() { 
			return camera; 
		};

		static Scene* getCurrScene() {
			return currScene;
		};

	private:
		Camera* camera;

		static Scene* currScene;
	};
}
