#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Input
{

public:

	static Input* Instance();
	void Update();

	char GetKeyUp();
	char GetKeyDown();

	bool IsMouseClicked();
	bool IsWindowClosed();
	Vector2D& GetMousePosition();

private:

	Input(){}
	Input(const Input&);
	Input& operator=(Input&);

	char m_keyUp{ ' ' };
	char m_keyDown{ ' ' };

	bool m_isMouseClicked{ false };
	bool m_isWindowClosed{ false };

	int m_mouseButtonUp{ 1 };
	int m_mouseButtonDown{ 0 };

	Vector2D m_mousePosition;
};