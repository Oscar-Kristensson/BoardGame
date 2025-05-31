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
		const uint8_t m_Id;
		static const int k_Width = 250;
		static const int k_Height = 400;
		static const int k_Radius = 100;
		const Color m_Color;

		bool m_IsDragged = false;

	public:
		Player() : Player(0, 0, GRAY) {}
		Player(int x, int y, Color color);

		void draw(float scale, bool isSelected);
		bool mouseHovers(int cursorX, int cursorY, float scale);
		bool isDragged();
		void startDragging();
		void stopDragging();
		void move(int x, int y);
	};
}