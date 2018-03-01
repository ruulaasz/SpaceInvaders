#pragma once

#include "Asset.h"
#include "SDL_Manager.h"

namespace LCF
{
	/**
	* A container class for an Audio
	*/
	class Audio : public LCF::Asset
	{
	public:
		Audio();
		virtual ~Audio();
	};
}