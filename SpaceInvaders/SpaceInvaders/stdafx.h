// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
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