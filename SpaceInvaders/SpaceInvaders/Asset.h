#pragma once

class Asset
{
public:
	Asset();
	virtual ~Asset();

	/**
	* Get the Name of the texture.
	*
	* @return m_name
	*
	*/
	std::string getName() { return m_name; }

	/**
	* Set the Name of the texture.
	*
	* @Param _newName
	* The new name of the texture
	*
	*/
	void setName(std::string* _newName) { m_name = *_newName; }

public:
	std::string m_name;
};