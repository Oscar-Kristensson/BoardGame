#pragma once
#include "entity.h"
#include "mouseDragController.h"

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

	public:
		BoardGame::DragController m_DragController;


	public:
		Player() : Player(0, 0, GRAY) {}
		Player(int x, int y, Color color);

		void draw(float scale, bool isSelected);
		bool mouseHovers(int cursorX, int cursorY, float scale);
		void move(int x, int y);
	};
}