#pragma once
#include "uiElement.h"
#include "raylib.h"
#include "dataTypes.h"
#include "constants.h"

namespace BoardGame
{
	namespace gui
	{
		class Label : public Element
		{
		private:
			std::string m_Text;
			uint8_t m_FontSize;
			TextAlignment m_TextAlignment;

		public:
			Label() = default;
			Label(float x, float y, uint8_t fontSize, std::string text, TextAlignment textAlignment);
			Label(LabelInfo labelInfo);

			void draw() override;

		};
	}
}