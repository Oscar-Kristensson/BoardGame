#include "game.h"
#include <cmath>

Font BoardGame::constants::font;

void BoardGame::constants::loadFont()
{
	std::string stringPath = BoardGame::paths::gameFontOpenSans.string();
	BoardGame::constants::font = LoadFontEx(stringPath.c_str(), 128, nullptr, 0);
}




BoardGame::Game::Game(Vector2 boardSize, Color backgroundColor, 
	std::vector<BoardGame::GameEntityData> entityData, 
	uint8_t playerCount, CommonPlayerInfo commonPlayerInfo, 
	std::vector<PlayerInfo> playersData, std::vector<DiceInfo> dieData, 
	int turnDisplayX, int turnDisplayY, int bankDisplayX, int bankDisplayY,
	std::vector<LabelInfo> labels, bool requireHoverForBanks)
	:m_BoardSize(boardSize), m_BackgroundColor(backgroundColor), m_CommonPlayerInfo(commonPlayerInfo), m_RequireHoverForBanks(requireHoverForBanks)
{
	m_Camera.target = { m_BoardSize.x / 2, m_BoardSize.y / 2 };
	m_Camera.offset = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	m_Camera.rotation = 0.0f;
	m_Camera.zoom = 0.5f;

	m_Entities.reserve(entityData.size());
	for (unsigned int i = 0; i < entityData.size(); i++)
		m_Entities.emplace_back(entityData[i], m_TextureManager);

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


	m_PlayerBankBalance.reserve(dieData.size());
	for (size_t i = 0; i < dieData.size(); i++)
		m_Die.push_back(BoardGame::gui::Dice(dieData[i].x, dieData[i].y, dieData[i].min, dieData[i].max));

	m_Labels.reserve(labels.size());
	for (size_t i = 0; i < labels.size(); i++)
		m_Labels.emplace_back(labels[i]);


	if (m_CommonPlayerInfo.hasAccounts && playerCount > 0)
	{
		m_PlayerBankInput.emplace(BoardGame::gui::ValueInput(bankDisplayX, bankDisplayY, m_RequireHoverForBanks));
		(*m_PlayerBankInput).setValue(m_CommonPlayerInfo.playerStartBalance);
	}

	m_PlayerNumberDisplayUnit = BoardGame::gui::ValueInput(turnDisplayX, turnDisplayY, true);


	m_PlayerNumberDisplayUnit.setValue(1);

}

BoardGame::Game::Game(GameConfigData gameData, uint8_t playerCount)
	: Game(Vector2(gameData.info.width, gameData.info.height),
		gameData.info.backgroundColor, gameData.entities, playerCount,
		gameData.commonPlayerInfo, gameData.players, gameData.die,
		gameData.info.turnDisplayX, gameData.info.turnDisplayY,
		gameData.info.bankDisplayX, gameData.info.bankDisplayY,
		gameData.labels, gameData.info.requireHoverForBanks)
{

}


