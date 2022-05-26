#pragma once
#include "Score.h"
#include "Vector2D.h"
#include "GameObject.h"
#include <vector>
#include "Cards.h"

class Dealer : public GameObject
{
public:

	void Initialize();
	void ResetScore();
	void AddCard(const Cards& card);
	const std::vector<Cards>& GetDeck() const;

	virtual bool Update() override;
	virtual bool Render() override;

	bool GetCoveredCardPlaced();
	void Unload();



private:

	Score* m_score = new Score;
	std::vector<Cards> m_cards;
	bool m_isReadyToMove = false;
	Vector2D m_finalDestination = { 321, 50 };
	std::vector<Vector2D> m_cardPositions;

	bool m_isCoveredCardPlaced = false;
};