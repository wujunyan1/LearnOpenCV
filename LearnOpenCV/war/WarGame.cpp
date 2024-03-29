#include "WarGame.h"

#include "../Core/Object.h"
#include "../Core/Camera.h"
#include "../Core/Scene.h"
#include "../Core/Transform.h"
#include "../Core/Model.h"
#include "../Core/SceneManager.h"

#include "../Core/ShowFpsComponent.h"

#include "../ui/UICanvas.h"
#include "../ui/UIImage.h"
#include "../ui/UIFont.h"
#include "../ui/UITransform.h"

#include "../war/map/Map.h"
#include "../war/client/MapClient.h"

#include "../render/renderQueue/RenderWarMapQueue.h"


using namespace Core;


void War::WarGame::NewGame()
{
	Render::CreateShader("warMapShader", "/asserts/shaders/warMapShader.vert", "/asserts/shaders/warMapShader.frag");
	Render::AddCustomRenderQueue("RenderWarMapQueue", Core::new_class<Render::RenderWarMapQueue>());

	Scene* root = SceneManager::GetInstance()->GetCurrScene();

	Transform* cameraTransForm = root->getMainCamera()->getGameObject()->GetComponent<Transform>();
	cameraTransForm->SetPosition({0, 200, 50});
	cameraTransForm->SetRotate({ 90.0f * Math::DEG2RAD, 180.0f * Math::DEG2RAD, 0 });

	/*scene->PreUpdate();
	scene->Update();
	scene->LaterUpdate();*/

	GameObject* uiBase = ObjectManager::createNewGameObject();
	UI::UITransform* baseTransform = uiBase->AddComponent<UI::UITransform>();
	uiBase->AddComponent<UI::UICanvas>();
	root->AddChild(uiBase);

	GameObject* showFont = ObjectManager::createNewGameObject();
	UI::UITransform* uiFontTransform = showFont->AddComponent<UI::UITransform>();
	UI::UIFont* uiFont = showFont->AddComponent<UI::UIFont>();
	uiFont->setText("fps : 60");
	uiFont->setColor({ 1.0, 0.0, 0.0 });

	uiFontTransform->SetPosition({ {0, 0} ,{0, 0} });
	uiFontTransform->SetPivot({ 0, 0 });
	uiFontTransform->SetSize({ {0, 200}, {0, 100} });

	showFont->AddComponent<Core::ShowFpsComponent>();
	uiBase->AddChild(showFont);

	MapSetting setting;
	setting.width = 10;
	setting.height = 10;
	Map::GetInstance()->initMap(setting);

	GameObject* o2 = ObjectManager::createNewGameObject();
	Transform* t2 = o2->AddComponent<Transform>();
	t2->SetPosition({0, 0, 0});
	Model* mesh2 = o2->AddComponent<Model>();
	MapClient* mapClient = o2->AddComponent<MapClient>();
	mapClient->setMap(Map::GetInstance());

	root->AddChild(o2);


	GameObject* showImage = ObjectManager::createNewGameObject();
	UI::UITransform* uiImageTransform = showImage->AddComponent<UI::UITransform>();
	UI::UIImage* testImage = showImage->AddComponent<UI::UIImage>();
	testImage->setImage("warMapData");

	// testImage->setImage("/asserts/map/fantasyhextiles_v3.png");

	uiImageTransform->SetPosition({ {1, -200} ,{1, -200} });
	uiImageTransform->SetPivot({ 0, 0 });
	uiImageTransform->SetSize({ {0, 200}, {0, 200} });

	uiBase->AddChild(showImage);
}
