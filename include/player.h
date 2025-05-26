#pragma once
#include "entity.h"

namespace BoardGame
{
	class Player
	{
	private:
		// These are the center coordinates of the player
		int m_X;
		int m_Y;

	public:
		Player(int x, int y);

		void draw();
	};
}