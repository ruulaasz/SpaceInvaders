// SpaceInvaders.cpp: define el punto de entrada de la aplicación.
//
#include "stdafx.h"
#include "SpaceInvaders.h"

typedef LCF::Controller<VerticalActor, VerticalStruct> VerticalActorController;

SDL_Renderer* g_renderer;

bool g_quit;
float g_deltaTime;
double g_angle;
float g_scalation;

LCF::BackgroundTexture* g_testBackgroundTexture;
LCF::Sprite* g_testSprite;
LCF::Sfx* g_testSfx;
LCF::Music* g_testMusic;

LCF::World g_world;

VerticalActor g_verticalActor;
VerticalActorController g_verticalActorController;

bool init()
{
	LCF::SDL_Manager::StartModule();

	if (!LCF::SDL_Manager::GetInstance().init("SpaceInvaders", 1600, 900))
	{
		return false;
	}

	g_renderer = LCF::SDL_Manager::GetInstance().m_renderer;

	LCF::AssetManager::StartModule();
	LCF::AssetManager::GetInstance().init(g_renderer);

	LCF::AudioManager::StartModule();

	LCF::AudioManager::GetInstance().SetMusicVolume(50);
	LCF::AudioManager::GetInstance().SetSfxVolume(-1, 30);

	return true;
}

void update()
{
	g_testSprite->update(g_deltaTime);
	g_angle += g_deltaTime*4;
	g_scalation += g_deltaTime/100;
}

void render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	
	if (g_testBackgroundTexture)
	{
		g_testBackgroundTexture->render(0, 0, g_renderer);
	}

	if (g_testSprite)
	{
		g_testSprite->render(1000, 75, g_renderer);
	}

	g_world.render(g_renderer);

	SDL_RenderPresent(g_renderer);
}

void renderDebugConsole()
{
	system("cls");
	printf("Assets Loaded: %d", LCF::AssetManager::GetInstance().m_allAssets.size());
	printf("\nCurrent Jump: %d", g_testSprite->m_currentJump);
	printf("\n\nCurrent sfx Volume: %d", LCF::AudioManager::GetInstance().SetSfxVolume(1, -1));
	printf("\n\nCurrent music Volume: %d", LCF::AudioManager::GetInstance().SetMusicVolume(-1));
	printf("\n\nNumber of Controllers: %d", LCF::InputManager::GetInstance().GetControllerNumber());
}

void loadContent()
{
	std::string assetName = "hakai";

	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);
	g_verticalActor.m_texture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().searchAsset(assetName));

	g_verticalActor.m_posX = 500;
	g_verticalActor.m_posY = 225;

	g_verticalActorController.addObject(&g_verticalActor);
	g_verticalActorController.addFunctionAndValues(SDLK_a, SDL_KEYUP,&VerticalActor::move, new VerticalStruct(-1));
	g_verticalActorController.addFunctionAndValues(SDLK_d, SDL_KEYDOWN,&VerticalActor::move, new VerticalStruct(1));
	LCF::InputManager::GetInstance().AddController(&g_verticalActorController);

	g_world.registerActor(&g_verticalActor);

	assetName = "background";

	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_BACKGROUNDTEXTURE);
	g_testBackgroundTexture = reinterpret_cast<LCF::BackgroundTexture*>(LCF::AssetManager::GetInstance().searchAsset(assetName));

	assetName = "numbers";

	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);
	g_testSprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().searchAsset(assetName));

	assetName = "bass";

	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);
	g_testSfx = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().searchAsset(assetName));

	assetName = "song";

	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_MUSIC);
	g_testMusic = reinterpret_cast<LCF::Music*>(LCF::AssetManager::GetInstance().searchAsset(assetName));
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

		g_testMusic->playFadeIn(3000);

		while (!g_quit)
		{
			thisTime = (float)SDL_GetTicks();
			g_deltaTime = (float)(thisTime - lastTime) / 1000.0f;
			lastTime = thisTime;

			handleInputs();

			update();

			render();
			renderDebugConsole();
		}
	}

	LCF::SDL_Manager::GetInstance().destroy();
	return 0;
}
