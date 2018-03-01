#include "AssetManager.h"
#include "Asset.h"
#include "Texture.h"
#include "BackgroundTexture.h"
#include "Sprite.h"
#include "Sfx.h"
#include "Music.h"
#include "message.h"

namespace LCF
{
	AssetManager::AssetManager()
	{
		m_renderer = SDL_Manager::GetInstance().m_renderer;
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

				newAsset->setName(_name);

				if (!reinterpret_cast<Texture*>(newAsset)->loadFromFile(path, m_renderer))
				{
					path = "..\\resources\\textures\\default.png";
					reinterpret_cast<Texture*>(newAsset)->loadFromFile(path, m_renderer);
					MESSAGE_WARNING("Texture not found, using default texture");
				}

				m_allAssets[_name] = newAsset;
				break;

			case AT_BACKGROUNDTEXTURE:
				newAsset = new BackgroundTexture();

				path += "background_textures\\";
				path += _name;
				path += ".png";

				newAsset->setName(_name);

				if (!reinterpret_cast<BackgroundTexture*>(newAsset)->loadFromFile(path, m_renderer))
				{
					path = "..\\resources\\background_textures\\default.png";
					reinterpret_cast<BackgroundTexture*>(newAsset)->loadFromFile(path, m_renderer);
					MESSAGE_WARNING("BackgroundTexture not found, using default texture");
				}

				m_allAssets[_name] = newAsset;
				break;

			case AT_SPRITE:
				newAsset = new Sprite();

				path += "sprites\\";
				path += _name;
				path += ".png";

				newAsset->setName(_name);

				if (!reinterpret_cast<Sprite*>(newAsset)->loadFromFile(path, m_renderer))
				{
					path = "..\\resources\\sprites\\default.png";
					reinterpret_cast<Sprite*>(newAsset)->loadFromFile(path, m_renderer);
					MESSAGE_WARNING("Sprite not found, using default texture");
				}

				m_allAssets[_name] = newAsset;
				break;

			case AT_SFX:
				newAsset = new Sfx();

				path += "sfx\\";
				path += _name;
				path += ".wav";

				newAsset->setName(_name);

				if (!reinterpret_cast<Sfx*>(newAsset)->loadFromFile(path))
				{
					path = "..\\resources\\sfx\\default.wav";
					reinterpret_cast<Sfx*>(newAsset)->loadFromFile(path);
					MESSAGE_WARNING("Sfx not found, using default sfx");
				}

				m_allAssets[_name] = newAsset;
				break;

			case AT_MUSIC:
				newAsset = new Music();

				path += "music\\";
				path += _name;
				path += ".mp3";

				newAsset->setName(_name);

				if (!reinterpret_cast<Music*>(newAsset)->loadFromFile(path))
				{
					path = "..\\resources\\music\\default.mp3";
					reinterpret_cast<Music*>(newAsset)->loadFromFile(path);
					MESSAGE_WARNING("Music not found, using default Music");
				}

				m_allAssets[_name] = newAsset;
				break;
			}
		}

		MESSAGE_SUCCESS("Asset ready");
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

	Asset * AssetManager::getAsset(std::string _name)
	{
		std::map<std::string, Asset*>::iterator it;
		it = m_allAssets.find(_name);

		if (it != m_allAssets.end())
		{
			return it->second;
		}
		else
		{
			return m_allAssets["default"];
		}
	}
}