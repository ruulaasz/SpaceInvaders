#include "stdafx.h"
#include "Prototype_1.h"

SDL_Renderer* g_renderer;
float thisTime = 0.f;
float lastTime = 0.f;
bool g_quit;
float g_deltaTime;

PlayerVehicle* g_player;
typedef LCF::Controller<PlayerVehicle, MovementInfo> PlayerVehicleController;
PlayerVehicleController g_playerVehicleController;

EnemySpawner g_enemySpawner;

Wall* g_leftWall;
Wall* g_rightWall;

LCF::Music* g_music;
LCF::BackgroundTexture* g_background;

bool initSystems()
{
	LCF::SDL_Manager::StartModule();

	LCF::ColliderManager::StartModule();

	LCF::FileManager::StartModule();
	
	if (!LCF::SDL_Manager::GetInstance().init("SpaceInvaders", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return false;
	}

	g_renderer = LCF::SDL_Manager::GetInstance().m_renderer;

	LCF::AssetManager::StartModule();

	LCF::AudioManager::StartModule();

	LCF::World::StartModule();

	TextManager::StartModule();

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

	assetName = "default";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_TEXTURE);

	//SPRITES
	assetName = "main_bullet";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "main_bullet_dead";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "meteor";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "meteor_dead";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "meteor_shoot";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "main_weapon_shoot";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "sub_bullet_base";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "hooper_mecha";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "hooper_mecha_large";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "hooper_mecha_shoot";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "hooper_mecha_large_shoot";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "hooper_mecha_dead"; 
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "sideweapon_shoot_base";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	//BACKGROUNDS
	assetName = "background";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_BACKGROUNDTEXTURE);

	//SFX
	assetName = "moving";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "core_damage";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "shield_damage";
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

	assetName = "skyenemy_dead";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "skyenemy_spawn";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "hooper_dead";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "hooper_spawn";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "mainbullet_impact";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "shoot_main_enemy_weapon";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "shoot_sub_enemy_weapon";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "skyenemy_damage";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);
	
	//MUSIC
	assetName = "background_music";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_MUSIC);
}

void initControllers()
{
	//PLAYER
	g_playerVehicleController.addObject(g_player);

	//movement
	g_playerVehicleController.addFunctionAndValues(SDLK_a, SDL_KEYDOWN, &PlayerVehicle::move, new MovementInfo(DIRECTION_LEFT));
	g_playerVehicleController.addFunctionAndValues(SDLK_d, SDL_KEYDOWN, &PlayerVehicle::move, new MovementInfo(DIRECTION_RIGHT));
	g_playerVehicleController.addFunctionAndValues(SDLK_a, SDL_KEYUP, &PlayerVehicle::move, new MovementInfo(DIRECTION_STOP));
	g_playerVehicleController.addFunctionAndValues(SDLK_d, SDL_KEYUP, &PlayerVehicle::move, new MovementInfo(DIRECTION_STOP));

	//shooting
	g_playerVehicleController.addFunctionAndValues(SDLK_UP, SDL_KEYUP, &PlayerVehicle::shootMainWeapon, new MovementInfo(0));
	g_playerVehicleController.addFunctionAndValues(SDLK_RIGHT, SDL_KEYUP, &PlayerVehicle::shootRightWeapon, new MovementInfo(0));
	g_playerVehicleController.addFunctionAndValues(SDLK_LEFT, SDL_KEYUP, &PlayerVehicle::shootLeftWeapon, new MovementInfo(0));
	g_playerVehicleController.addFunctionAndValues(SDLK_SPACE, SDL_KEYUP, &PlayerVehicle::superShot, new MovementInfo(0));

	LCF::InputManager::GetInstance().AddController(&g_playerVehicleController);
}

