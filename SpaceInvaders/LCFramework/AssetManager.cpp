#include "AssetManager.h"
#include "Asset.h"
#include "Texture.h"
#include "BackgroundTexture.h"
#include "Sprite.h"
#include "Sfx.h"
#include "Music.h"

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{

}

Asset * AssetManager::loadAsset(std::string _name, AssetType _type)
{
	std::string path = "..\\resources\\";
	Asset* newAsset = searchAsset(_name);

	if (!newAsset)
	{
		switch (_type)
		{
		default:
			break;

		case AT_TEXTURE:
			newAsset = new Texture();

			path += "textures\\";
			path += _name;
			path += ".png";

			if (reinterpret_cast<Texture*>(newAsset)->loadFromFile(path, m_renderer))
			{
				newAsset->m_name = _name;
				m_allAssets[_name] = newAsset;
			}
			break;

		case AT_BACKGROUNDTEXTURE:
			newAsset = new BackgroundTexture();

			path += "background_textures\\";
			path += _name;
			path += ".png";

			if (reinterpret_cast<BackgroundTexture*>(newAsset)->loadFromFile(path, m_renderer))
			{
				newAsset->m_name = _name;
				m_allAssets[_name] = newAsset;
			}
			break;

		case AT_SPRITE:
			newAsset = new Sprite();

			path += "sprites\\";
			path += _name;
			path += ".png";

			if (reinterpret_cast<Sprite*>(newAsset)->loadFromFile(path, m_renderer))
			{
				newAsset->m_name = _name;
				m_allAssets[_name] = newAsset;
			}
			break;

		case AT_SFX:
			newAsset = new Sfx();

			path += "sfx\\";
			path += _name;
			path += ".wav";

			if (reinterpret_cast<Sfx*>(newAsset)->loadFromFile(path))
			{
				newAsset->m_name = _name;
				m_allAssets[_name] = newAsset;
			}
			break;

		case AT_MUSIC:
			newAsset = new Music();

			path += "music\\";
			path += _name;
			path += ".mp3";

			if (reinterpret_cast<Music*>(newAsset)->loadFromFile(path))
			{
				newAsset->m_name = _name;
				m_allAssets[_name] = newAsset;
			}
			break;
		}
	}

	return newAsset;
}

Asset * AssetManager::searchAsset(std::string _name)
{
	std::map<std::string, Asset*>::iterator it;
	it = m_allAssets.find(_name);

	if (it != m_allAssets.end())	
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

void AssetManager::init(SDL_Renderer * _renderer)
{
	m_renderer = _renderer;
}