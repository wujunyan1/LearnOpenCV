#include "Scene.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"
#include "TestComponent.h"
#include "CameraMoveComponent.h"
#include "SkyBox.h"

#include "../math/Math.h"

using namespace Core;

Scene* Scene::currScene = nullptr;

Scene::Scene() 
{
	currScene = this;
	cameras = std::vector<Camera*>();
}

void Scene::Bind()
{
	
	Object* cameraObj = ObjectManager::createNewObject();
	this->AddChild(cameraObj);

	Transform* cameraT = cameraObj->AddComponent<Transform>();
	mainCamera = cameraObj->AddComponent<Camera>();

	Math::Vector2T<int> size = Render::GetWindowSize();

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