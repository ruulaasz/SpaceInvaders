// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"
#include <Windows.h>
#include <tchar.h>
#include <LCFramework.h>

#include "Wall.h"
#include "MainBullet.h"
#include "SubBullet.h"
#include "SideWeapon.h"
#include "PlayerVehicle.h"

#define PLAYERMOVEMENT_SFXCHANNEL 1
#define MAINWEAPON_CASKET_SFXCHANNEL 2
#define CHANGEWEAPON_SFXCHANNEL 3
#define MAINWEAPON_SHOOT_SFXCHANNEL 4
#define SUBWEAPON_SHOOT_SFXCHANNEL 5

#pragma comment(lib, "LCFramework.lib")