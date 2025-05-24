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
		std::vector<std::string> m_GameNames;
		uint16_t m_SelectedGame;
	public:
		StartMenu(Color backgroundColor);

		void update() override;
		std::vector<std::string> getGames();
		void render() override;
		std::string getGameName();
	};
}