#pragma once

#include "../math/Math.h"
#include "../math/Triangle.h"
#include <opencv2/opencv.hpp>

using namespace cv;

namespace OpenCV
{
	enum class AntiAliasing
	{
		UNUSE = 1,
		X2 = 2,
		X3 = 3,
		X4 = 4,
	};

	class RenderBuffer
	{

	public:
		static RenderBuffer* init(int _w, int _h);
		static RenderBuffer* getInstance() { return instance; };

		Mat getRenderBuffer();
		Mat getNextBuffer();

		void changeNext();

		void setBackgroundColor(Math::Vector3 color);

		void renderTriangle(Math::Triangle<Math::Vector3> triangle, Math::Vector3 color);
		void renderTriangle(Math::Triangle<Math::Vector3> triangle, Math::Triangle<Math::Vector4> color);

		void setColor(int col, int row, Math::Vector3 color, float z = 0.0f);
		void setColor(int col, int row, Math::Vector4 color, float z = 0.0f);
		void setAntiAliasing(AntiAliasing a);

		void swapRenderBuffers();

	private:
		bool inTriangleStrength(int col, int row, Math::Triangle<Math::Vector3> triangle, float* strength);

		void updateRenderColor(int col, int row);

	private:
		RenderBuffer(int _w, int _h);

		Mat renderBuff;
		Mat nextBuff;
		Math::Matrix4 sk;

		std::vector<float> zBuffer;
		std::vector<Math::Vector3> renderData;

		unsigned int w, h;
		AntiAliasing antiAliasing = AntiAliasing::UNUSE;
		int antiAliasingSize = 1;

		std::vector<Math::Triangle<Math::Vector3>> renderTriangles;
		std::vector<Math::Triangle<Math::Vector4>> renderColor;

		static RenderBuffer* instance;

	};
}