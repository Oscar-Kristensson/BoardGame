#pragma once



#include "raylib.h"
#include "dataTypes.h"
#include "entity.h"
#include "utils.h"
#include "app.h"
#include "startMenu.h"
#include "parser.h"
#include "player.h"
#include "inputElement.h"
#include "debugScreen.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include <optional>


namespace BoardGame 
{
	namespace paths
	{
		const std::filesystem::path gamesDirPath = "games";
		const std::filesystem::path gameDataTextFilePath = "game.txt";
	}

	namespace constants
	{
		constexpr uint8_t playerColorsLength = 8;
		const Color playerColors[playerColorsLength] = {
			{255, 42, 42, 255},		// red
			{0, 155, 0, 255},		// green
			{42, 42, 255, 255},		// blue
			{255, 255, 42, 255},	// yellow
			{148, 42, 255, 255},	// purple
			{255, 148, 42, 255},	// orange
			{42, 255, 255, 255},	// turkoise
			{255, 42, 255, 255},	// pink
		};
	}

	const std::unordered_map<std::string, EntityType> entityMap =
	{
		{"Entity", TypeEntity},
		{"GameInfo", TypeGameInfo},
		{"StartMenu", TypeStartMenuInfo},
		{"CommonPlayerInfo", TypeCommonPlayerInfo},
		{"PlayerInfo", TypePlayerInfo}
	};






	class Game : public App
	{
	private:
		Camera2D m_Camera = { 0 };
        Vector2 m_BoardSize;
		Color m_BackgroundColor;
		std::vector<BoardGame::Entity> m_Entities;
		std::vector<BoardGame::Player> m_Players;
		CommonPlayerInfo m_CommonPlayerInfo;
		std::optional<BoardGame::gui::ValueInput> m_PlayerBankInput;
		BoardGame::gui::ValueInput m_PlayerNumberDisplayUnit = BoardGame::gui::ValueInput(32, 20);
		std::vector<int> m_PlayerBankBalance;
		uint8_t m_CurrentPlayerID = 0;

	public:
		Game(Vector2 boardSize, Color backgroundColor, 
			std::vector<BoardGame::GameEntityData> entityData,
			uint8_t playerCount, CommonPlayerInfo commonPlayerInfo,
			std::vector<PlayerInfo> players);

		Game(GameConfigData gameData, uint8_t playerCount);

		void update() override;
		void render() override;
		void changePlayer(bool increase);
		
	};


	int convertCPToPixels(float cp);
	float convertPixelsToCP(int pixels);

};
