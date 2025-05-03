#pragma once
#include "game.h"

namespace BoardGame
{
	class StartMenu : public App
	{
	public:
		StartMenu()
		{

		};

		void update() override;
		void render() override;
	};
}