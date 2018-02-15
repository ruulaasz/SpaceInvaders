#pragma once

#include <string>
#include <map>
#include "SDL_Manager.h"
#include "Module.h"

enum AssetType
{
	AT_TEXTURE = 0,
	AT_BACKGROUNDTEXTURE,
	AT_SPRITE,
	AT_SFX,
	AT_MUSIC
};

class Asset;

class AssetManager : public LFC::Module<AssetManager>
{
public:
	AssetManager();
	virtual ~AssetManager();

	Asset* loadAsset(std::string _name, AssetType _type);
	Asset* searchAsset(std::string _name);
	void init(SDL_Renderer* _renderer);

public:
	std::map<std::string, Asset*> m_allAssets;

private:
	SDL_Renderer* m_renderer;
};