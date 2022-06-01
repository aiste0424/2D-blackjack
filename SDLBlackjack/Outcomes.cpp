#include "Outcomes.h"
#include <iostream>

bool Outcomes::Win(Player& player, Dealer& dealer)
{
    if (dealer.GetScore()->GetScore() > 21)
    {
        return true;
    }
    else if (dealer.GetScore()->GetScore() < player.GetScore()->GetScore())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Outcomes::Lose(Player& player, Dealer& dealer)
{
    if (player.GetScore()->GetScore() < dealer.GetScore()->GetScore() && dealer.GetScore()->GetScore() < 22)
    {
        return true;
    }
    else if (player.GetScore()->GetScore() > 21)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Outcomes::Draw(Player& player, Dealer& dealer)
{
    if (dealer.GetScore()->GetScore() == player.GetScore()->GetScore())
    {
        return true;
    }
    else
    {
        return false;
    }
}
//if the player has a blackjack, but the dealer does not, player wins
//if the dealer has a blackjack, but the player does not, house wins
//otherwise it's a standoff
void Outcomes::IsBlackjack(Player& player, Dealer& dealer)
{
    if (player.GetScore()->GetScore() == 21 && dealer.GetScore()->GetScore() == 21)
    {
        m_blackjackStates = Outcomes::IsBlackjackStates::Draw;
    }
    else if (dealer.GetScore()->GetScore() == 21 && player.GetScore()->GetScore() < 21)
    {
        m_blackjackStates = Outcomes::IsBlackjackStates::DealerWins;
    }
    else if (dealer.GetScore()->GetScore() < 21 && player.GetScore()->GetScore() == 21)
    {
        m_blackjackStates = Outcomes::IsBlackjackStates::PlayerWins;
    }
    else
    {
        m_blackjackStates = Outcomes::IsBlackjackStates::GameContinues;
    }
}

const Outcomes::IsBlackjackStates& Outcomes::GetIsBlackjackStates() const
{
    return m_blackjackStates;
}