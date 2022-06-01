#pragma once
#include <string>
#include <SDL.h>
#include "Screen.h"
#include "Vector2D.h"

class Sprite
{
public:

	enum class Flip
	{
		NO_FLIP = SDL_FLIP_NONE,
		HORZ_FLIP = SDL_FLIP_HORIZONTAL,
		VERT_FLIP = SDL_FLIP_VERTICAL
	};

	Sprite();

	void IsAnimated(bool flag);
	void IsAnimationLooping(bool flag);
	void SetAnimationVelocity(float velocity);
	void SetImageCel(int column, int row);
	void SetSpriteDimension(Vector2D dimensions);
	void SetImageDimension(int columns, int rows, Vector2D dimensions);

	Vector2D GetSpriteDimension();
	Vector2D GetImageDimension();

	bool Load(const std::string& filename);

	void Unload();
	void Update();
	void Render(int xPos, int yPos, double angle = 0.0, Sprite::Flip flip = Sprite::Flip::NO_FLIP);

private:

	int m_imageCel;
	float m_animationVelocity;

	bool m_isAnimated;
	bool m_isAnimationDead;
	bool m_isAnimationLooping;

	SDL_Texture* m_image;
	Vector2D m_celDimension;
	Vector2D m_imageDimension;
	Vector2D m_spriteDimension;

	SDL_Rect m_targetRect;
};