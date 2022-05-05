#include "PlayState.h"
#include "Input.h"

bool PlayState::OnEnter()
{
    auto InitializingImages = [](Sprite& sprite, const std::string& filename,
        const Vector2D& spriteSize, const Vector2D& imageSize)
    {
        sprite.Load(filename);
        sprite.SetSpriteDimension(spriteSize);
        sprite.SetImageDimension(1, 1, imageSize);
    };

    InitializingImages(m_backgroundImage, "Assets/Images/MainGame/MainGameBackgroundImage.png",
                        { 1280, 720 }, { 1280, 720 });
    InitializingImages(m_deckImage1, "Assets/Images/MainGame/DeckImage.png",
        { 128, 170 }, { 128, 170 });
    InitializingImages(m_deckImage2, "Assets/Images/MainGame/DeckImage.png",
        { 128, 170 }, {128, 170});

    m_table.Initialize();

    return true;
}

GameState* PlayState::Update()
{
    m_table.Update();

    return this;
}

bool PlayState::Render()
{
    m_backgroundImage.Render(0, 0);
    m_deckImage1.Render(135, 275);
    m_deckImage2.Render(125, 265);
    m_table.Render();

    return true;
}

void PlayState::OnExit()
{
    m_backgroundImage.Unload();
    m_deckImage1.Unload();
    m_deckImage2.Unload();
}
