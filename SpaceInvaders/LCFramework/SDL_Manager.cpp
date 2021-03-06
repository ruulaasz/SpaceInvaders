#include "SDL_Manager.h"
#include <cstdio>
#include "Transform.h"
#include "Texture.h"

namespace LCF
{
	SDL_Manager::SDL_Manager()
	{
		m_windowHeight = 0;
		m_windowWidth = 0;
		m_renderer = nullptr;
		m_window = nullptr;
	}

	SDL_Manager::~SDL_Manager()
	{

	}

	bool SDL_Manager::initSubSystems()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL failed to initialize the video system: %s\n", SDL_GetError());
			return false;
		}

		int imgFlags = IMG_INIT_PNG;

		if (!(IMG_Init(imgFlags)& imgFlags))
		{
			printf("Failed to load PNG module");
		}

		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			printf("SDL failed to initialize the audio system: %s\n", SDL_GetError());
			return false;
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		Mix_AllocateChannels(100);

		return true;
	}

	bool SDL_Manager::createSDLWindow(const char*  _name, int _windowWidth, int _windowHeight)
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: linear texture filtering not enabled");
		}

		m_window = SDL_CreateWindow(_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, SDL_WINDOW_SHOWN);

		m_windowHeight = _windowHeight;
		m_windowWidth = _windowWidth;

		return true;
	}

	void SDL_Manager::createRenderer()
	{
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}

	void SDL_Manager::RenderTexture(Transform _transform, Texture* _texture, bool _flip)
	{
		SDL_Rect renderQuad = { _transform.m_posX, _transform.m_posY, _transform.m_sizeW, _transform.m_sizeH };

		if (!_flip)
		{
			SDL_RenderCopyEx(m_renderer, _texture->m_sdlTexture, nullptr, &renderQuad, _transform.m_angle, nullptr, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopyEx(m_renderer, _texture->m_sdlTexture, nullptr, &renderQuad, _transform.m_angle, nullptr, SDL_FLIP_HORIZONTAL);
		}
	}

	void SDL_Manager::RenderAnimation(Texture* _texture, SDL_Rect * _dstRect, SDL_Rect * _srcRect, bool _flip , double _angle)
	{
		if (!_flip)
		{
			SDL_RenderCopyEx(m_renderer, _texture->m_sdlTexture, _srcRect, _dstRect, _angle, nullptr, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopyEx(m_renderer, _texture->m_sdlTexture, _srcRect, _dstRect, _angle, nullptr, SDL_FLIP_HORIZONTAL);
		}
	}

	void SDL_Manager::RenderBox(float _x, float _y, float _w, float _h)
	{
		SDL_Rect renderQuad = { (int)_x, (int)_y, (int)_w, (int)_h };
		SDL_RenderDrawRect(m_renderer, &renderQuad);
	}

	void SDL_Manager::RenderLine(int _x, int _y, int _x1, int _y1)
	{
		SDL_RenderDrawLine(m_renderer, _x, _y, _x1, _y1);
	}

	bool SDL_Manager::init()
	{
		if (initSubSystems())
		{
			if (createSDLWindow())
			{
				createRenderer();
			}
		}

		return true;
	}

	bool SDL_Manager::init(const char* _name, int _windowWidth, int _windowHeight)
	{
		if (initSubSystems())
		{
			if (createSDLWindow(_name, _windowWidth, _windowHeight))
			{
				createRenderer();
			}
		}

		return true;
	}

	void SDL_Manager::destroy()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
		m_renderer = nullptr;

		IMG_Quit();
		SDL_Quit();
		Mix_Quit();
	}
}