// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows
// Archivos de encabezado de Windows:
#include <windows.h>

// Archivos de encabezado en tiempo de ejecución de C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include <SDL.h>
#include <SDL_image.h>

#include "SDL_Manager.h"
#include "Asset.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Sprite.h"
#include "BackgroundTexture.h"
#include "Audio.h"
#include "Sfx.h"
#include "Music.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")