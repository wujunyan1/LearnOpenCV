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

int main(int argc, char* argv[])
{
	bool isClose = true;

	int w = 1000;
	int h = 1000;
	/*RenderBuffer* buffer = RenderBuffer::init(w, h);
	buffer->setBackgroundColor(Math::Vector3(0.0f, 0.0f, 0.6f));
	buffer->setAntiAliasing(AntiAliasing::X2);*/

	char buffer[200];
	char* c = _getcwd(buffer, 200);

	printf(c);
	FilePathManager::setRootPath(buffer);

	Render::InitEngine();
	Render::CreateWindow(1000, 1000, "Learn Shader");

	Core::Game* game = Core::Game::GetInstance();
	game->LoadMainScene();

	long time = Render::getCurrentRenderTime();
	while (!Render::ShouldCloseWindow()) {
		// buffer->setBackgroundColor(Math::Vector3(1.0f, 1.0f, 1.0f));
		Render::ClearBuffer();
		Render::SetBackgroundColor(Math::Vector3(0.01f, 0.01f, 0.01f));

		long currTime = Render::getCurrentRenderTime();
		float delay = currTime - time;

		game->Tick(delay);
		game->Render(delay);
		/*transform->PreUpdate();
		transform->Update();
		transform->LaterUpdate();
		transform->Render();*/

		/*
		buffer->renderTriangle(
			Math::Triangle<Math::Vector3>(
				Math::Vector3(0, 0.2, 3),
				Math::Vector3(0.6, 0, 1),
				Math::Vector3(0.1, 0.4, 2)
			),
			Math::Triangle<Math::Vector4>(
				Math::Vector4(0, 0.5, 1, 1),
				Math::Vector4(0, 0.5, 1, 1),
				Math::Vector4(0, 0.5, 1, 1)
			)
		);

		buffer->renderTriangle(
			Math::Triangle<Math::Vector3>(
				Math::Vector3(0, 0.3, 2),
				Math::Vector3(0.7, 0, 2),
				Math::Vector3(0.2, 0.5, 2)
			),
			Math::Triangle<Math::Vector4>(
				Math::Vector4(1, 1, 0, 1),
				Math::Vector4(1, 1, 0, 1),
				Math::Vector4(1, 1, 0, 1)
			)
		);
		*/


		//cv::Mat image = buffer->getRenderBuffer();
		////image.convertTo(image, CV_8UC3, 1.0f);
		//cv::imshow("image", image);
		//int key = cv::waitKey(10);

		Render::Render(delay);
		time = currTime;

		Render::RenderEnd();
	}

	return 0;
}