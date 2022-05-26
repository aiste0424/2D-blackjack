#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Screen.h"
#include "Vector2D.h"

class Text
{

public:

	Text() {};

	static bool Initialize();

	bool Load(const std::string& filename, int fontSize);

	static void Shutdown();

	void SetText(const std::string text);
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetDimension(int width, int height);
	void Render(int x, int y);
	void Unload();

private:

	bool m_isDirty = false;
	std::string m_text;

	TTF_Font* m_font = { nullptr };
	SDL_Color m_color = {0, 0, 0, 0};
	Vector2D m_dimension = { 0, 0 };
	SDL_Texture* m_texture = { nullptr };
};