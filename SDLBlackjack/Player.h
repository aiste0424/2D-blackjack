#pragma once
#include <vector>
#include "Score.h"
#include "Cards.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Sound.h"

class Player : public GameObject
{
public:

	void Initialize();
	virtual bool Update() override;
	virtual bool Render() override;
	void Unload();

	void AddCard(Cards& card); //adds a card to the vector of cards
	bool GetIsReadyToMove();
	Score* GetScore();
	void Reset();

private:

	std::vector<Cards> m_cards;
	Score* m_score = new Score;
	Vector2D m_finalDestination = { 320, 510 }; //the position of the first card (starts the vector container)
	std::vector<Vector2D> m_cardPositions;//card positions on screen

	bool m_isReadyToMove = true;
	Sound m_deal;
};