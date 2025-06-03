#include "game.h"
#include <cmath>

Font BoardGame::constants::font;

void BoardGame::constants::loadFont()
{
	std::string stringPath = BoardGame::paths::gameFontOpenSans.string();
	BoardGame::constants::font = LoadFontEx(stringPath.c_str(), 128, nullptr, 0);
}

BoardGame::Game::Game(Vector2 boardSize, Color backgroundColor, std::vector<BoardGame::GameEntityData> entityData, uint8_t playerCount, CommonPlayerInfo commonPlayerInfo, std::vector<PlayerInfo> playersData)
	:m_BoardSize(boardSize), m_BackgroundColor(backgroundColor), m_CommonPlayerInfo(commonPlayerInfo)
{
	m_Camera.target = { m_BoardSize.x / 2, m_BoardSize.y / 2 };
	m_Camera.offset = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	m_Camera.rotation = 0.0f;
	m_Camera.zoom = 0.5f;

	m_Entities.reserve(entityData.size());
	for (unsigned int i = 0; i < entityData.size(); i++)
		m_Entities.emplace_back(entityData[i]);

	if (playerCount > playersData.size())
	{
		playerCount = playersData.size();
		std::cout << "Waring: Trying to create more players that configurated in the game file" << std::endl;
	}
	
	m_Players.reserve(playerCount);
	for (uint8_t i = 0; i < playerCount; i++)
		m_Players.push_back(BoardGame::Player(playersData[i].x, playersData[i].y, playersData[i].color));

	m_PlayerBankBalance.reserve(playerCount);
	for (uint8_t i = 0; i < playerCount; i++)
		m_PlayerBankBalance.push_back(m_CommonPlayerInfo.playerStartBalance);


	if (m_CommonPlayerInfo.hasAccounts && playerCount > 0)
	{
		m_PlayerBankInput.emplace(BoardGame::gui::ValueInput(120, 20));
		(*m_PlayerBankInput).setValue(m_CommonPlayerInfo.playerStartBalance);
	}

	m_PlayerNumberDisplayUnit.setValue(1);

}

BoardGame::Game::Game(GameConfigData gameData, uint8_t playerCount) 
	: Game(Vector2(gameData.info.width, gameData.info.height), 
		gameData.info.backgroundColor, gameData.entities, playerCount,
		gameData.commonPlayerInfo, gameData.players)
{

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
	DEBUG_NEW_FRAME();



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
	Vector2 mouseDelta = GetMouseDelta();

	if (IsMouseButtonPressed(1))
		DisableCursor();

	if (IsMouseButtonDown(1))
	{
		m_Camera.target.x += mouseDelta.x / m_Camera.zoom;
		m_Camera.target.y += mouseDelta.y / m_Camera.zoom;
	}

	if (IsMouseButtonReleased(1))
		EnableCursor();

	// Check if a player was clicked and dragged
	if (m_Players.size() > 0 && IsMouseButtonPressed(0) && \
		m_Players[m_CurrentPlayerID].mouseHovers(mouseWorldPosition.x, mouseWorldPosition.y, 1 / m_Camera.zoom / 5))
	{
		m_Players[m_CurrentPlayerID].startDragging();
	}

#if _DEBUG
	DEBUG_POST_UPDATE(std::format("Player count {}", m_Players.size()));

	std::string temp = "Mouse pos: (" + std::to_string(GetMouseX()) + ", " + std::to_string(GetMouseY()) + ")";
	DEBUG_POST_UPDATE(temp);

	temp = "World pos: (" + std::to_string(mouseWorldPosition.x) + ", " + std::to_string(mouseWorldPosition.y) + ")";
	DEBUG_POST_UPDATE(temp);
#endif

	if (IsMouseButtonPressed(0) && IsKeyDown(KEY_L))
		for (size_t i = m_Players.size(); i-- > 0; )
		{
			if (m_Players[i].mouseHovers(mouseWorldPosition.x, mouseWorldPosition.y, 1 / m_Camera.zoom / 5))
			{
				m_Players[i].startDragging();
				break;
			}
		}


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

	if (m_PlayerBankInput.has_value() && m_CommonPlayerInfo.hasAccounts)
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

	if (m_PlayerBankInput.has_value() && m_CommonPlayerInfo.hasAccounts)
		(*m_PlayerBankInput).draw();

	if (m_Players.size() > 0)
		m_PlayerNumberDisplayUnit.draw();

	DEBUG_DRAW();
}













int BoardGame::convertCPToPixels(float cp)
{
	return GetScreenHeight() * cp / 100;
};

float BoardGame::convertPixelsToCP(int pixels)
{
	return pixels / GetScreenHeight() * 100;
};
