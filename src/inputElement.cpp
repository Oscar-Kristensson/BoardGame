#include "inputElement.h"
#include "utils.h"
#include "raylib.h"
#include <string>

BoardGame::gui::ValueInput::ValueInput()
	: Element(0, 0)
{
}


BoardGame::gui::ValueInput::ValueInput(float x, float y, bool requireHover)
	: Element(x, y), m_RequireHover(requireHover)
{
	updateSize();
	m_Height = m_FontSize + m_PaddingY * 2;
}

void BoardGame::gui::ValueInput::update(int cursorX, int cursorY)
{
	updateElement(cursorX, cursorY);
	
	if ((!m_RequireHover || m_Hovered) && (IsKeyPressed(KEY_P) || IsKeyPressedRepeat(KEY_P)))
	{
		if (IsKeyDown(KEY_LEFT_SHIFT))
			if (IsKeyDown(KEY_LEFT_CONTROL))
				setValue(m_Value + 100);
			else
				setValue(m_Value + 10);
		else
			if (IsKeyDown(KEY_LEFT_CONTROL))
				setValue(m_Value + 5);
			else
				setValue(m_Value + 1);

	}
	else if ((!m_RequireHover || m_Hovered) && (IsKeyPressed(KEY_O) || IsKeyPressedRepeat(KEY_O)))
	{
		if (IsKeyDown(KEY_LEFT_SHIFT))
			if (IsKeyDown(KEY_LEFT_CONTROL))
				setValue(m_Value - 100);
			else
				setValue(m_Value - 10);
		else
			if (IsKeyDown(KEY_LEFT_CONTROL))
				setValue(m_Value - 5);
			else
				setValue(m_Value - 1);
	}
}


void BoardGame::gui::ValueInput::draw()
{
	DrawRectangle(m_X, m_Y, m_Width, m_Height, WHITE);
	DrawTextEx(BoardGame::constants::font, m_ValueString.c_str(), Vector2(m_X + m_PaddingX, m_Y + m_PaddingY), m_FontSize, 2, BLACK);
	//DrawText(m_ValueString.c_str(), m_X + m_PaddingX, m_Y + m_PaddingY, m_FontSize, BLACK);
}


int BoardGame::gui::ValueInput::getValue() { return m_Value; }

void BoardGame::gui::ValueInput::updateSize()
{
	m_Width = MeasureTextEx(BoardGame::constants::font, m_ValueString.c_str(), m_FontSize, 2).x + m_PaddingX * 2;
}

void BoardGame::gui::ValueInput::setValue(int value) 
{
	m_Value = value;
	m_ValueString = std::to_string(m_Value);
	updateSize();
}	