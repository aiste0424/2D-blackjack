#pragma once
#include <vector>
#include "Cards.h"
#include "Score.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Sound.h"

class Dealer : public GameObject
{
public:

	void Initialize();
	virtual bool Update() override;
	virtual bool Render() override;
	void Unload();
	void Reset();

	void AddCard(Cards& card); //adds a card to the vector of cards
	bool GetIsReadyToMove();
	bool GetCoveredCardPlaced();
	Score* GetScore();
	const std::vector<Cards>& GetCards() const;

private:

	std::vector<Cards> m_cards;
	Score* m_score = new Score;
	Vector2D m_finalDestination = { 320, 50 }; //the position of the first card (starts the vector container)
	std::vector<Vector2D> m_cardPositions;//card positions on screen

	bool m_isReadyToMove = true;
	bool m_isCoveredCardPlaced = false;
	Sound m_deal;
};