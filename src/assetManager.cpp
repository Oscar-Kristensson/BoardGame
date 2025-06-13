#include "assetManager.h"
#include <stdexcept>


BoardGame::TextureManager::TextureManager()
{
}

uint16_t BoardGame::TextureManager::load(std::string filePath, std::string name)
{
	m_StringIDs[name] = m_Textures.size();
	m_Textures.emplace_back(LoadTexture(filePath.c_str()));
	return m_Textures.size() - 1;
}

uint16_t BoardGame::TextureManager::getID(std::string name)
{
	return m_StringIDs[name.c_str()];
}

Texture2D* BoardGame::TextureManager::getTexture(uint16_t id)
{
	if (!(id < m_Textures.size()))
		throw std::out_of_range("Unvalid texture ID");

	return &(m_Textures[id]);

}
