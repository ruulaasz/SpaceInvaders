#include "stdafx.h"
#include "Prototype_1.h"

SDL_Renderer* g_renderer;

bool g_quit;
float g_deltaTime;

PlayerVehicle g_player;
typedef LCF::Controller<PlayerVehicle, MovementInfo> PlayerVehicleController;
PlayerVehicleController g_playerVehicleController;

Wall g_leftWall;
Wall g_rightWall;

LCF::Music* g_music;

LCF::BackgroundTexture* g_background;

SkyEnemy g_testEnemy;

bool initSystems()
{
	LCF::SDL_Manager::StartModule();

	LCF::ColliderManager::StartModule();
	LCF::ColliderManager::GetInstance().Init();

	if (!LCF::SDL_Manager::GetInstance().init("SpaceInvaders", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return false;
	}

	g_renderer = LCF::SDL_Manager::GetInstance().m_renderer;

	LCF::AssetManager::StartModule();
	LCF::AssetManager::GetInstance().init(g_renderer);

	LCF::AudioManager::StartModule();

	LCF::World::StartModule();

	return true;
}

void loadContent()
{
	//TEXTURES
	std::string assetName = "MainWeapon";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	assetName = "MainWeapon_Selected";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	assetName = "SideWeaponA";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	assetName = "SideWeaponA_Selected";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	assetName = "wall";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	assetName = "sub_bullet_base";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	assetName = "default";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	//SPRITES
	assetName = "main_bullet";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "meteor";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	//BACKGROUNDS
	assetName = "background";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_BACKGROUNDTEXTURE);

	//SFX
	assetName = "moving";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "after_shoot_subweapon";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "change_weapon";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "shoot_mainweapon";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "shoot_subweapon";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "skyenemy";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	//MUSIC
	assetName = "background_music";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_MUSIC);
}

void initControllers()
{
	//PLAYER
	g_playerVehicleController.addObject(&g_player);

	//movement
	g_playerVehicleController.addFunctionAndValues(SDLK_a, SDL_KEYDOWN, &PlayerVehicle::move, new MovementInfo(DIRECTION_LEFT));
	g_playerVehicleController.addFunctionAndValues(SDLK_d, SDL_KEYDOWN, &PlayerVehicle::move, new MovementInfo(DIRECTION_RIGHT));
	g_playerVehicleController.addFunctionAndValues(SDLK_a, SDL_KEYUP, &PlayerVehicle::move, new MovementInfo(DIRECTION_STOP));
	g_playerVehicleController.addFunctionAndValues(SDLK_d, SDL_KEYUP, &PlayerVehicle::move, new MovementInfo(DIRECTION_STOP));

	//shooting
	g_playerVehicleController.addFunctionAndValues(SDLK_UP, SDL_KEYUP, &PlayerVehicle::shootMainWeapon, new MovementInfo(0));
	g_playerVehicleController.addFunctionAndValues(SDLK_RIGHT, SDL_KEYUP, &PlayerVehicle::shootRightWeapon, new MovementInfo(0));
	g_playerVehicleController.addFunctionAndValues(SDLK_LEFT, SDL_KEYUP, &PlayerVehicle::shootLeftWeapon, new MovementInfo(0));

	LCF::InputManager::GetInstance().AddController(&g_playerVehicleController);
}

void initWorld()
{
	g_player.init(LCF::SDL_Manager::GetInstance().m_windowWidth, LCF::SDL_Manager::GetInstance().m_windowHeight);
	LCF::World::GetInstance().registerActor(&g_player);

	g_testEnemy.init();
	LCF::World::GetInstance().registerActor(&g_testEnemy);

	g_leftWall.init();

	LCF::World::GetInstance().registerActor(&g_leftWall);

	g_rightWall.init();
	g_rightWall.m_posY = LCF::SDL_Manager::GetInstance().m_windowHeight - g_rightWall.m_sizeH;
	g_rightWall.m_posX = LCF::SDL_Manager::GetInstance().m_windowWidth - g_rightWall.m_sizeW;

	LCF::World::GetInstance().registerActor(&g_rightWall);

	g_music = reinterpret_cast<LCF::Music*>(LCF::AssetManager::GetInstance().getAsset("background_music"));
	g_background = reinterpret_cast<LCF::BackgroundTexture*>(LCF::AssetManager::GetInstance().getAsset("background"));

	g_music->playFadeIn(1500);
	LCF::AudioManager::GetInstance().SetMusicVolume(15);
	LCF::AudioManager::GetInstance().SetSfxVolume(-1, 15);
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

void update()
{
	LCF::World::GetInstance().update(g_deltaTime);
	LCF::ColliderManager::GetInstance().Update(g_deltaTime);
}

void render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderClear(g_renderer);

	g_background->render(0, 0, g_renderer);

	LCF::World::GetInstance().render(g_renderer);

	LCF::ColliderManager::GetInstance().Render(g_renderer);

	SDL_RenderPresent(g_renderer);
}

void renderDebug()
{
	system("cls");
	printf("%d", g_testEnemy.m_damageText.size());
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
	if (initSystems())
	{
		float thisTime = 0.f;
		float lastTime = 0.f;

		loadContent();

		initControllers();

		initWorld();

		while (!g_quit)
		{
			thisTime = (float)SDL_GetTicks();
			g_deltaTime = (float)(thisTime - lastTime) / 1000.0f;
			lastTime = thisTime;

			handleInputs();

			update();

			render();

			//renderDebug();
		}
	}

	LCF::SDL_Manager::GetInstance().destroy();
	return 0;
}