void initPlayer()
{
	std::string route;
	g_player = new PlayerVehicle();

	route = "..\\resources\\units\\";
	route = route + "bullet\\main_bullet.txt";
	MainBullet* bullet = g_enemySpawner.m_mainBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\main_weapon.txt";
	g_player->m_weapons[MAIN_WEAPON] = g_enemySpawner.m_mainWeaponfactory.create(route);
	reinterpret_cast<MainWeapon*>(g_player->m_weapons[MAIN_WEAPON])->m_bulletType = bullet->m_type;

	route = "..\\resources\\units\\";
	route = route + "bullet\\sub_bullet.txt";
	SubBullet* sbullet = g_enemySpawner.m_subBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\side_weapon.txt";
	g_player->m_weapons[RIGHT_WEAPON] = g_enemySpawner.m_sideWeaponfactory.create(route);
	reinterpret_cast<SideWeapon*>(g_player->m_weapons[RIGHT_WEAPON])->m_bulletType = sbullet->m_type;

	route = "..\\resources\\units\\";
	route = route + "bullet\\sub_bullet.txt";
	sbullet = g_enemySpawner.m_subBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\side_weapon.txt";
	g_player->m_weapons[LEFT_WEAPON] = g_enemySpawner.m_sideWeaponfactory.create(route);
	reinterpret_cast<SideWeapon*>(g_player->m_weapons[LEFT_WEAPON])->m_bulletType = sbullet->m_type;

	g_player->m_transform.m_posX = 800;
	g_player->m_transform.m_posY = 700;
	g_player->init();
	LCF::World::GetInstance().registerActor(g_player);
}

void initWorld()
{
	g_enemySpawner.init();

	initPlayer();

	g_leftWall = new Wall();
	g_leftWall->init();

	LCF::World::GetInstance().registerActor(g_leftWall);

	g_rightWall = new Wall();
	g_rightWall->init();
	g_rightWall->m_transform.m_posY = 700;
	g_rightWall->m_transform.m_posX = LCF::SDL_Manager::GetInstance().m_windowWidth - g_rightWall->m_transform.m_sizeW;

	LCF::World::GetInstance().registerActor(g_rightWall);

	g_music = reinterpret_cast<LCF::Music*>(LCF::AssetManager::GetInstance().getAsset("background_music"));
	g_background = reinterpret_cast<LCF::BackgroundTexture*>(LCF::AssetManager::GetInstance().getAsset("background"));

	//g_music->playFadeIn(1500);
	LCF::AudioManager::GetInstance().SetMusicVolume(15);
	LCF::AudioManager::GetInstance().SetSfxVolume(-1, 25);
}

void init()
{
	initSystems();

	loadContent();

	initWorld();

	initControllers();
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
	TextManager::GetInstance().update(g_deltaTime);
}

void renderDebug()
{
	system("cls");
	printf("%d", TextManager::GetInstance().m_fallingText.size());
}

void render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderClear(g_renderer);
	
	LCF::SDL_Manager::GetInstance().RenderTexture(LCF::Transform(0.0f,0.0f, g_background->getWidth(), g_background->getHeight(), 0.0f), g_background);

	LCF::World::GetInstance().render();

	LCF::ColliderManager::GetInstance().Render(g_renderer);

	TextManager::GetInstance().render(g_renderer);

	//renderDebug();

	SDL_RenderPresent(g_renderer);
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

int _tmain(int /*argc*/, char** /*argv*/)
{
	init();

	g_enemySpawner.create(SKY_ENEMY, 775.f, -100.f);

	float m_spawnTimer = 0.0f;
	float m_spawnTime = 5.0f;

	float m_spawnLargeTimer = 13.0f;
	float m_spawnLargeTime = 13.0f;

	while (!g_quit)
	{
		thisTime = (float)SDL_GetTicks();
		g_deltaTime = (float)(thisTime - lastTime) / 1000.0f;
		lastTime = thisTime;

		m_spawnTimer += g_deltaTime;
		m_spawnLargeTimer += g_deltaTime;

		if (m_spawnTimer >= m_spawnTime)
		{
			g_enemySpawner.create(GROUND_ENEMY, 1600.f, 713, DIRECTION_LEFT);
			//g_enemySpawner.create(GROUND_ENEMY, -100.f, 713, DIRECTION_RIGHT);
			m_spawnTimer = 0.0f;
		}

		if (m_spawnLargeTimer >= m_spawnLargeTime)
		{
			g_enemySpawner.create(GROUND_ENEMY_LARGE, -100.f, 700, DIRECTION_RIGHT);
			//g_enemySpawner.create(GROUND_ENEMY_LARGE, 1600.f, 700, DIRECTION_LEFT);

			m_spawnLargeTimer = 0.0f;
		}

		handleInputs();

		update();

		render();
	}
	

	LCF::SDL_Manager::GetInstance().destroy();
	return 0;
}