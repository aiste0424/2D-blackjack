#include <iostream>
#include "Score.h"

Score::Score()
{
	m_score = 0;
	m_cardValue = 0;
	m_text.Load("Assets/Fonts/PixelFont.ttf", 100);
	m_text.SetDimension(m_dimension.x, m_dimension.y);
	m_text.SetColor(255, 245, 109, 250);
}

void Score::SetCardValue(int value)
{
	m_cardValue = value;
}

bool Score::Render()
{
	m_text.Render(m_position.x, m_position.y);
	return true;
}

void Score::UpdateScore()
{
	m_score = m_score + m_cardValue;
	if (m_position.y == 10)
	{
		m_text.SetText("Dealer's score: " + std::to_string(m_score));
	}
	else if (m_position.y == 650)
	{
		m_text.SetText("Your score: " + std::to_string(m_score));
	}
}

void Score::ChangeAceValue()
{
	m_score = m_score - 10;
}

int Score::GetScore()
{
	return m_score;
}

void Score::SetScore(int score)
{
	m_score = score;
}

void Score::Unload()
{
	m_text.Unload();
}

void Score::SetScoreTextDimension()
{
	m_text.SetDimension(m_dimension.x, m_dimension.y);
}