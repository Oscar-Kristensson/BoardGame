#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>
#include "raylib.h"



namespace BoardGame
{
	class TextureManager
	{
	private:
		std::vector<Texture2D> m_Textures;
		std::unordered_map<std::string, uint16_t> m_StringIDs;
		uint16_t m_TextureCount = 0;

	public:
		TextureManager();
		~TextureManager();
		uint16_t load(std::filesystem::path filePath, std::string name);
		uint16_t getID(std::string name);
		Texture2D* getTexture(uint16_t id);

#if _DEBUG
		void printOut();
#endif

		// Add a destructor that unloads the textures

	};
}