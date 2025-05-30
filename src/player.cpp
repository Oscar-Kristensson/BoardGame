#include "player.h"
#include "utils.h"

BoardGame::Player::Player(int x, int y)
	:m_X(x), m_Y(y), m_Id(0)
{

}


bool BoardGame::Player::mouseHovers(int cursorX, int cursorY, float scale)
{
	if (BoardGame::utils::abs(m_X - cursorX) < k_Width / 2 * scale  && BoardGame::utils::abs(m_Y - cursorY) < k_Height / 2 * scale)
		return true;
	return false;
}

bool BoardGame::Player::isDragged()
{
	return m_IsDragged;
}

void BoardGame::Player::startDragging()
{
	m_IsDragged = true;
}

void BoardGame::Player::stopDragging()
{
	m_IsDragged = false;
}

void BoardGame::Player::move(int x, int y)
{
	m_X += x;
	m_Y += y;
}


void BoardGame::Player::draw(float scale)
{
	int height = k_Height * scale;
	int width = k_Width * scale;
	int radius = k_Radius * scale;

	Vector2 topPoint = { m_X, (m_Y - height /2 + radius) };
	Vector2 bottomLeft = { (m_X - width /2), (m_Y + height /2) };
	Vector2 bottomRight = { (m_X + width / 2), (m_Y + height /2) };

	DrawCircle(m_X, m_Y - height /2 + radius, radius, RED);
	DrawTriangle(topPoint, bottomLeft, bottomRight, RED);

}