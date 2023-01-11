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
			return mainCamera; 
		};

		static Scene* getCurrScene() {
			return currScene;
		};

		void setMainCamera(Camera* camera)
		{
			this->mainCamera = camera;
		};

	private:
		Camera* mainCamera;
		std::vector<Camera*> cameras;

		static Scene* currScene;
	};
}
