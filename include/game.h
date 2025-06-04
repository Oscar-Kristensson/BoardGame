#pragma once



#include "raylib.h"
#include "dataTypes.h"
#include "constants.h"
#include "entity.h"
#include "utils.h"
#include "app.h"
#include "startMenu.h"
#include "parser.h"
#include "player.h"
#include "inputElement.h"
#include "debugScreen.h"
#include "dice.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include <optional>


namespace BoardGame 
{
	/**
	 * @brief Maps the phrase in the parsed file to the type (enum)
	 */
	const std::unordered_map<std::string, EntityType> entityMap =
	{
		{"Entity", TypeEntity},
		{"GameInfo", TypeGameInfo},
		{"StartMenu", TypeStartMenuInfo},
		{"CommonPlayerInfo", TypeCommonPlayerInfo},
		{"PlayerInfo", TypePlayerInfo},
		{"DiceInfo", TypeDiceInfo}
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
		BoardGame::gui::ValueInput m_PlayerNumberDisplayUnit;
		std::vector<int> m_PlayerBankBalance;
		uint8_t m_CurrentPlayerID = 0;

		bool m_UseHighFPS = false;

		std::vector<BoardGame::gui::Dice> m_Die;

#if _DEBUG
		bool m_ShowDebugScreen = true;
#endif


	public:
		Game(Vector2 boardSize, Color backgroundColor, 
			std::vector<BoardGame::GameEntityData> entityData,
			uint8_t playerCount, CommonPlayerInfo commonPlayerInfo,
			std::vector<PlayerInfo> players, std::vector<DiceInfo> dieData,
			int turnDisplayX, int turnDisplayY, int bankDisplayX,
			int bankDisplayY);

		Game(GameConfigData gameData, uint8_t playerCount);

		void update() override;
		void render() override;
		void changePlayer(bool increase);
		bool getUseHighFPS() { return m_UseHighFPS; }
		
	};


	int convertCPToPixels(float cp);
	float convertPixelsToCP(int pixels);

};
