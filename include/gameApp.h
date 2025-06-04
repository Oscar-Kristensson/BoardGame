#pragma once
#include "app.h"
#include "raylib.h"
#include <optional>
#include <string>
#include <vector>
#include "dataTypes.h"
#include "entity.h"
#include "player.h"
#include "inputElement.h"
#include "dice.h"

namespace BoardGame
{

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

		bool m_UseHighFPS = false;

		BoardGame::gui::Dice m_Dice;

	public:
		Game(Vector2 boardSize, Color backgroundColor,
			std::vector<BoardGame::GameEntityData> entityData,
			uint8_t playerCount, CommonPlayerInfo commonPlayerInfo,
			std::vector<PlayerInfo> players);

		Game(GameConfigData gameData, uint8_t playerCount);

		void update() override;
		void render() override;
		void changePlayer(bool increase);
		bool getUseHighFPS() { return m_UseHighFPS; }

	};
}


