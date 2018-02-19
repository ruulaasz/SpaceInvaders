#include "stdafx.h"
#include "Prototype_1.h"

SDL_Renderer* g_renderer;

bool g_quit;
float g_deltaTime;

LCF::World g_world;

bool init()
{
	LCF::SDL_Manager::StartModule();

	LCF::ColliderManager::StartModule();
	LCF::ColliderManager::GetInstance().Init();

	if (!LCF::SDL_Manager::GetInstance().init("SpaceInvaders", 1600, 900))
	{
		return false;
	}

	g_renderer = LCF::SDL_Manager::GetInstance().m_renderer;

	LCF::AssetManager::StartModule();
	LCF::AssetManager::GetInstance().init(g_renderer);

	LCF::AudioManager::StartModule();

	return true;
}

void update()
{
	LCF::ColliderManager::GetInstance().Update(g_deltaTime);
}

void render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	g_world.render(g_renderer);

	SDL_RenderPresent(g_renderer);
}

void loadContent()
{

}

void handleInputs()
{
	while (SDL_PollEvent(&LCF::SDL_Manager::GetInstance().m_events))
	{
		LCF::InputManager::GetInstance().dispatchInput(LCF::SDL_Manager::GetInstance().m_events);

		if (LCF::SDL_Manager::GetInstance().m_events.type == SDL_QUIT)
		{
			g_quit = true;
		}

		if (LCF::SDL_Manager::GetInstance().m_events.type == SDL_KEYDOWN)
		{
			switch (LCF::SDL_Manager::GetInstance().m_events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				g_quit = true;
				break;
			}
		}
	}
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

int _tmain(int argc, char **argv)
{
	if (init())
	{

		float thisTime = 0.f;
		float lastTime = 0.f;

		loadContent();

		while (!g_quit)
		{
			thisTime = (float)SDL_GetTicks();
			g_deltaTime = (float)(thisTime - lastTime) / 1000.0f;
			lastTime = thisTime;

			handleInputs();

			update();

			render();
		}
	}

	LCF::SDL_Manager::GetInstance().destroy();
	return 0;
}