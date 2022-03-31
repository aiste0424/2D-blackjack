#include <iostream>
#include "Sprite.h"
#include <SDL_image.h>

Sprite::Sprite()
{
	m_image = nullptr;
	m_animationVelocity = 0.0f;
	m_imageCel = 0;
	m_isAnimated = false;
	m_isAnimationDead = false;
	m_isAnimationLooping = false;

	m_celDimension = { 0, 0 };
	m_imageDimension = { 0, 0 };
	m_spriteDimension = { 0, 0 };

	m_targetRect = {0, 0};
}


void Sprite::IsAnimated(bool flag)
{
	m_isAnimated = flag;
}

void Sprite::IsAnimationLooping(bool flag)
{
	m_isAnimationLooping = flag;
}

//gives a number of the frame/placement the right image is in
void Sprite::SetImageCel(int column, int row)
{
	m_imageCel = ((row - 1) * m_imageDimension.x) + (column - 1);
}
//speed
void Sprite::SetAnimationVelocity(float velocity)
{
	m_animationVelocity = velocity;
}

//This is the resolution of the sprite image as it will appear on-screen
void Sprite::SetSpriteDimension(Vector2D dimensions)
{
	m_spriteDimension = dimensions;
}

Vector2D Sprite::GetSpriteDimension()
{
	return m_spriteDimension;
}

//This is the resolution and col/row dimensions of the sprite image as it is stored in the Assets folder
void Sprite::SetImageDimension(int columns, int rows, Vector2D dimensions)
{
	m_imageDimension.x = columns;
	m_imageDimension.y = rows;

	m_celDimension.x = dimensions.x / columns;
	m_celDimension.y = dimensions.y / rows;
}

Vector2D Sprite::GetImageDimension()
{
	return m_imageDimension;
}

bool Sprite::Load(const std::string& filename)
{
	SDL_Surface* rawImageData = IMG_Load(filename.c_str());

	if (!rawImageData)
	{
		std::cout << "Error loading image file." << std::endl;
		return false;
	}

	m_image = SDL_CreateTextureFromSurface(Screen::Instance()->GetRenderer(), rawImageData);

	return true;
}

void Sprite::Unload()
{
	SDL_DestroyTexture(m_image);
}

void Sprite::Update()
{

	if (m_isAnimated)
	{

		static float total = 0.0f;
		total += 0.1f;

		m_imageCel = static_cast<int>(total * m_animationVelocity) % (m_imageDimension.x * m_imageDimension.y);

		if (!m_isAnimationLooping && m_imageCel == (m_imageDimension.x * m_imageDimension.y - 1))
		{
			m_isAnimationDead = true;
		}

	}
}

void Sprite::Render(int xPos, int yPos, double angle, Sprite::Flip flip)
{
	SDL_Rect sourceRect;

	if (!m_isAnimationDead)
	{
		sourceRect.x = (m_imageCel % m_imageDimension.x) * m_celDimension.x;
		sourceRect.y = (m_imageCel / m_imageDimension.x) * m_celDimension.y;
		sourceRect.w = m_celDimension.x;
		sourceRect.h = m_celDimension.y;

		m_targetRect.x = xPos;
		m_targetRect.y = yPos;
		m_targetRect.w = m_spriteDimension.x;
		m_targetRect.h = m_spriteDimension.y;

		SDL_Point centre{ m_spriteDimension.x / 2, m_spriteDimension.y / 2 };

		SDL_RenderCopyEx(Screen::Instance()->GetRenderer(), m_image, &sourceRect, &m_targetRect, angle, &centre, static_cast<SDL_RendererFlip>(flip));
	}
}
