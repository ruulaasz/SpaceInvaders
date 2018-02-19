#pragma once

#include <string>
#include <map>
#include "SDL_Manager.h"
#include "Module.h"
#include "Asset.h"

/**
* Enum of Asset Types
*/
enum AssetType
{
	AT_TEXTURE = 0,
	AT_BACKGROUNDTEXTURE,
	AT_SPRITE,
	AT_SFX,
	AT_MUSIC
};

namespace LCF
{
	/**
	* Manager class for Assets
	*/
	class AssetManager : public LCF::Module<AssetManager>
	{
	public:
		AssetManager();
		virtual ~AssetManager();

		/**
		* Load the given type of asset
		*
		* @param _name
		* a string with the asset name
		*
		* @param _type
		* the tyoe if asset to load
		*
		* @return Asset
		* a pointer to the loaded asset, null if the loading fails
		*
		*/
		Asset* loadAsset(std::string _name, AssetType _type);

		/**
		* Search an asset by name
		*
		* @param _name
		* a string with the asset name
		*
		* @return Asset
		* a pointer to the found asset, null if the search fails
		*
		*/
		Asset* searchAsset(std::string _name);

		/**
		* Dispatch any kind of message
		*
		* @param _renderer
		* a sdl renderer
		*
		*/
		void init(SDL_Renderer* _renderer);

	public:
		std::map<std::string, Asset*> m_allAssets;

	private:
		SDL_Renderer* m_renderer;
	};
}