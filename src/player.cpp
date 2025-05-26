#include "player.h"

BoardGame::Player::Player(int x, int y)
	:m_X(x), m_Y(y)
{

}

void BoardGame::Player::draw()
{
	int radius = 100;
	int width = 250;
	int height = 400;

	Vector2 topPoint = { m_X, m_Y - height/2 + radius };
	Vector2 bottomLeft = { m_X - width/2, m_Y + height/2 };
	Vector2 bottomRight = { m_X + width / 2, m_Y + height/2 };

	DrawCircle(m_X, m_Y - height/2 + radius, radius, RED);
	DrawTriangle(topPoint, bottomLeft, bottomRight, RED);

}