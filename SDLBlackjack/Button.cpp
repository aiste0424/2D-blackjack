#include "Button.h"
#include "Input.h"

//default state sprite attributes
void Button::SetNormalAttributes(const std::string& filename, const Vector2D& imageDimensions,
                                 const Vector2D& spriteDimensions, const Vector2D& columnsRows)
{
    m_normalSprite.Load(filename);
    m_normalSprite.SetImageDimension(columnsRows.x, columnsRows.y, imageDimensions);
    m_normalSprite.SetSpriteDimension(spriteDimensions);
}

//hovered state sprite attributes
void Button::SetHoveredAttributes(const std::string& filename, const Vector2D& imageDimensions,
                                  const Vector2D& spriteDimensions, const Vector2D& columnsRows)
{
    m_hoveredSprite.Load(filename);
    m_hoveredSprite.SetImageDimension(columnsRows.x, columnsRows.y, imageDimensions);
    m_hoveredSprite.SetSpriteDimension(spriteDimensions);
}

//bounding box (same size as the image) for collision
void Button::SetButtonRect()
{
    m_buttonRect.x = this->GetPosition().x;
    m_buttonRect.y = this->GetPosition().y;
    m_buttonRect.w = this->GetDimension().x;
    m_buttonRect.h = this->GetDimension().y;
}

SDL_Point Button::GetMousePosition()
{
    m_mousePosition = { Input::Instance()->GetMousePosition().x, Input::Instance()->GetMousePosition().y };
    return m_mousePosition;
}

//mainly updates button states for the Render() function
bool Button::Update()
{
    GetMousePosition();
    
    //if mouse in inside the bounding box
    if (static_cast<bool>(SDL_PointInRect(&m_mousePosition, &m_buttonRect)))
    {
        //if mouse is clicked
        if (Input::Instance()->IsMouseClicked())
        {
            m_buttonState = Button::ButtonState::Clicked;
            return true;
        }
        m_buttonState = Button::ButtonState::Hovered;
    }
    else
    {
        m_buttonState = Button::ButtonState::Default;
    }

    //if nothing happens to the button
    return false;
}

bool Button::Render()
{
    if (m_buttonState == Button::ButtonState::Hovered)
    {
		auto flip = Sprite::Flip::NO_FLIP;
		
		if (m_isFlipped)
		{
			flip = Sprite::Flip::HORZ_FLIP;
		}
		
		m_hoveredSprite.Render(this->GetPosition().x, this->GetPosition().y, this->GetAngle(), flip);
    }
    else
    {
        m_normalSprite.Render(this->GetPosition().x, this->GetPosition().y, this->GetAngle());
    }
    return true;
}

void Button::Shutdown()
{
    m_hoveredSprite.Unload();
    m_normalSprite.Unload();
}
