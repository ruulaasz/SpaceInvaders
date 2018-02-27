#include "stdafx.h"
#include "Prototype_1.h"

SDL_Renderer* g_renderer;

bool g_quit;
float g_deltaTime;

PlayerVehicle* g_player;
typedef LCF::Controller<PlayerVehicle, MovementInfo> PlayerVehicleController;
PlayerVehicleController g_playerVehicleController;

Wall* g_leftWall;
Wall* g_rightWall;

LCF::Music* g_music;

LCF::BackgroundTexture* g_background;

SkyEnemy* g_testEnemy;
GroundEnemy* g_groundEnemy;

EnemyType* g_skyEnemyType;
EnemyType* g_groundEnemyType;

WeaponType* g_mainWeaponType;
WeaponType* g_sideWeaponType;
WeaponType* g_sideWeaponType2;

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

	assetName = "wall";
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
	g_mainWeaponType = new WeaponType();
	g_mainWeaponType->m_rateOfFire = 0.2f;

	g_mainWeaponType->m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_mainweapon"));
	g_mainWeaponType->m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon_Selected"));
	g_mainWeaponType->m_weaponTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("MainWeapon"));

	g_mainWeaponType->m_shootAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_weapon_shoot"));
	g_mainWeaponType->m_shootAnimation->m_frameHeight = 32;
	g_mainWeaponType->m_shootAnimation->m_frameWidth = 90;
	g_mainWeaponType->m_shootAnimation->m_animSpeed = 0.04f;
	g_mainWeaponType->m_shootAnimation->m_numOfFrames = 8;
	g_mainWeaponType->m_shootAnimation->m_maxRepetitions = 1;
	g_mainWeaponType->m_shootAnimation->m_finished = true;

	g_sideWeaponType = new WeaponType();
	g_sideWeaponType->m_rateOfFire = 0.2f;

	g_sideWeaponType->m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_subweapon"));
	g_sideWeaponType->m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA_Selected"));
	g_sideWeaponType->m_weaponTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA"));

	g_sideWeaponType->m_shootAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_weapon_shoot"));
	g_sideWeaponType->m_shootAnimation->m_frameHeight = 32;
	g_sideWeaponType->m_shootAnimation->m_frameWidth = 90;
	g_sideWeaponType->m_shootAnimation->m_animSpeed = 0.04f;
	g_sideWeaponType->m_shootAnimation->m_numOfFrames = 8;
	g_sideWeaponType->m_shootAnimation->m_maxRepetitions = 1;
	g_sideWeaponType->m_shootAnimation->m_finished = true;

	g_sideWeaponType2 = new WeaponType();
	g_sideWeaponType2->m_rateOfFire = 0.2f;

	g_sideWeaponType2->m_shootSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("shoot_subweapon"));
	g_sideWeaponType2->m_weaponReadyTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA_Selected"));
	g_sideWeaponType2->m_weaponTexture = reinterpret_cast<LCF::Texture*>(LCF::AssetManager::GetInstance().getAsset("SideWeaponA"));

	g_sideWeaponType2->m_shootAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("main_weapon_shoot"));
	g_sideWeaponType2->m_shootAnimation->m_frameHeight = 32;
	g_sideWeaponType2->m_shootAnimation->m_frameWidth = 90;
	g_sideWeaponType2->m_shootAnimation->m_animSpeed = 0.04f;
	g_sideWeaponType2->m_shootAnimation->m_numOfFrames = 8;
	g_sideWeaponType2->m_shootAnimation->m_maxRepetitions = 1;
	g_sideWeaponType2->m_shootAnimation->m_finished = true;

	g_player = new PlayerVehicle();

	g_player->m_weapons[MAIN_WEAPON] = new MainWeapon();
	reinterpret_cast<MainWeapon*>(g_player->m_weapons[MAIN_WEAPON])->m_weaponType = g_mainWeaponType;

	g_player->m_weapons[RIGHT_WEAPON] = new SideWeapon();
	reinterpret_cast<SideWeapon*>(g_player->m_weapons[RIGHT_WEAPON])->m_weaponType = g_sideWeaponType;

	g_player->m_weapons[LEFT_WEAPON] = new SideWeapon();
	reinterpret_cast<SideWeapon*>(g_player->m_weapons[LEFT_WEAPON])->m_weaponType = g_sideWeaponType2;

	g_player->init(LCF::SDL_Manager::GetInstance().m_windowWidth, LCF::SDL_Manager::GetInstance().m_windowHeight);
	LCF::World::GetInstance().registerActor(g_player);

	g_skyEnemyType = new EnemyType();
	g_skyEnemyType->m_damage = 30;
	g_skyEnemyType->m_life = 200;
	g_skyEnemyType->m_movementSpeed = 125;

	g_skyEnemyType->m_moveAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor"));
	g_skyEnemyType->m_moveAnimation->m_frameHeight = g_skyEnemyType->m_moveAnimation->m_sprite->getHeight();
	g_skyEnemyType->m_moveAnimation->m_numOfFrames = 5;
	g_skyEnemyType->m_moveAnimation->m_frameWidth = g_skyEnemyType->m_moveAnimation->m_sprite->getWidth() / g_skyEnemyType->m_moveAnimation->m_numOfFrames;
	g_skyEnemyType->m_moveAnimation->m_animSpeed = 0.1f;

	g_skyEnemyType->m_deadAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor_dead"));
	g_skyEnemyType->m_deadAnimation->m_frameHeight = g_skyEnemyType->m_deadAnimation->m_sprite->getHeight();
	g_skyEnemyType->m_deadAnimation->m_numOfFrames = 5;
	g_skyEnemyType->m_deadAnimation->m_frameWidth = g_skyEnemyType->m_deadAnimation->m_sprite->getWidth() / g_skyEnemyType->m_deadAnimation->m_numOfFrames;
	g_skyEnemyType->m_deadAnimation->m_animSpeed = 0.1f;
	g_skyEnemyType->m_deadAnimation->m_maxRepetitions = 1;

	g_skyEnemyType->m_moveSFX = new LCF::Sfx(*reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("skyenemy")));
	g_skyEnemyType->m_deadSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("skyenemy_dead"));

	g_skyEnemyType->m_weapon = new MainWeapon();
	g_skyEnemyType->m_weapon->m_direction = DIRECTION_STOP;
	g_skyEnemyType->m_weapon->m_weaponSelected = true;

	g_testEnemy = new SkyEnemy();
	g_testEnemy->m_posX = 775;
	g_testEnemy->m_posY = 100;
	g_testEnemy->m_type = g_skyEnemyType;
	g_testEnemy->init();
	LCF::World::GetInstance().registerActor(g_testEnemy);

	g_groundEnemyType = new EnemyType();
	g_groundEnemyType->m_damage = 10;
	g_groundEnemyType->m_life = 25;
	g_groundEnemyType->m_movementSpeed = 50;
	
	g_groundEnemyType->m_moveAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor_small"));
	g_groundEnemyType->m_moveAnimation->m_frameHeight = g_groundEnemyType->m_moveAnimation->m_sprite->getHeight();
	g_groundEnemyType->m_moveAnimation->m_numOfFrames = 5;
	g_groundEnemyType->m_moveAnimation->m_frameWidth = g_groundEnemyType->m_moveAnimation->m_sprite->getWidth() / g_groundEnemyType->m_moveAnimation->m_numOfFrames;
	g_groundEnemyType->m_moveAnimation->m_animSpeed = 0.1f;
	
	g_groundEnemyType->m_deadAnimation->m_sprite = reinterpret_cast<LCF::Sprite*>(LCF::AssetManager::GetInstance().getAsset("meteor_small_dead"));
	g_groundEnemyType->m_deadAnimation->m_frameHeight = g_groundEnemyType->m_deadAnimation->m_sprite->getHeight();
	g_groundEnemyType->m_deadAnimation->m_numOfFrames = 5;
	g_groundEnemyType->m_deadAnimation->m_frameWidth = g_groundEnemyType->m_deadAnimation->m_sprite->getWidth() / g_groundEnemyType->m_deadAnimation->m_numOfFrames;
	g_groundEnemyType->m_deadAnimation->m_animSpeed = 0.1f;
	g_groundEnemyType->m_deadAnimation->m_maxRepetitions = 1;
	
	g_groundEnemyType->m_moveSFX = new LCF::Sfx(*reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("skyenemy")));
	g_groundEnemyType->m_deadSFX = reinterpret_cast<LCF::Sfx*>(LCF::AssetManager::GetInstance().getAsset("skyenemy_dead"));
	
	g_groundEnemyType->m_weapon = new MainWeapon();

	g_groundEnemy = new GroundEnemy();
	g_groundEnemy->m_direction = DIRECTION_LEFT;
	g_groundEnemy->m_type = g_groundEnemyType;
	g_groundEnemy->init();
	g_groundEnemy->m_posX = SCREEN_WIDTH - g_groundEnemy->m_sizeW;
	g_groundEnemy->m_posY = SCREEN_HEIGHT - g_groundEnemy->m_sizeH;
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
	LCF::World::GetInstance().update(g_deltaTime);
	LCF::ColliderManager::GetInstance().Update(g_deltaTime);
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