#include "game.h"
#include "startMenu.h"
#include <iostream>
#include <filesystem>


BoardGame::StartMenu::StartMenu(Color backgroundColor, Color playerCountSelectBackgroundColor, Color playerCountSelectTextColor)
    :m_BackgroundColor(backgroundColor), m_GameNames(getGames()), m_SelectedGame(0), m_PlayerCount(0), m_PlayerCountSelectBackgroundColor(playerCountSelectBackgroundColor), m_PlayerCountSelectTextColor(playerCountSelectTextColor)
{

}

void BoardGame::StartMenu::drawPlayerCountSelectMenu()
{
    int fontSize = (int)convertCPToPixels(4);

    std::string playerCountString = std::to_string(m_PlayerCount);
    double time = GetTime();

    int playerCountTextLength = MeasureTextEx(BoardGame::constants::font, "Player Count", fontSize, 2).x;
    int plusSignLength = MeasureTextEx(BoardGame::constants::font, "K+", fontSize, 2).x;
    int minusSignLength = MeasureTextEx(BoardGame::constants::font, "L-", fontSize, 2).x;
    int playerNumberCountTextLength = MeasureTextEx(BoardGame::constants::font, playerCountString.c_str(), fontSize, 2).x;
    int marginUnit = plusSignLength / 2;

    int totalWidth = marginUnit + playerCountTextLength + marginUnit \
        + marginUnit + plusSignLength + marginUnit + \
        marginUnit + playerNumberCountTextLength + marginUnit + \
        marginUnit + minusSignLength + marginUnit;

    int top = GetScreenHeight() - fontSize;
    int left = GetScreenWidth() - totalWidth;

    Rectangle rect = { (float)left, (float)top, (float)totalWidth, (float)fontSize };
    DrawRectangleRounded(rect, 1, 10, m_PlayerCountSelectBackgroundColor);

    // Player Count
    //DrawRectangle(left, top, playerCountTextLength + marginUnit * 2, fontSize, m_PlayerCountSelectBackgroundColor);
    DrawTextEx(BoardGame::constants::font, "Player Count", Vector2(left + marginUnit, top), fontSize, 2, m_PlayerCountSelectTextColor);
    
    // Plus
    //DrawRectangle(left + playerCountTextLength + marginUnit * 2, top, plusSignLength + marginUnit * 2, fontSize, m_PlayerCountSelectBackgroundColor);
    DrawTextEx(BoardGame::constants::font, "K+", Vector2(left + playerCountTextLength + marginUnit * 3, top), fontSize, 2, m_PlayerCountSelectTextColor);
    
    // Amount
    //DrawRectangle(left + playerCountTextLength + marginUnit * 6, top, marginUnit * 2 + playerNumberCountTextLength, top, m_PlayerCountSelectBackgroundColor);
    DrawTextEx(BoardGame::constants::font, playerCountString.c_str(), Vector2(left + playerCountTextLength + marginUnit * 7, top), fontSize, 2, m_PlayerCountSelectTextColor);

    // Minus
    //DrawRectangle(left + playerCountTextLength + marginUnit * 8 + playerNumberCountTextLength, top, minusSignLength + marginUnit * 2, fontSize, m_PlayerCountSelectBackgroundColor);
    DrawTextEx(BoardGame::constants::font, "L-", Vector2(left + playerCountTextLength + marginUnit * 9 + playerNumberCountTextLength, top), fontSize, 2, m_PlayerCountSelectTextColor);
}

uint8_t BoardGame::StartMenu::getPlayerCount()
{
    return m_PlayerCount;
}

void BoardGame::StartMenu::update()
{
    if (IsKeyPressed(KEY_UP) && m_SelectedGame > 0) 
        m_SelectedGame--;
    
    if (IsKeyPressed(KEY_DOWN) && m_SelectedGame < m_GameNames.size() - 1)
        m_SelectedGame++;

    if (IsKeyPressed(KEY_K) && m_PlayerCount < BoardGame::constants::playerColorsLength)
        m_PlayerCount++;

    if (IsKeyPressed(KEY_L) && m_PlayerCount != 0)
        m_PlayerCount--;

}

std::vector<std::string> BoardGame::StartMenu::getGames()
{
    std::vector<std::string> games;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(BoardGame::paths::gamesDirPath)) {
            std::filesystem::path relativePath = std::filesystem::relative(entry.path(), BoardGame::paths::gamesDirPath);
            games.push_back(relativePath.string());
        }
    }
    catch (std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    };

    return games;
}


void BoardGame::StartMenu::render()
{
    ClearBackground(m_BackgroundColor);

    int fontSize = BoardGame::convertCPToPixels(5.0f);
    size_t i = 0;
    for (;i < m_GameNames.size(); i++)
    {
        std::string gameNameString; 
        Color textColor;

        if (i == m_SelectedGame)
        {
            textColor = YELLOW;
            gameNameString = "> " + m_GameNames[i] + " <";
            fontSize *= 1.1;
        }
        else
        {
            textColor = BLACK;
            gameNameString = m_GameNames[i];

        };
        
        int textWidth = MeasureTextEx(BoardGame::constants::font, gameNameString.c_str(), fontSize, 2).x;

        DrawTextEx(BoardGame::constants::font, gameNameString.c_str(), Vector2(GetScreenWidth()/2 - textWidth / 2, GetScreenHeight() / 2 - ((m_GameNames.size()/2 - i) * BoardGame::convertCPToPixels(10.0f)) - fontSize / 2), fontSize, 2, textColor);
    }



    drawPlayerCountSelectMenu();

}


std::string BoardGame::StartMenu::getGameName()
{
    return m_GameNames[m_SelectedGame];
};