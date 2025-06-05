#include "label.h"



BoardGame::gui::Label::Label(float x, float y, uint8_t fontSize, std::string text, TextAlignment textAlignment)
	: Element(x, y), m_FontSize(fontSize), m_Text(text), m_TextAlignment(textAlignment)
{
	m_Height = m_FontSize;
	m_Width = MeasureTextEx(BoardGame::constants::font, m_Text.c_str(), m_FontSize, 2).x;
}

BoardGame::gui::Label::Label(LabelInfo labelInfo)
	: Label(labelInfo.x, labelInfo.y, labelInfo.fontSize, labelInfo.labelText, labelInfo.textAlignment)
{

}


void BoardGame::gui::Label::draw()
{
	int x;
	switch (m_TextAlignment)
	{
	case Centered:
		x = m_X - m_Width / 2;
		break;
	case Left:
		x = m_X;
		break;
	case Right:
		x = m_X - m_Width;
		break;
	}


	//DrawRectangle(x, m_Y, m_Width + m_PaddingX * 2, m_Height + m_PaddingY * 2, DARKBLUE);
	DrawTextEx(BoardGame::constants::font, m_Text.c_str(), Vector2(x, m_Y), m_FontSize, 2, WHITE);
};