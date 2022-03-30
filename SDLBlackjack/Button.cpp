#include "Button.h"
#include <iostream>

void Button::SetNormalAttributes(const std::string& filename, Vector2D dimensions, Vector2D position)
{
    m_normalSprite.Load(filename);
    m_normalSprite.SetImageDimension(1, 1, dimensions.x, dimensions.y);
    m_normalSprite.SetPosition(position.x, position.y);
}

void Button::SetHoveredAttributes(const std::string& filename, Vector2D dimensions, Vector2D position)
{
    m_hoveredSprite.Load(filename);
    m_hoveredSprite.SetImageDimension(1, 1, dimensions.x, dimensions.y);
    m_hoveredSprite.SetPosition(position.x, position.y);
}

void Button::SetButtonRect()
{
    m_buttonRect.x = m_normalSprite.GetPosition().x;
    m_buttonRect.y = m_normalSprite.GetPosition().y;
    m_buttonRect.w = m_normalSprite.GetSpriteDimension().x;
    m_buttonRect.h = m_normalSprite.GetSpriteDimension().y;
}

SDL_Point Button::GetMousePosition()
{
    m_mousePosition = { Input::Instance()->GetMousePosition().x, Input::Instance()->GetMousePosition().y };
    return m_mousePosition;
}

bool Button::Update()
{
    GetMousePosition();
    m_buttonState = Button::ButtonState::Default;

    if (static_cast<bool>(SDL_PointInRect(&m_mousePosition, &m_buttonRect)))
    {
        if (Input::Instance()->IsMouseClicked())
        {
            m_buttonState = Button::ButtonState::Clicked;
            return true;
        }
        m_buttonState = Button::ButtonState::Hovered;
    }
    
    return false;
}

bool Button::Render(FacingDirection facingDirection)
{
    if (m_buttonState == Button::ButtonState::Hovered)
    {
        m_hoveredSprite.Render(m_hoveredSprite.GetPosition().x, m_hoveredSprite.GetPosition().y, static_cast<double>(facingDirection));
    }
    else
    {
        m_normalSprite.Render(m_normalSprite.GetPosition().x, m_normalSprite.GetPosition().y, static_cast<double>(facingDirection));
    }
    return true;
}

void Button::Shutdown()
{
    m_hoveredSprite.Unload();
    m_normalSprite.Unload();
}
