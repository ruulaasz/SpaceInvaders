#include "stdafx.h"

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

			path += "img\\";
			path += _name;
			path += ".png";

			reinterpret_cast<Texture*>(newAsset)->loadFromFile(path, m_renderer);
			newAsset->m_name = _name;

			if (reinterpret_cast<Texture*>(newAsset)->m_sdlTexture)
			{
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