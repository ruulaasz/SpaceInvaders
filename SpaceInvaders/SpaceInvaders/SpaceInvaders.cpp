// SpaceInvaders.cpp: define el punto de entrada de la aplicación.
//
#include "stdafx.h"
#include "SpaceInvaders.h"

SDL_Manager g_sdlManager;
AssetManager g_assetManager;

bool g_quit;
float g_deltaTime;
Asset* g_testTexture;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void render()
{
	SDL_SetRenderDrawColor(g_sdlManager.m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_sdlManager.m_renderer);

	reinterpret_cast<Texture*>(g_testTexture)->render(0, 35, g_sdlManager.m_renderer);

	SDL_RenderPresent(g_sdlManager.m_renderer);
}

void renderDebugConsole()
{
	system("cls");
	printf("Assets Loaded: %d", g_assetManager.m_allAssets.size());
}

void handleKeyboardEvents()
{
	while (SDL_PollEvent(&g_sdlManager.m_events))
	{
		if (g_sdlManager.m_events.type == SDL_QUIT)
		{
			g_quit = true;
		}

		if (g_sdlManager.m_events.type == SDL_KEYDOWN && g_sdlManager.m_events.key.repeat == 0)
		{
			switch (g_sdlManager.m_events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				g_quit = true;
				break;
			}
		}
		else if (g_sdlManager.m_events.type == SDL_KEYUP && g_sdlManager.m_events.key.repeat == 0)
		{
			switch (g_sdlManager.m_events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				g_quit = true;
				break;
			}
		}
	}
}

int _tmain(int, _TCHAR**)
{
	if (g_sdlManager.init("SpaceInvaders", 1600, 900))
	{
		float thisTime = 0.f;
		float lastTime = 0.f;

		g_assetManager.init(g_sdlManager.m_renderer);
		g_assetManager.loadAsset("hakai", AT_TEXTURE);
		g_testTexture = g_assetManager.m_allAssets["hakai"];

		while (!g_quit)
		{
			thisTime = (float)SDL_GetTicks();
			g_deltaTime = (float)(thisTime - lastTime) / 1000.0f;
			lastTime = thisTime;

			handleKeyboardEvents();

			render();
			renderDebugConsole();
		}
	}

	g_sdlManager.destroy();
	return 0;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO:  procesar mensajes de la ventana principal.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
           
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}