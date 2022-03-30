#pragma once
#include <string>
#include <SDL.h>

class Screen
{

public:

	static Screen* Instance();
	
	bool Initialize(const std::string& windowTitle = "<No name>",
					int width = 1280,
					int height = 720);
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
};

