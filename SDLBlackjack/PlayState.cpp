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
        { 128, 170 }, { 128, 170 });

    m_table.Initialize();

    m_win.Load("WinAudio.wav", "WinAudio");
    m_win.SetSound("WinAudio");
    m_win.SetVolume(1.0f);

    m_lose.Load("LoseAudio.wav", "LoseAudio");
    m_lose.SetSound("LoseAudio");
    m_lose.SetVolume(1.0f);

    return true;
}

GameState* PlayState::Update()
{
    m_table.Update();
    if (m_table.GetTableStates() == Table::TableStates::PlayerWins && m_hasWinPlayed == false)
    {
        m_hasWinPlayed = true;
        m_win.Play();
    }
    else if (m_table.GetTableStates() == Table::TableStates::HouseWins && m_hasLosePlayed == false)
    {
        m_hasLosePlayed = true;
        m_lose.Play();
    }

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
    m_win.Unload();
    m_lose.Unload();
}