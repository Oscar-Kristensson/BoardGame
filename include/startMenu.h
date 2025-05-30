#pragma once
#include "game.h"
#include <vector>
#include <string>

namespace BoardGame
{
	class StartMenu : public App
	{
	private:
		Color m_BackgroundColor;
		Color m_PlayerCountSelectBackgroundColor;
		Color m_PlayerCountSelectTextColor;
		std::vector<std::string> m_GameNames;
		uint16_t m_SelectedGame;
		uint8_t m_PlayerCount;


	public:
		StartMenu(Color backgroundColor, Color playerCountSelectBackgroundColor, Color playerCountSelectTextColor);

		void drawPlayerCountSelectMenu();
		uint8_t getPlayerCount();
		void update() override;
		std::vector<std::string> getGames();
		void render() override;
		std::string getGameName();
	};
}