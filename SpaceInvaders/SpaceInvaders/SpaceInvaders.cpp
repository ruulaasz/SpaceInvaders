// SpaceInvaders.cpp: define el punto de entrada de la aplicación.
//
#include "stdafx.h"
#include "SpaceInvaders.h"

SDL_Manager g_sdlManager;
//AssetManager g_assetManager;
AudioManager g_audioManager;
//InputManager g_inputManager;

bool g_quit;
float g_deltaTime;
double g_angle;
float g_scalation;

Texture* g_testTexture;
BackgroundTexture* g_testBackgroundTexture;
Sprite* g_testSprite;
Sfx* g_testSfx;
Music* g_testMusic;

World g_World;
testActor g_Actor;
TestActorController g_Controller;
//std::vector<LCF::BaseController*> g_allControllers;

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
		//g_testTexture->renderEx(400, 225, 0.5 + g_scalation, 0.5 + g_scalation, g_angle, g_sdlManager.m_renderer);
	}

	if (g_testSprite)
	{
		g_testSprite->render(1000, 75, g_sdlManager.m_renderer);
	}

	g_World.render(g_sdlManager.m_renderer);

	SDL_RenderPresent(g_sdlManager.m_renderer);
}

void renderDebugConsole()
{
	system("cls");
	printf("Assets Loaded: %d", AssetManager::GetInstance().m_allAssets.size());
	printf("\nCurrent Jump: %d", g_testSprite->m_currentJump);
	printf("\n\nCurrent sfx Volume: %d", g_audioManager.SetSfxVolume(1, -1));
	printf("\n\nCurrent music Volume: %d", g_audioManager.SetMusicVolume(-1));
}

void loadContent()
{
	std::string assetName = "hakai";

	AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);
	g_testTexture = reinterpret_cast<Texture*>(AssetManager::GetInstance().searchAsset(assetName));

	g_Actor.m_texture = g_testTexture;
	g_Actor.m_posX = 500;
	g_Actor.m_posY = 225;

	g_Controller.addObject(&g_Actor);
	g_Controller.addFunctionAndValues(SDLK_a, &testActor::move, new testStruct(-1));
	g_Controller.addFunctionAndValues(SDLK_d, &testActor::move, new testStruct(1));
	LCF::InputManager::GetInstance().AddController(&g_Controller);
//	g_allControllers.push_back(&g_Controller);

	g_World.registerActor(&g_Actor);

	assetName = "background";

	AssetManager::GetInstance().loadAsset(assetName, AT_BACKGROUNDTEXTURE);
	g_testBackgroundTexture = reinterpret_cast<BackgroundTexture*>(AssetManager::GetInstance().searchAsset(assetName));

	assetName = "numbers";

	AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);
	g_testSprite = reinterpret_cast<Sprite*>(AssetManager::GetInstance().searchAsset(assetName));

	assetName = "bass";

	AssetManager::GetInstance().loadAsset(assetName, AT_SFX);
	g_testSfx = reinterpret_cast<Sfx*>(AssetManager::GetInstance().searchAsset(assetName));

	assetName = "song";

	AssetManager::GetInstance().loadAsset(assetName, AT_MUSIC);
	g_testMusic = reinterpret_cast<Music*>(AssetManager::GetInstance().searchAsset(assetName));
}

void handleKeyboardEvents()
{
	while (SDL_PollEvent(&g_sdlManager.m_events))
	{
		LCF::InputManager::GetInstance().dispatchInput(g_sdlManager.m_events);

		if (g_sdlManager.m_events.type == SDL_KEYDOWN)
			g_Controller.checkInput(g_sdlManager.m_events.key.keysym.sym);
			//g_allControllers[0]->checkInput(g_sdlManager.m_events.key.keysym.sym);
			

		if (g_sdlManager.m_events.type == SDL_QUIT)
		{
			g_quit = true;
		}

		/*if (g_sdlManager.m_events.type == SDL_KEYDOWN)
		{
			switch (g_sdlManager.m_events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				g_quit = true;
				break;

			case SDLK_m:
				if (g_audioManager.PausedChannel(-1))
				{
					g_audioManager.ResumeChannel(-1);
				}
				else
				{
					g_audioManager.PauseChannel(-1);
				}
				break;

			case SDLK_s:
				g_audioManager.StopChannelFadeOut(-1, 300);
				break;

			//case SDLK_d:
				//g_audioManager.SetSfxVolume(-1, 1);
				//break;

			case SDLK_f:
				g_audioManager.SetSfxVolume(-1, MIX_MAX_VOLUME);
				break;

			case SDLK_SPACE:
				g_testSfx->playFadeIn(-1, 1500);
				break;
				
			case SDLK_a:
			{
<<<<<<< HEAD
				testStruct inputValue;
				inputValue.value = -10;
				g_Controller.checkInput('A', inputValue);
=======
				g_Controller.checkInput(SDLK_a);
>>>>>>> 5ed56f09f03848d060c00ccdf9afb59debe0dd49
				
			}
			break;
			case SDLK_d:
			{
<<<<<<< HEAD
				testStruct inputValue;
				inputValue.value = 10;
				g_Controller.checkInput('D', inputValue);
=======
				g_Controller.checkInput(SDLK_d);
>>>>>>> 5ed56f09f03848d060c00ccdf9afb59debe0dd49
			}
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
		}*/
	}
}

int _tmain(int, _TCHAR**)
{
	if (g_sdlManager.init("SpaceInvaders", 1600, 900))
	{
		float thisTime = 0.f;
		float lastTime = 0.f;

		AssetManager::StartModule();
		AssetManager::GetInstance().init(g_sdlManager.m_renderer);
		
		loadContent();

		g_audioManager.SetMusicVolume(50);
		g_testMusic->playFadeIn(3000);
		g_audioManager.SetSfxVolume(-1, 30);

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