#include "ShowFpsComponent.h"
#include "Transform.h"
#include "Game.h"
#include "../ui/UIFont.h"
#include "../Util/StringUtil.h"
#include "../opengl/OpenGLCore.h"

using namespace Core;
ShowFpsComponent::ShowFpsComponent()
{
}

void ShowFpsComponent::Bind()
{
}

void ShowFpsComponent::Update()
{

    GL_GET_ERROR();
    UI::UIFont* font = getObject()->GetComponent<UI::UIFont>();
    if (font)
    {
        String fpsStr = StringUtil::Format("fps : %f", Game::GetInstance()->GetCurrFPS());
        font->setText(fpsStr);
    }
    GL_GET_ERROR();
}