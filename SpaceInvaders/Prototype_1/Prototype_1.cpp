#include "stdafx.h"
#include "Prototype_1.h"

SDL_Renderer* g_renderer;

bool g_quit;
float g_deltaTime;

PlayerVehicle* g_player;
typedef LCF::Controller<PlayerVehicle, MovementInfo> PlayerVehicleController;
PlayerVehicleController g_playerVehicleController;

LCF::Factory<SkyEnemy, EnemyType> g_skyEnemyFactory;
LCF::Factory<GroundEnemy, EnemyType> g_groundEnemyFactory;
LCF::Factory <MainWeapon , WeaponType > g_mainWeaponfactory;
LCF::Factory <SideWeapon, WeaponType > g_sideWeaponfactory;
LCF::Factory <MainBullet, BulletType > g_mainBulletFactory;
LCF::Factory <SubBullet, BulletType > g_subBulletFactory;

Wall* g_leftWall;
Wall* g_rightWall;

LCF::Music* g_music;

LCF::BackgroundTexture* g_background;

SkyEnemy* g_skyEnemy;
GroundEnemy* g_groundEnemy;

bool initSystems()
{
	LCF::SDL_Manager::StartModule();

	LCF::ColliderManager::StartModule();
	LCF::ColliderManager::GetInstance().Init();

	LCF::FileManager::StartModule();
	
	if (!LCF::SDL_Manager::GetInstance().init("SpaceInvaders", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		return false;
	}

	g_renderer = LCF::SDL_Manager::GetInstance().m_renderer;

	LCF::AssetManager::StartModule();
	LCF::AssetManager::GetInstance().init(g_renderer);

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

	assetName = "meteor_small";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "meteor_small_dead";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "main_weapon_shoot";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SPRITE);

	assetName = "sub_bullet_base";
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

	assetName = "skyenemy_dead";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "mainbullet_impact";
	LCF::AssetManager::GetInstance().loadAsset(assetName, AT_SFX);

	assetName = "shoot_main_enemy_weapon";
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

void initWorld()
{
	std::string route;
	g_player = new PlayerVehicle();

	route = "..\\resources\\units\\";
	route = route + "bullet\\main_bullet.txt";
	MainBullet* bullet = g_mainBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\main_weapon.txt";
	g_player->m_weapons[MAIN_WEAPON] = g_mainWeaponfactory.create(route);
	reinterpret_cast<MainWeapon*>(g_player->m_weapons[MAIN_WEAPON])->m_bulletType = bullet->m_type;

	route = "..\\resources\\units\\";
	route = route + "bullet\\sub_bullet.txt";
	SubBullet* sbullet = g_subBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\side_weapon.txt";
	g_player->m_weapons[RIGHT_WEAPON] = g_sideWeaponfactory.create(route);
	reinterpret_cast<SideWeapon*>(g_player->m_weapons[RIGHT_WEAPON])->m_bulletType = sbullet->m_type;

	route = "..\\resources\\units\\";
	route = route + "bullet\\sub_bullet.txt";
	sbullet = g_subBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\side_weapon.txt";
	g_player->m_weapons[LEFT_WEAPON] = g_sideWeaponfactory.create(route);
	reinterpret_cast<SideWeapon*>(g_player->m_weapons[LEFT_WEAPON])->m_bulletType = sbullet->m_type;

	g_player->init(LCF::SDL_Manager::GetInstance().m_windowWidth, LCF::SDL_Manager::GetInstance().m_windowHeight);
	LCF::World::GetInstance().registerActor(g_player);

	route = "..\\resources\\units\\";
	route = route + "bullet\\main_enemy_bullet.txt";
	bullet = g_mainBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "enemy\\skyenemy.txt";
	g_skyEnemy = g_skyEnemyFactory.create(route);
	g_skyEnemy->m_posX = 775;
	g_skyEnemy->m_posY = 100;

	route = "..\\resources\\units\\";
	route = route + "weapon\\main_enemy_weapon.txt";
	g_skyEnemy->m_weapon = g_mainWeaponfactory.create(route);
	g_skyEnemy->m_weapon->m_bulletType = bullet->m_type;

	g_skyEnemy->init();
	LCF::World::GetInstance().registerActor(g_skyEnemy);

	route = "..\\resources\\units\\";
	route = route + "bullet\\sub_enemy_bullet.txt";
	sbullet = g_subBulletFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "enemy\\groundenemy.txt";
	g_groundEnemy = g_groundEnemyFactory.create(route);

	route = "..\\resources\\units\\";
	route = route + "weapon\\side_enemy_weapon.txt";
	g_groundEnemy->m_weapon = g_sideWeaponfactory.create(route);
	g_groundEnemy->m_weapon->m_bulletType = sbullet->m_type;

	g_groundEnemy->m_direction = DIRECTION_LEFT;
	g_groundEnemy->m_posX = SCREEN_WIDTH - g_groundEnemy->m_type->m_moveAnimation->m_frameWidth;
	g_groundEnemy->m_posY = SCREEN_HEIGHT - g_groundEnemy->m_type->m_moveAnimation->m_frameHeight;
	g_groundEnemy->init();
	LCF::World::GetInstance().registerActor(g_groundEnemy);

	g_leftWall = new Wall();
	g_leftWall->init();

	LCF::World::GetInstance().registerActor(g_leftWall);

	g_rightWall = new Wall();
	g_rightWall->init();
	g_rightWall->m_posY = LCF::SDL_Manager::GetInstance().m_windowHeight - g_rightWall->m_sizeH;
	g_rightWall->m_posX = LCF::SDL_Manager::GetInstance().m_windowWidth - g_rightWall->m_sizeW;

	LCF::World::GetInstance().registerActor(g_rightWall);

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
	LCF::ColliderManager::GetInstance().Update(g_deltaTime);
	LCF::World::GetInstance().update(g_deltaTime);
	TextManager::GetInstance().update(g_deltaTime);
}

void render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderClear(g_renderer);

	g_background->render(0, 0, g_renderer);

	LCF::World::GetInstance().render(g_renderer);

	LCF::ColliderManager::GetInstance().Render(g_renderer);

	TextManager::GetInstance().render(g_renderer);

	SDL_RenderPresent(g_renderer);
}

void renderDebug()
{
	system("cls");
	printf("%d", TextManager::GetInstance().m_fallingText.size());
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
	if (initSystems())
	{
		float thisTime = 0.f;
		float lastTime = 0.f;

		loadContent();

		initWorld();

		initControllers();

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