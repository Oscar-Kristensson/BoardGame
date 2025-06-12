#include "player.h"
#include "utils.h"

BoardGame::Player::Player(int x, int y, Color color)
	:m_X(x), m_Y(y), m_Id(0), m_Color(color)
{

}


bool BoardGame::Player::mouseHovers(int cursorX, int cursorY, float scale)
{
	if (BoardGame::utils::abs(m_X - cursorX) < k_Width / 2 * scale  && BoardGame::utils::abs(m_Y - cursorY) < k_Height / 2 * scale)
		return true;
	return false;
}


void BoardGame::Player::move(int x, int y)
{
	m_X += x;
	m_Y += y;
}


void BoardGame::Player::draw(float scale, bool isSelected)
{
	int height = (int)(k_Height * scale);
	int width = (int)(k_Width * scale);
	int radius = (int)(k_Radius * scale);

	Vector2 topPoint = { (float)m_X, (float)(m_Y - height /2 + radius) };
	Vector2 bottomLeft = { (float)(m_X - width /2), (float)(m_Y + height /2) };
	Vector2 bottomRight = { (float)(m_X + width / 2), (float)(m_Y + height /2) };

	Color color = m_Color;

	if (!isSelected)
	{
		color = BoardGame::utils::brighten(m_Color, 0.4);
	}

	DrawCircle(m_X, m_Y - height /2 + radius, radius, color);
	DrawTriangle(topPoint, bottomLeft, bottomRight, color);

}