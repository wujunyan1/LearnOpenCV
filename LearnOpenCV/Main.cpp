#include "Main.h"

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include "render/RenderBuffer.h"

#include "math/Vector3.h"
#include "core/Scene.h"
#include "core/Object.h"
#include "core/ObjectManager.h"
#include "core/Transform.h"

using namespace Render;
using namespace cv;

int main(int argc, char* argv[])
{
	bool isClose = true;

	int w = 1280;
	int h = 720;
	RenderBuffer* buffer = RenderBuffer::init(w, h);
	buffer->setBackgroundColor(Math::Vector3(0.0f, 0.0f, 0.6f));

	Core::Object* root = Core::ObjectManager::createRootObject();
	Core::Transform* transform = root->AddComponent<Core::Transform>();
	Core::Scene* scene = root->AddComponent<Core::Scene>();

	while (isClose) {
		buffer->setBackgroundColor(Math::Vector3(0.0f, 0.0f, 0.0f));

		transform->PreUpdate();
		transform->Update();
		transform->LaterUpdate();
		transform->Render();

		/*buffer->renderTriangle(
			Math::Triangle(
				Math::Vector3(0, 0.2, 0),
				Math::Vector3(0.6, 0, 0),
				Math::Vector3(0.1, 0.4, 0)
			),
			Math::Vector3(1.0f, 0.0f, 0.0f)
		);

		buffer->renderTriangle(
			Math::Triangle(
				Math::Vector3(1, 0.2, 0),
				Math::Vector3(0.6, 0, 0),
				Math::Vector3(0.1, 0.4, 0)
			),
			Math::Triangle(
				Math::Vector3(1, 0, 0),
				Math::Vector3(0, 1, 0),
				Math::Vector3(0, 0, 1)
			)
		);*/


		cv::Mat image = buffer->getRenderBuffer();
		//image.convertTo(image, CV_8UC3, 1.0f);
		cv::imshow("image", image);
		int key = cv::waitKey(10);
	}

	return 0;
}