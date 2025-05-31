#include "game.h"



BoardGame::Game::Game(Vector2 boardSize, Color backgroundColor, std::vector<BoardGame::GameEntityData> entityData, uint8_t playerCount, PlayerInfo playerInfo)
	:m_BoardSize(boardSize), m_BackgroundColor(backgroundColor), m_PlayerInfo(playerInfo)
{
	m_Camera.target = { m_BoardSize.x / 2, m_BoardSize.y / 2 };
	m_Camera.offset = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	m_Camera.rotation = 0.0f;
	m_Camera.zoom = 0.5f;


	for (unsigned int i = 0; i < entityData.size(); i++)
		m_Entities.push_back(BoardGame::Entity(entityData[0]));
	
	for (uint8_t i = 0; i < playerCount; i++)
		m_Players.push_back(BoardGame::Player(64, 64, BoardGame::constants::playerColors[i]));

	for (uint8_t i = 0; i < playerCount; i++)
		m_PlayerBankBalance.push_back(m_PlayerInfo.playerStartBalance);

	if (m_PlayerInfo.hasAccounts && playerCount > 0)
	{
		m_PlayerBankInput.emplace(BoardGame::gui::ValueInput(120, 20));
		(*m_PlayerBankInput).setValue(m_PlayerInfo.playerStartBalance);
	}

	m_PlayerNumberDisplayUnit.setValue(1);

}




void BoardGame::Game::changePlayer(bool increase)
{
	if (m_Players.size() == 0)
		return;
	m_PlayerBankBalance[m_CurrentPlayerID] = (*m_PlayerBankInput).getValue();

	if (increase)
	{

		if (m_CurrentPlayerID + 1 == m_Players.size())
		{
			m_CurrentPlayerID = 0;
		}
		else
		{
			m_CurrentPlayerID++;
		}
	}
	else
	{
		if (m_CurrentPlayerID == 0)
		{
			m_CurrentPlayerID = m_Players.size() - 1;
		}
		else
		{
			m_CurrentPlayerID--;
		}
	}

	(*m_PlayerBankInput).setValue(m_PlayerBankBalance[m_CurrentPlayerID]);

	m_PlayerNumberDisplayUnit.setValue(m_CurrentPlayerID + 1);
}


void BoardGame::Game::update()
{
	// Change the camera offset
	if (IsWindowResized())
	{
		m_Camera.offset = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	}

	if (IsKeyPressed(KEY_Q))
	{
		changePlayer(true);
	}
	
	if (IsKeyPressed(KEY_W))
	{
		changePlayer(false);
	}

	if (IsKeyDown(KEY_RIGHT)) m_Camera.target.x += 8 / m_Camera.zoom;
	else if (IsKeyDown(KEY_LEFT)) m_Camera.target.x -= 8 / m_Camera.zoom;


	if (IsKeyDown(KEY_DOWN)) m_Camera.target.y += 8 / m_Camera.zoom;
	else if (IsKeyDown(KEY_UP)) m_Camera.target.y -= 8 / m_Camera.zoom;


	m_Camera.zoom = expf(logf(m_Camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));
	if (m_Camera.zoom > 3.0f) m_Camera.zoom = 3.0f;
	else if (m_Camera.zoom < 0.1f) m_Camera.zoom = 0.1f;


	Vector2 mouseWorldPosition = GetScreenToWorld2D(GetMousePosition(), m_Camera);

	// Check if a player was clicked and dragged
	if (m_Players.size() > 0 && IsMouseButtonPressed(0) && \
		m_Players[m_CurrentPlayerID].mouseHovers(mouseWorldPosition.x, mouseWorldPosition.y, 1 / m_Camera.zoom / 5))
	{
		m_Players[m_CurrentPlayerID].startDragging();
	}


	if (IsMouseButtonPressed(0) && IsKeyDown(KEY_L))
		for (size_t i = m_Players.size(); i-- > 0; )
		{
			if (m_Players[i].mouseHovers(mouseWorldPosition.x, mouseWorldPosition.y, 1 / m_Camera.zoom / 5))
			{
				m_Players[i].startDragging();
				break;
			}
		}

	Vector2 mouseDelta = GetMouseDelta();

	// Move the dragged players
	for (size_t i = 0; i < m_Players.size(); i++)
	{
		if (m_Players[i].isDragged())
		{
			m_Players[i].move(mouseDelta.x / m_Camera.zoom, mouseDelta.y / m_Camera.zoom);
		}
	}

	if (IsMouseButtonReleased(0))
	{
		for (size_t i = 0; i < m_Players.size(); i++)
		{
			m_Players[i].stopDragging();
		};
	}

	if (m_PlayerBankInput.has_value() && m_PlayerInfo.hasAccounts)
		(*m_PlayerBankInput).update(GetMouseX(), GetMouseY());
}

void BoardGame::Game::render()
{
	ClearBackground(m_BackgroundColor);

	BeginMode2D(m_Camera);
		for (int i = 0; i < m_Entities.size(); i++)
			m_Entities[i].draw();

		bool isSelectedPlayer;
		for (uint8_t i = 0; i < m_Players.size(); i++)
		{
			isSelectedPlayer = m_CurrentPlayerID == i;

			m_Players[i].draw(1/m_Camera.zoom/5, isSelectedPlayer);

		}




	EndMode2D();

	if (m_PlayerBankInput.has_value() && m_PlayerInfo.hasAccounts)
		(*m_PlayerBankInput).draw();

	m_PlayerNumberDisplayUnit.draw();
}













int BoardGame::convertCPToPixels(float cp)
{
	return GetScreenHeight() * cp / 100;
};

float BoardGame::convertPixelsToCP(int pixels)
{
	return pixels / GetScreenHeight() * 100;
};
