#pragma once
#include "stdafx.h"

/**
* Container class for a SDL 2.0 texture.
*/
class Texture
{
public:
	Texture();
	virtual ~Texture();

	/**
	* Loads a texture from a file.
	*
	* @param _path
	* String to the file direction.
	*
	* @param _renderer
	* Reference to a SDL_Renderer.
	*
	*/
	bool loadFromFile(std::string _path, SDL_Renderer* _renderer);

	/**
	* Render the texture in a given screen coordinate.
	*
	* @param _x
	* Position in the x axis of the screen.
	*
	* @param _y
	*  Position in the y axis of the screen.
	*
	* @param _renderer
	* Reference to a SDL_Renderer.
	*
	*/
	void render(int _x, int _y, SDL_Renderer* _renderer);

	/**
	* Free the texture from the memory.
	*
	*/
	void free();

	/**
	* Get the Width of the texture.
	*
	* @return m_width
	*
	*/
	int getWidth() { return m_width; };

	/**
	* Get the Height of the texture.
	*
	* @return m_height
	*
	*/
	int getHeight() { return m_height; };

	/**
	* Get the Name of the texture.
	*
	* @return m_name
	*
	*/
	std::string getName(){ return m_name; }

	/**
	* Set the Name of the texture.
	*
	* @Param _newName
	* The new name of the texture
	*
	*/
	void setName(std::string* _newName){ m_name = *_newName; }

public:
	SDL_Texture* m_sdlTexture;

private:
	int m_width;
	int m_height;
	std::string m_name;
};