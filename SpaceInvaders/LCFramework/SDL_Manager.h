#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Module.h"


namespace LCF
{
	class Transform;
	class Texture;
	/**
	* Manager class for SDL 2.0
	*/
	class SDL_Manager : public LCF::Module<SDL_Manager>
	{
	public:
		SDL_Manager();
		virtual ~SDL_Manager();

		/**
		* Initialize SDL 2.0 systems.
		*
		*@return bool
		*The result of the initialization
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
		*@return bool
		*The result of the initialization
		*
		*/
		bool init(const char* _name, int _windowWidth, int _windowHeight);

		/**
		* Shut down SDL 2.0 systems.
		*
		*/
		void destroy();

		/**
		* Render a texture
		*
		*/
		void RenderTexture(Transform _transform, Texture* _texture, bool _flip = false);

		/**
		* Render a animation
		*
		*/
		void RenderAnimation(Texture* _texture, SDL_Rect * _dstRect, SDL_Rect * _srcRect,  bool _flip = false, double _angle = 0.0f);

		/**
		* Render a box
		*
		*/
		void RenderBox(float _x, float _y, float _w, float _h);

		/**
		* Render aline
		*
		*/
		void RenderLine(int _x, int _y, int _x1, int _y1);

	private:
		/**
		* Initialize SDL 2.0 subsystems.
		*
		*@return bool
		*The result of the initialization
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
		*@return bool
		*The result of the initialization
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
}