// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"
#include <Windows.h>
#include <tchar.h>
#include <LCFramework.h>

#include "Pawn.h"
#include "Wall.h"
#include "Bullet.h"
#include "MainBullet.h"
#include "SubBullet.h"
#include "Weapon.h"
#include "MainWeapon.h"
#include "SideWeapon.h"
#include "SideWeaponB.h"
#include "PlayerVehicle.h"

#define PLAYERMOVEMENT_SFXCHANNEL 1
#define MAINWEAPON_CASKET_SFXCHANNEL 2
#define CHANGEWEAPON_SFXCHANNEL 3
#define MAINWEAPON_SHOOT_SFXCHANNEL 4
#define SUBWEAPON_SHOOT_SFXCHANNEL 5

#define MAX_NUMBER_TO_THE_LEFT -2
#define MAX_NUMBER_TO_THE_RIGHT 2

#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT -1
#define DIRECTION_UP -2
#define DIRECTION_DOWN 2
#define DIRECTION_STOP 0

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#pragma comment(lib, "LCFramework.lib")