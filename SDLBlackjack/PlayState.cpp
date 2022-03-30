#include "PlayState.h"


bool PlayState::OnEnter()
{
    m_backgroundImage.Load("Assets/Images/MainGame/MainGameBackgroundImage.png");
    m_backgroundImage.SetSpriteDimension(1280, 720);
    m_backgroundImage.SetImageDimension(1, 1, 1920, 1080);

    return true;
}

GameState* PlayState::Update()
{
    return this;
}

bool PlayState::Render()
{
    m_backgroundImage.Render(0, 0, 0.0);
    return true;
}

void PlayState::OnExit()
{
    m_backgroundImage.Unload();
}
