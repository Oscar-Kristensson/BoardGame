#pragma once
#include "game.h"

namespace BoardGame
{
	class StartMenu : public App
	{
	private:
		Color m_BackgroundColor;
	public:
		StartMenu(Color backgroundColor);

		void update() override;
		void render() override;
	};
}