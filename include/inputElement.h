#pragma once
#include "uiElement.h"
#include <string>

namespace BoardGame
{
	namespace gui
	{
		class ValueInput : public BoardGame::gui::Element
		{
		private:
			int m_Value = 0;
			std::string m_ValueString = "0";
			uint8_t m_FontSize = 48;
			
		public:
			ValueInput(float x, float y);
			ValueInput();
			void draw() override;
			void update(int cursorX, int cursorY); 
			void setValue(int value);
			int getValue();
			void updateSize();
		};
	}
}