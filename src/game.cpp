#include "game.h"



BoardGame::Game::Game(Vector2 boardSize, Color backgroundColor, std::vector<BoardGame::GameEntityData> entityData)
	:m_BoardSize(boardSize), m_BackgroundColor(backgroundColor)
{
	m_MapImage = LoadTexture("assets/WorldGame/map.png");
	m_Camera.target = { m_BoardSize.x / 2, m_BoardSize.y / 2 };
	m_Camera.offset = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	m_Camera.rotation = 0.0f;
	m_Camera.zoom = 0.5f;


	for (unsigned int i = 0; i < entityData.size(); i++)
		m_Entities.push_back(BoardGame::Entity(entityData[0]));
	

};



void BoardGame::Game::update()
{
	// Change the camera offset
	if (IsWindowResized())
	{
		m_Camera.offset = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	}


	if (IsKeyDown(KEY_RIGHT)) m_Camera.target.x += 10;
	else if (IsKeyDown(KEY_LEFT)) m_Camera.target.x -= 10;


	if (IsKeyDown(KEY_DOWN)) m_Camera.target.y += 10;
	else if (IsKeyDown(KEY_UP)) m_Camera.target.y -= 10;



	m_Camera.zoom = expf(logf(m_Camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));
	if (m_Camera.zoom > 3.0f) m_Camera.zoom = 3.0f;
	else if (m_Camera.zoom < 0.1f) m_Camera.zoom = 0.1f;

	// m_Camera.target = Vector2(m_Player.x + 20, m_Player.y + 20);

}

void BoardGame::Game::render()
{
	ClearBackground(m_BackgroundColor);

	BeginMode2D(m_Camera);
		DrawTexture(m_MapImage, 0, 0, WHITE);
		DrawRectangleRec(m_Player, RED);
		for (int i = 0; i < m_Entities.size(); i++)
			m_Entities[i].draw();



	EndMode2D();


	DrawText("Hello from Raylib", 128, 128, 32, BLACK);

}













int BoardGame::convertCPToPixels(float cp)
{
	return GetScreenHeight() * cp / 100;
};

float BoardGame::convertPixelsToCP(int pixels)
{
	return pixels / GetScreenHeight() * 100;
};
