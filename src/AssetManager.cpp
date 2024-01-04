#include "AssetManager.hpp"

void GatorEngine::AssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;

	if (tex.loadFromFile(fileName))
	{
		this->_textures[name] = tex;
	}
}

sf::Texture& GatorEngine::AssetManager::GetTexture(std::string name)
{
	return this->_textures.at(name);
}

void GatorEngine::AssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		this->_fonts[name] = font;
	}
}

sf::Font& GatorEngine::AssetManager::GetFont(std::string name)
{
	return this->_fonts.at(name);
}