void BoardGame::Game::handleKeyboardEvents(Vector2 mouseWorldPosition, Vector2 mouseDelta)
{
	// Change the camera offset (so that the camera stays centerd when resizing the window)
	if (IsWindowResized())
	{
		m_Camera.offset = Vector2(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);
	}

	// Change player logic
	if (IsKeyPressed(KEY_Q))
	{
		changePlayer(true);
	}

	if (IsKeyPressed(KEY_W))
	{
		changePlayer(false);
	}

	// Camera control
	if (IsKeyDown(KEY_RIGHT))
	{
		m_Camera.target.x += BoardGame::constants::cameraMovementSpeed / m_Camera.zoom * GetFrameTime();
		m_UseHighFPS = true;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		m_Camera.target.x -= BoardGame::constants::cameraMovementSpeed / m_Camera.zoom * GetFrameTime();
		m_UseHighFPS = true;
	}


	if (IsKeyDown(KEY_DOWN))
	{
		m_Camera.target.y += BoardGame::constants::cameraMovementSpeed / m_Camera.zoom * GetFrameTime();
		m_UseHighFPS = true;
	}
	else if (IsKeyDown(KEY_UP))
	{
		m_Camera.target.y -= BoardGame::constants::cameraMovementSpeed / m_Camera.zoom * GetFrameTime();
		m_UseHighFPS = true;
	}


	m_Camera.zoom = expf(logf(m_Camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));
	if (m_Camera.zoom > 3.0f) m_Camera.zoom = 3.0f;
	else if (m_Camera.zoom < 0.1f) m_Camera.zoom = 0.1f;

	if (IsMouseButtonPressed(1))
		DisableCursor();

	if (IsMouseButtonDown(1))
	{
		m_Camera.target.x += mouseDelta.x / m_Camera.zoom;
		m_Camera.target.y += mouseDelta.y / m_Camera.zoom;
		m_UseHighFPS = true;
	}

	else if (IsMouseButtonDown(0))
		m_UseHighFPS = true;

	if (IsMouseButtonReleased(1))
		EnableCursor();


	if (IsMouseButtonPressed(0)) {
		// Check if a player was clicked and dragged
		if (m_Players.size() > 0 && \
			m_Players[m_CurrentPlayerID].mouseHovers(mouseWorldPosition.x, mouseWorldPosition.y, 1 / m_Camera.zoom / 5))
				m_Players[m_CurrentPlayerID].m_DragController.startDragging();


		// Check if a entity was clicked and dragged
		else if (m_Entities.size() > 0)
		{
			for (size_t i = 0; i < m_Entities.size(); i++)
			{
				if (m_Entities[i].m_DragController.has_value() && m_Entities[i].isMouseHovering(mouseWorldPosition.x, mouseWorldPosition.y))
				{
					(*m_Entities[i].m_DragController).startDragging();
					break;
				}

			}
		}

	}


	if (IsMouseButtonPressed(0) && IsKeyDown(KEY_L))
		for (size_t i = m_Players.size(); i-- > 0; )
		{
			if (m_Players[i].mouseHovers(mouseWorldPosition.x, mouseWorldPosition.y, 1 / m_Camera.zoom / 5))
			{
				m_Players[i].m_DragController.startDragging();
				break;
			}
		}


	// Move the dragged players
	for (size_t i = 0; i < m_Players.size(); i++)
	{
		if (m_Players[i].m_DragController.isDragged())
		{
			m_Players[i].move(mouseDelta.x / m_Camera.zoom, mouseDelta.y / m_Camera.zoom);
		}
	}

	for (size_t i = 0; i < m_Entities.size(); i++)
	{
		if (m_Entities[i].m_DragController.has_value() && m_Entities[i].m_DragController.value().isDragged())
			m_Entities[i].move(mouseDelta.x / m_Camera.zoom, mouseDelta.y / m_Camera.zoom);
	}

	if (IsMouseButtonReleased(0))
	{
		for (size_t i = 0; i < m_Players.size(); i++)
		{
			m_Players[i].m_DragController.stopDragging();
		};

		for (size_t i = 0; i < m_Entities.size(); i++)
			if (m_Entities[i].m_DragController.has_value())
				m_Entities[i].m_DragController.value().stopDragging();
	}

	if (m_PlayerBankInput.has_value() && m_CommonPlayerInfo.hasAccounts)
		(*m_PlayerBankInput).update(GetMouseX(), GetMouseY());


	for (size_t i = 0; i < m_Die.size(); i++)
		m_Die[i].update(GetMouseX(), GetMouseY());






	DEBUG_POST_UPDATE(std::format("Use hFPS: {}", m_UseHighFPS));
	DEBUG_POST_UPDATE(std::format("FPS: {}", GetFPS()));

#if _DEBUG
	if (IsKeyPressed(KEY_F4))
		m_ShowDebugScreen = !m_ShowDebugScreen;
#endif



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
	// Reset the use high FPS counter
	m_UseHighFPS = false;

#if _DEBUG

	DEBUG_NEW_FRAME();

#endif


	Vector2 mouseWorldPosition = GetScreenToWorld2D(GetMousePosition(), m_Camera);
	Vector2 mouseDelta = GetMouseDelta();

	handleKeyboardEvents(mouseWorldPosition, mouseDelta);


#if _DEBUG
	DEBUG_POST_UPDATE(std::format("Player count {}", m_Players.size()));

	std::string temp = "Mouse pos: (" + std::to_string(GetMouseX()) + ", " + std::to_string(GetMouseY()) + ")";
	DEBUG_POST_UPDATE(temp);

	temp = "World pos: (" + std::to_string(mouseWorldPosition.x) + ", " + std::to_string(mouseWorldPosition.y) + ")";
	DEBUG_POST_UPDATE(temp);
#endif




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

	for (size_t i = 0; i < m_Labels.size(); i++)
		m_Labels[i].draw();

	if (m_PlayerBankInput.has_value() && m_CommonPlayerInfo.hasAccounts)
		(*m_PlayerBankInput).draw();

	if (m_Players.size() > 0)
		m_PlayerNumberDisplayUnit.draw();

	for (size_t i = 0; i < m_Die.size(); i++)
		m_Die[i].draw();

#if _DEBUG
	if (m_ShowDebugScreen)
		DEBUG_DRAW();
#endif
}













int BoardGame::convertCPToPixels(float cp)
{
	return GetScreenHeight() * cp / 100;
};

float BoardGame::convertPixelsToCP(int pixels)
{
	return pixels / GetScreenHeight() * 100;
};
