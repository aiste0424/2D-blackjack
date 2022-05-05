#pragma once
#include "Score.h"
#include "GameObject.h"
#include "Deck.h"
#include <vector>

class Player : public GameObject
{
public:

	//Aiste's enum class and 2 functions
	enum class Choice
	{
		No,
		Yes
	};

	void DrawCard();
	int GetScore();   //for the outcomes
	void AddCard(const Cards& card);

	Choice GetChoice();  
	void ResetScore();

	virtual bool Update() override;
	virtual bool Render() override;

private:

	Choice m_choice;
	Score m_score;
	std::vector<Cards> m_cards;
	int m_positionIncrementX   = 150;
	//Render buttons in the player class?
};

