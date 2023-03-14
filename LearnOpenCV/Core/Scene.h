#pragma once
#include "Core.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"

namespace Core
{
	class Scene : public Object
	{
	public:
		Scene();

		void Bind();

		void Render()
		{
			cameras.clear();
			Object::Render();
		};

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

		void addRenderCamera(Camera* camera)
		{
			cameras.push_back(camera);
		}

		std::vector<Camera*>& getRenderCameras()
		{
			return cameras;
		}

	private:
		Camera* mainCamera;
		std::vector<Camera*> cameras;

		static Scene* currScene;
	};
}
