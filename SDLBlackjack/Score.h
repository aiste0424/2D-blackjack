#pragma once
#include "GameObject.h"
#include "Text.h"

class Score : public GameObject
{
public:

	Score();

	int GetScore();
	void SetScore(int score);
	void UpdateScore();

	void SetCardValue(int value);

	virtual bool Update() override { return false; };
	virtual bool Render() override;
	void Unload();
	void SetScoreTextDimension();
private:

	int m_cardValue;
	int m_score;
	Text m_text;
};