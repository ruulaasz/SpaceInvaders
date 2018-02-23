// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"
#include <Windows.h>
#include <tchar.h>

#include <LCFramework.h>
#include <spiGUI.h>

#include "Pawn.h"
#include "Wall.h"
#include "SkyEnemy.h"
#include "Bullet.h"
#include "MainBullet.h"
#include "SubBullet.h"
#include "Weapon.h"
#include "MainWeapon.h"
#include "SideWeapon.h"
#include "SideWeaponB.h"
#include "PlayerVehicle.h"

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

#pragma comment(lib, "LCFramework.lib")
#pragma comment(lib, "spiGUI.lib")