#include "Cards.h"

void Cards::SetSuit(Suit suit)
{
    m_suit = suit;
}

void Cards::SetRank(Rank rank)
{
    m_rank = rank;
}

void Cards::SetValue(int value)
{
    m_value = value;
}

void Cards::SetIsTaken(bool taken)
{
    m_isTaken = taken;
}

void Cards::SetImage(Sprite& sprite)
{
    m_sprite = sprite;
}

void Cards::SetCardState(CardState state)
{
    m_cardState = state;
}

int Cards::GetValue()
{
    return m_value;
}

const Cards::Suit& Cards::GetSuit() const
{
    return m_suit;
}

const Cards::Rank& Cards::GetRank() const
{
    return m_rank;
}

bool Cards::GetIsTaken()
{
    return m_isTaken;
}

const Sprite& Cards::GetImage() const
{
    return m_sprite;
}

const Cards::CardState& Cards::GetCardState() const
{
    return m_cardState;
}

bool Cards::Update()
{
    return true;
}


bool Cards::Render()
{
    m_sprite.Render(m_position.x, m_position.y);
    return true;
}