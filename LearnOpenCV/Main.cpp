#include "Main.h"

#include <stdlib.h>
#include "math/Vector3.h"
#include "render/RenderMain.h"
#include "core/Scene.h"
#include "core/Object.h"
#include "core/ObjectManager.h"
#include "core/Transform.h"
#include "core/Game.h"

#include <direct.h>
#include "file/FilePathManager.h"
#include "Core/SceneManager.h"

int main(int argc, char* argv[])
{
	bool isClose = true;

	int w = 1280;
	int h = 720;
	/*RenderBuffer* buffer = RenderBuffer::init(w, h);
	buffer->setBackgroundColor(Math::Vector3(0.0f, 0.0f, 0.6f));
	buffer->setAntiAliasing(AntiAliasing::X2);*/

	char buffer[200];
	char* c = _getcwd(buffer, 200);

	printf(c);
	FilePathManager::setRootPath(buffer);

	Render::InitEngine();
	Render::CreateWindow(w, h, "Learn Shader");

	Core::Game* game = Core::Game::GetInstance();
	game->InitEngine();
	game->LoadMainScene();

	long time = Render::getCurrentRenderTime();
	while (!Render::ShouldCloseWindow()) {
		// buffer->setBackgroundColor(Math::Vector3(1.0f, 1.0f, 1.0f));
		/*Render::ClearBuffer();*/
		Render::SetBackgroundColor(Math::Vector3(0.01f, 0.01f, 0.01f));

		long currTime = Render::getCurrentRenderTime();
		float delay = currTime - time;

		game->Tick(delay);

		Render::updateTextures(delay);

		Scene* currScene = SceneManager::GetInstance()->GetCurrScene();
		Render::RenderScene(currScene);

		time = currTime;

		// printf("fps : %f \n", 1000.0f / delay);

		Render::RenderEnd();
	}
	game->DestroyInstance();

	return 0;
}