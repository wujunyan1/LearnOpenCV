#include "MapClient.h"
#include "../../Core/GameObject.h"
#include "../../Core/Model.h"

using namespace Core;

void War::MapClient::Init()
{
	GameObject* object = getGameObject();
	object->AddComponent<Model>();

}
