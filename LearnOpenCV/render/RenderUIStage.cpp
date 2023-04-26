#include "RenderUIStage.h"
#include "RenderQueue.h"
#include "../Core/Object.h"
#include "../Core/SkyBox.h"
#include "RenderSkyBox.h"
#include "../Core/Scene.h"
#include "../ui/UICanvas.h"

using namespace Render;

RenderUIStage::RenderUIStage(unsigned int index) : RenderStage(index)
{
}

RenderUIStage::~RenderUIStage()
{
	
}

void Render::RenderUIStage::AddRenderCanvas(UI::UICanvas* canvas)
{

}

void Render::RenderUIStage::render(Core::Camera* renderCamera)
{

}