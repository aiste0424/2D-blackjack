#pragma once
#include "Sprite.h"
#include "GameObject.h"

class Cards : public GameObject
{
public:

	enum class Suit
	{
		//the allignment is the same as in the DeckOfCards.png. DO NOT TOUCH
		Hearts,
		Clubs,
		Diamonds,
		Spades
	};

	//the allignment is the same as in the DeckOfCards.png. DO NOT TOUCH
	enum class Rank
	{
		Two = 2,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
		Ace
	};

	enum class CardMovementState
	{
		NoMovement,
		Moving,
		Finished
	};

	void SetSuit(Suit& suit);
	void SetRank(Rank& rank);
	void SetValue(int value);
	void SetIsTaken(bool taken);
	void SetImage(Sprite& sprite);
	void SetHasCardMoved(bool hasCardMoved);
	void SetCardMovementState(CardMovementState& state);

	const Suit& GetSuit() const;
	const Rank& GetRank() const;
	int GetValue();
	bool GetIsTaken();
	bool GetHasCardMoved();
	const Sprite& GetImage() const;
	CardMovementState GetCardMovementState();

	virtual bool Update() override;
	virtual bool Render() override;

private:

	Suit m_suit = static_cast<Suit>(0);
	Rank m_rank = static_cast<Rank>(0);
	CardMovementState m_cardMovementState = { CardMovementState::NoMovement };
	int m_value = 0;
	bool m_isTaken = false;
	bool m_hasCardMoved = false; //checks if the card travelled to its destination
	Sprite m_sprite;
};
