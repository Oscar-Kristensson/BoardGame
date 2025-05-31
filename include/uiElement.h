#pragma once
#include <stdint.h>

namespace BoardGame
{
	namespace gui
	{
		class Element
		{
		public:
			float m_X = 0;
			float m_Y = 0;
			float m_Width = 1;
			float m_Height = 1;
			uint16_t m_PaddingX = 24;
			uint16_t m_PaddingY = 8;
			bool m_Hovered = false;


		public:
			Element(float x, float y);

			void updateElement(int cursorX, int cursorY);
			bool isHoveringOver(int cursorX, int cursorY);
			
			// void virtual update();
			void virtual draw();

		};
	}
}

