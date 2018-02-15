// stdafx.h: archivo de inclusi�n de los archivos de inclusi�n est�ndar del sistema
// o archivos de inclusi�n espec�ficos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"
#include <Windows.h>
#include <tchar.h>
#include <LCFramework.h>

#include "testActor.h"
typedef LCF::Controller<testActor, testStruct> TestActorController;
#pragma comment(lib, "LCFramework.lib")