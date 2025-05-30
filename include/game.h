#pragma once


#include "raylib.h"
#include "dataTypes.h"
#include "entity.h"
#include "utils.h"
#include "app.h"
#include "startMenu.h"
#include "parser.h"
#include "player.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>


namespace BoardGame 
{
	namespace paths
	{
		const std::filesystem::path gamesDirPath = "games";
		const std::filesystem::path gameDataTextFilePath = "game.txt";

	}

	const std::unordered_map<std::string, EntityType> entityMap =
	{
		{"Entity", TypeEntity},
		{"GameInfo", TypeGameInfo},
		{"StartMenu", TypeStartMenuInfo}
	};






	class Game : public App
	{
	private:
		Camera2D m_Camera = { 0 };
        Vector2 m_BoardSize;
		Color m_BackgroundColor;
		std::vector<BoardGame::Entity> m_Entities;
		std::vector<BoardGame::Player> m_Players;

	public:
		Game(Vector2 boardSize, Color backgroundColor, std::vector<BoardGame::GameEntityData> entityData);
		
		void update() override;
		void render() override;
	};


	int convertCPToPixels(float cp);
	float convertPixelsToCP(int pixels);

};
