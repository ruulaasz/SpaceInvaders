// stdafx.h: archivo de inclusi�n de los archivos de inclusi�n est�ndar del sistema
// o archivos de inclusi�n espec�ficos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#define MAX_NUMBER_TO_THE_LEFT -2
#define MAX_NUMBER_TO_THE_RIGHT 2

#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT -1
#define DIRECTION_UP -2
#define DIRECTION_DOWN 2
#define DIRECTION_STOP 0

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MAIN_WEAPON 0
#define RIGHT_WEAPON 1
#define LEFT_WEAPON 2
#define NUMBEROF_PLAYERWEAPONS 3

#define SKY_ENEMY 0
#define GROUND_ENEMY 1
#define GROUND_ENEMY_LARGE 2

#include "targetver.h"
#include <Windows.h>
#include <tchar.h>

#include <LCFramework.h>
#include <spiGUI.h>

#include "Pawn.h"

#include "Wall.h"

#include "BulletType.h"
#include "Bullet.h"
#include "MainBullet.h"
#include "SubBullet.h"

#include "WeaponType.h"
#include "Weapon.h"
#include "MainWeapon.h"
#include "SideWeapon.h"

#include "PlayerVehicle.h"

#include "EnemyType.h"
#include "Enemy.h"
#include "SkyEnemy.h"
#include "GroundEnemy.h"

#include "Spawner.h"
#include "EnemySpawner.h"

#pragma comment(lib, "LCFramework.lib")
#pragma comment(lib, "spiGUI.lib")