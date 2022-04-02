#include "PlayState.h"
#include "Input.h"


bool PlayState::OnEnter()
{
    m_backgroundImage.Load("Assets/Images/MainGame/MainGameBackgroundImage.png");
    m_backgroundImage.SetSpriteDimension({ 1280, 720 });
    m_backgroundImage.SetImageDimension(1, 1, { 1920, 1080 });

    auto InitializingButtons = [](Button& button, const std::string& filenameNormal, const std::string& filenameHovered,
        const Vector2D& imageSize, const Vector2D& buttonSize, const Vector2D& buttonPosition, const Vector2D& columnsRows)
    {
        button.SetNormalAttributes(filenameNormal, imageSize, buttonSize, columnsRows); //button position missing
        button.SetHoveredAttributes(filenameHovered, imageSize, buttonSize, columnsRows);
        button.SetDimension(buttonSize); //position and dimension needs to be set BEFORE buttonRect
        button.SetPosition(buttonPosition);
        button.SetButtonRect();
    };

    InitializingButtons(m_buttonGetCard, "Assets/Images/UI/ButtonIconsNormal.png",
        "Assets/Images/UI/ButtonIconsHovered.png", { 1280, 1536 }, { 256, 256 }, {200, 200}, { 5, 6 });
    

    return true;
}

GameState* PlayState::Update()
{
    if (Input::Instance()->IsMouseClicked())
    {
        m_deck.Update();
    }
    return this;
}

bool PlayState::Render()
{
    m_backgroundImage.Render(0, 0);
    m_deck.Render();
    return true;
}

void PlayState::OnExit()
{
    m_backgroundImage.Unload();
}
