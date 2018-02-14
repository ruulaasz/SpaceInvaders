#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")

#include <SDL.h>
#include <SDL_image.h>

/**
* Manager class for SDL 2.0.
*/
class SDL_Manager
{
public:
	SDL_Manager();
	virtual ~SDL_Manager();

	/**
	* Initialize SDL 2.0 systems.
	*
	*/
	bool init();

	/**
	* Initialize SDL 2.0 systems.
	*
	* @param _name
	* The Name of the window.
	*
	* @param _windowWidth
	* The Width of the window.
	*
	* @param _windowHeight
	* The Height of the window.
	*
	*/
	bool init(const char* _name, int _windowWidth, int _windowHeight);

	/**
	* Shut down SDL 2.0 systems.
	*
	*/
	void destroy();

private:
	/**
	* Initialize SDL 2.0 subsystems.
	*
	*/
	bool initSubSystems();

	/**
	* Creates a window using SDL 2.0.
	*
	* @param _name
	* The Name of the window.
	*
	* @param _windowWidth
	* The Width of the window.
	*
	* @param _windowHeight
	* The Height of the window.
	*
	*/
	bool createSDLWindow(const char* _name = "New Window", int _windowWidth = 1280, int _windowHeight = 920);

	/**
	* Creates the renderer with default vallues and initialize the png module.
	*
	*/
	void createRenderer();

public:
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	SDL_Event m_events;

	int m_windowWidth;
	int m_windowHeight;
};