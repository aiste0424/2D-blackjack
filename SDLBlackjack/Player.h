#pragma once
#include "Score.h"
#include "GameObject.h"
#include "Vector2D.h"
#include <vector>
#include "Cards.h"

class Player : public GameObject
{
public:

	enum class Choice
	{
		No,
		Yes
	};

	void Initialize();
	void AddCard(const Cards& card);

	Choice GetChoice();  
	void ResetScore();

	virtual bool Update() override;
	virtual bool Render() override;

private:

	Choice m_choice;
	Score* m_score = new Score;
	std::vector<Cards> m_cards;
	Vector2D m_finalDestination = { 321, 510 };
	std::vector<Vector2D> m_cardPositions;

	bool m_isReadyToMove = false;
	bool m_isCardInPlace = true;
};