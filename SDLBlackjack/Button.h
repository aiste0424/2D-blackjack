#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Vector2D.h"
#include "GameObject.h"

class Button : public GameObject
{
public:

	enum class ButtonState
	{
		Default,
		Hovered,
		Clicked
	};

	//the numbers are angles
	enum class FacingDirection
	{
		Default = 0,
		Left = 90,
		Down = 180,
		Right = 270
	};
	
	void SetButtonRect();
	SDL_Point GetMousePosition();

	void SetNormalAttributes(const std::string& filename, Vector2D dimensions, Vector2D position);
	void SetHoveredAttributes(const std::string& filename, Vector2D dimensions, Vector2D position);
	
	virtual bool Update();
	virtual bool Render(FacingDirection facingDirection);
	
	void Shutdown();
private:

	Sprite m_normalSprite;
	Sprite m_hoveredSprite;
	SDL_Rect m_buttonRect = {0, 0, 0, 0};
	SDL_Point m_mousePosition = { 0, 0 };
	ButtonState m_buttonState = { ButtonState::Default };
	FacingDirection m_facingDirection = { FacingDirection::Default };
	int m_angle = 0;
};

