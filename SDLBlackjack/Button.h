#pragma once
#include "Sprite.h"
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

	void SetButtonRect();
	SDL_Point GetMousePosition();
	void SetIsFlipped(bool isFlipped);

	void SetNormalAttributes(const std::string& filename, const Vector2D& imageDimensions,
							 const Vector2D& spriteDimensions, const Vector2D& columnsRows);
	void SetHoveredAttributes(const std::string& filename, const Vector2D& imageDimensions,
							  const Vector2D& spriteDimensions, const Vector2D& columnsRows);
	
	virtual bool Update() override;
	virtual bool Render() override;
	
	void Unload();

private:

	bool m_isFlipped = { false };

	Sprite m_normalSprite;
	Sprite m_hoveredSprite;
	SDL_Rect m_buttonRect = {0, 0, 0, 0};
	SDL_Point m_mousePosition = { 0, 0 };
	ButtonState m_buttonState = { ButtonState::Default };
};