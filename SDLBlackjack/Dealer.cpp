#include "Dealer.h"
#include <iostream>

void Dealer::Initialize()
{
    for (auto i = 0; i < 5; i++)
    {
        m_cardPositions.push_back(m_finalDestination);
        m_finalDestination.x += 140;
    }
    m_score->SetPosition({ 20, 10 });
    m_score->SetDimension({ 200, 50 });
    m_score->SetScoreTextDimension();
    m_score->SetScore(0);
}

void Dealer::ResetScore()
{
    m_score->SetScore(0);
}

void Dealer::AddCard(const Cards& card)
{
    m_cards.push_back(card);
    m_cards.back().SetPosition({ 125, 266 });

    if (m_cards.size() == 1)
    {
        m_cards[0].SetCardState(Cards::CardState::Moving);
    }
    if (m_isCoveredCardPlaced == true)
    {
        m_score->SetCardValue(m_cards.back().GetValue());
        m_score->UpdateScore();
    }
}

const std::vector<Cards>& Dealer::GetDeck() const
{
    return m_cards;
}

bool Dealer::Update()
{
    for (auto i = 0; i < m_cards.size(); i++)
    {
        if (m_isReadyToMove == true)
        {
            m_cards[i].SetCardState(Cards::CardState::Moving);
            m_isReadyToMove = false;
        }

        for (auto j = 0; j < m_cardPositions.size(); j++)
        {
            if (i == j)
            {
                if (m_cards[i].GetCardState() == Cards::CardState::Moving)
                {
                    if (m_cards[i].GetPosition().x != m_cardPositions[j].x)
                    {
                        m_cards[i].SetPosition({ m_cards[i].GetPosition().x + 2, m_cards[i].GetPosition().y });
                    }
                    else if (m_cards[i].GetPosition().y != m_cardPositions[j].y)
                    {
                        m_cards[i].SetPosition({ m_cards[i].GetPosition().x, m_cards[i].GetPosition().y - 2 });
                    }
                    else
                    {
                        if (i == 1 && m_isCoveredCardPlaced == false)
                        {
                            m_isCoveredCardPlaced = true;
                        }
                        m_cards[i].SetCardState(Cards::CardState::Finished);
                        m_isReadyToMove = true;
                    }
                }
            }
        }
    }
    
    return true;
}

bool Dealer::Render()
{
    for (auto& m_cards : m_cards)
    {
        if (m_cards.GetCardState() != Cards::CardState::NoMovement)
        {
            m_cards.Render();
        }
    }

    m_score->Render();

    return true;
}

bool Dealer::GetCoveredCardPlaced()
{
    return m_isCoveredCardPlaced;
}

void Dealer::Unload()
{
    m_cards.clear();
    m_score->Unload();
}
