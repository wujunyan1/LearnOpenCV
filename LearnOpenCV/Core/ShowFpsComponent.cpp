#include "ShowFpsComponent.h"
#include "Transform.h"
#include "Game.h"
#include "../ui/UIFont.h"
#include "../Util/StringUtil.h"

using namespace Core;
ShowFpsComponent::ShowFpsComponent()
{
}

void ShowFpsComponent::Bind()
{
}

void ShowFpsComponent::Update()
{
    UI::UIFont* font = getObject()->GetComponent<UI::UIFont>();
    if (font)
    {
        String fpsStr = StringUtil::Format("fps : %f", Game::GetInstance()->GetCurrFPS());
        font->setText(fpsStr);
    }
}