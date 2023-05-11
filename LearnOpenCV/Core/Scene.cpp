#include "Scene.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"
#include "TestComponent.h"
#include "CameraMoveComponent.h"
#include "SkyBox.h"

#include "../math/Math.h"
#include "GlobalDictionary.h"

using namespace Core;

Scene* Scene::currScene = nullptr;

Scene::Scene() : GameObject()
{
	currScene = this;
	cameras = std::vector<Camera*>();
	models = std::map<ui64, Model*>();
}

void Scene::Bind()
{
	
	GameObject* cameraObj = ObjectManager::createNewGameObject();
	this->AddChild(cameraObj);

	Transform* cameraT = cameraObj->AddComponent<Transform>();
	mainCamera = cameraObj->AddComponent<Camera>();

	Math::Vector2T<int> size = GlobalDictionary::getRealWindowSize();

	mainCamera->init(Math::radians(45.0f), size.x * 1.0f / size.y, 0.1f, 1000.0f);
	cameraT->SetPosition({0, 0, 0});

	cameraObj->AddComponent<CameraMoveComponent>();
	
	mainCamera->SetMainCamera(true);
	
	SkyBox* skybox = cameraObj->AddComponent<SkyBox>();

	std::vector<std::string> faces
	{
		"/asserts/images/skybox/right.jpg",
		"/asserts/images/skybox/left.jpg",
		"/asserts/images/skybox/top.jpg",
		"/asserts/images/skybox/bottom.jpg",
		"/asserts/images/skybox/front.jpg",
		"/asserts/images/skybox/back.jpg"
	};

	skybox->SetImags(faces);

	

	//o2->AddComponent<TestComponent>();
}

void Core::Scene::addRenderModel(Model* model)
{
	models.insert(std::pair<ui64, Model*>(model->getId(), model));
}

void Core::Scene::removeRenderModel(ui64 id)
{
	models.erase(id);
}
