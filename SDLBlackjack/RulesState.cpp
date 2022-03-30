#include "RulesState.h"
#include <string>
#include "Vector2D.h"
bool RulesState::OnEnter()
{
    auto InitializingBackgroundImages = [](Sprite& sprite, std::string filename, Vector2D spriteSize, Vector2D imageSize)
    {
        sprite.Load(filename);
        sprite.SetSpriteDimension(spriteSize.x, spriteSize.y);
        sprite.SetImageDimension(1, 1, imageSize.x, imageSize.y);
    };

    auto InitializingButtons = [](Button& button, std::string filenameNormal, std::string filenameHovered,
        Vector2D imageSize, Vector2D buttonSize, Vector2D buttonPosition)
    {
        button.SetNormalAttributes(filenameNormal, imageSize, buttonPosition);
        button.SetHoveredAttributes(filenameHovered, imageSize, buttonPosition);
        button.SetPosition(buttonPosition);
        button.SetDimension(buttonSize);
        button.SetButtonRect();
    };

    InitializingBackgroundImages(m_rulesImage, "Assets/Images/Rules/RulesPart1.png", { 1280, 720 }, { 1920, 1080 });
    InitializingBackgroundImages(m_payoutsImage, "Assets/Images/Rules/RulesPart2.png", { 1280, 720 }, { 1920, 1080 });

    InitializingButtons(m_arrowBack, "Assets/Images/Rules/ArrowBackNormal.png",
                        "Assets/Images/Rules/ArrowBackHovered.png", { 450, 500 }, { 100, 100 }, {1180, 0});

    InitializingButtons(m_arrowLeftRight, "Assets/Images/Rules/ArrowSidesNormal.png",
        "Assets/Images/Rules/ArrowSidesHovered.png", { 700, 700 }, { 150, 150 }, { 500, 200 });
    

    return true;
}

GameState* RulesState::Update()
{
    if (m_arrowBack.Update())
    {
        return new MainMenuState;
    }
    return this;
}

bool RulesState::Render()
{
    if (m_arrowLeftRight.Update())
    {

    }
    if (m_arrowLeftRight.Update())
    {
        m_payoutsImage.Render(0, 0, 0.0);
        m_arrowLeftRight.SetPosition({ 0, 520 });
        m_arrowLeftRight.Render(Button::FacingDirection::Right);
    }
    else
    {
        m_rulesImage.Render(0, 0, 0.0);
        m_arrowLeftRight.SetPosition({ 500, 200 });
        m_arrowLeftRight.SetButtonRect();
        m_arrowLeftRight.Render(Button::FacingDirection::Left);
    }
    
    m_arrowBack.Render(Button::FacingDirection::Default);
    
    return true;
}

void RulesState::OnExit()
{
    m_rulesImage.Unload();
    m_payoutsImage.Unload();
    m_arrowBack.Shutdown();
    m_arrowLeftRight.Shutdown();
}
