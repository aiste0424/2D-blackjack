#pragma once
#include <string>
#include <SDL.h>

class Screen
{

public:

	static Screen* Instance();
	
	bool Initialize(const std::string& windowTitle, int width, int height);
	void Clear();
	void Present();
	void Shutdown();

	SDL_Renderer* GetRenderer();

private:

	//cannot create, copy, or assign one screen to another externally
	Screen(){}							//constructor
	Screen(const Screen&);				//copy constructor
	Screen& operator=(const Screen&);	//assignment operator

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
	SDL_Rect* m_screenSize{ nullptr };
};