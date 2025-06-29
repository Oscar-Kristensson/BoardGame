#include "assetManager.h"
#include <stdexcept>
#include <filesystem>
#include <iostream>

BoardGame::TextureManager::TextureManager()
{
}

BoardGame::TextureManager::~TextureManager()
{
	// Unload the textures and free up memory
	for (size_t i = 0; i < m_Textures.size(); i++)
		UnloadTexture(m_Textures[i]);
}

uint16_t BoardGame::TextureManager::load(std::filesystem::path filePath, std::string name)
{
	// TBD: Add checks for if the file exists
	if (!std::filesystem::exists(filePath))
		std::cout << "Path " << filePath.string() << " does not exist" << std::endl;

	m_StringIDs[name] = m_Textures.size();
	std::string filePathString = filePath.string();
	m_Textures.emplace_back(LoadTexture(filePathString.c_str()));
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

#if _DEBUG
#include <iostream>

void BoardGame::TextureManager::printOut()
{
	std::cout << "Loaded textures\n";
	for (const auto& [stringID, id] : m_StringIDs) {
		std::cout << "Texture " << stringID << ": " << id << " " << m_Textures[id].width << "x" << m_Textures[id].height << "\n";
	}
	std::cout << std::endl;
}


#endif