// SpaceInvaders.cpp: define el punto de entrada de la aplicación.
//
#include "stdafx.h"
#include "SpaceInvaders.h"

SDL_Manager g_sdlManager;
AssetManager g_assetManager;

bool g_quit;
float g_deltaTime;
double g_angle;
float g_scalation;

Texture* g_testTexture;
BackgroundTexture* g_testBackgroundTexture;
Sprite* g_testSprite;
CWorld g_world;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void update()
{
	g_testSprite->update(g_deltaTime);
	g_angle += g_deltaTime*4;
	g_scalation += g_deltaTime/100;
}

void render()
{
	SDL_SetRenderDrawColor(g_sdlManager.m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_sdlManager.m_renderer);
	
	if (g_testBackgroundTexture)
	{
		g_testBackgroundTexture->render(0, 0, g_sdlManager.m_renderer);
	}

	if (g_testTexture)
	{
		g_testTexture->renderEx(400, 225, 0.5 + g_scalation, 0.5 + g_scalation, g_angle, g_sdlManager.m_renderer);
	}

	if (g_testSprite)
	{
		g_testSprite->render(1000, 200, g_sdlManager.m_renderer);
	}

	SDL_RenderPresent(g_sdlManager.m_renderer);
}

void renderDebugConsole()
{
	system("cls");
	printf("Assets Loaded: %d", g_assetManager.m_allAssets.size());
	printf("\nCurrent Jump: %d", g_testSprite->m_currentJump);
}

void loadContent()
{
	std::string assetName = "hakai";

	g_assetManager.loadAsset(assetName, AT_TEXTURE);
	g_testTexture = reinterpret_cast<Texture*>(g_assetManager.searchAsset(assetName));

	assetName = "background";

	g_assetManager.loadAsset(assetName, AT_BACKGROUNDTEXTURE);
	g_testBackgroundTexture = reinterpret_cast<BackgroundTexture*>(g_assetManager.searchAsset(assetName));

	assetName = "numbers";

	g_assetManager.loadAsset(assetName, AT_SPRITE);
	g_testSprite = reinterpret_cast<Sprite*>(g_assetManager.searchAsset(assetName));
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
		
		loadContent();

		while (!g_quit)
		{
			thisTime = (float)SDL_GetTicks();
			g_deltaTime = (float)(thisTime - lastTime) / 1000.0f;
			lastTime = thisTime;

			handleKeyboardEvents();

			update();

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