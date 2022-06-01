#pragma once
#include "Player.h"
#include "Dealer.h"

class Outcomes
{
public:

	enum class IsBlackjackStates
	{
		PlayerWins,
		DealerWins,
		Draw,
		GameContinues
	};

	bool Win(Player& player, Dealer& dealer);
	bool Lose(Player& player, Dealer& dealer);
	bool Draw(Player& player, Dealer& dealer);
	void IsBlackjack(Player& player, Dealer& dealer);
	const IsBlackjackStates& GetIsBlackjackStates() const;

private:

	IsBlackjackStates m_blackjackStates = { IsBlackjackStates::GameContinues };
};