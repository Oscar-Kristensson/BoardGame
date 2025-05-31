#include "uiElement.h"
#include "utils.h"

BoardGame::gui::Element::Element(float x, float y)
	:m_X(x), m_Y(y)
{

}

void BoardGame::gui::Element::updateElement(int cursorX, int cursorY)
{
	m_Hovered = isHoveringOver(cursorX, cursorY);
}

void BoardGame::gui::Element::draw()
{

}

bool BoardGame::gui::Element::isHoveringOver(int cursorX, int cursorY)
{
	return cursorX >= m_X && cursorX < m_X + m_Width &&
		cursorY >= m_Y && cursorY < m_Y + m_Height;
}