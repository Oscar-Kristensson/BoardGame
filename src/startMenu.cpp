#include "game.h"
#include "startMenu.h"
#include <iostream>
#include <filesystem>


BoardGame::StartMenu::StartMenu(Color backgroundColor)
    :m_BackgroundColor(backgroundColor), m_GameNames(getGames()), m_SelectedGame(0), m_PlayerCount(0)
{

}

void BoardGame::StartMenu::drawPlayerCountSelectMenu()
{
    int fontSize = convertCPToPixels(4);

    std::string playerCountString = std::to_string(m_PlayerCount);
    double time = GetTime();

    int playerCountTextLength = MeasureText("Player Count", fontSize);
    int plusSignLength = MeasureText("K+", fontSize);
    int minusSignLength = MeasureText("L-", fontSize);
    int playerNumberCountTextLength = MeasureText(playerCountString.c_str(), fontSize);
    int marginUnit = plusSignLength / 2;

    int totalWidth = marginUnit + playerCountTextLength + marginUnit \
        + marginUnit + plusSignLength + marginUnit + \
        marginUnit + playerNumberCountTextLength + marginUnit + \
        marginUnit + minusSignLength + marginUnit;

    int top = GetScreenHeight() - fontSize;
    int left = GetScreenWidth() - totalWidth;


    // Player Count
    DrawRectangle(left, top, playerCountTextLength + marginUnit * 2, fontSize, RED);
    DrawText("Player Count", left + marginUnit, top, fontSize, BLACK);
    
    // Plus
    DrawRectangle(left + playerCountTextLength + marginUnit * 2, top, plusSignLength + marginUnit * 2, fontSize, YELLOW);
    DrawText("K+", left + playerCountTextLength + marginUnit * 3, top, fontSize, GREEN);
    
    // Amount
    DrawRectangle(left + playerCountTextLength + marginUnit * 6, top, marginUnit * 2 + playerNumberCountTextLength, top, BLUE);
    DrawText(playerCountString.c_str(), left + playerCountTextLength + marginUnit * 7, top, fontSize, PINK);

    // Minus
    DrawRectangle(left + playerCountTextLength + marginUnit * 8 + playerNumberCountTextLength, top, minusSignLength + marginUnit * 2, fontSize, MAGENTA);
    DrawText("L-", left + playerCountTextLength + marginUnit * 9 + playerNumberCountTextLength, top, fontSize, GREEN);
}

void BoardGame::StartMenu::update()
{
    if (IsKeyPressed(KEY_UP) && m_SelectedGame > 0) 
        m_SelectedGame--;
    
    if (IsKeyPressed(KEY_DOWN) && m_SelectedGame < m_GameNames.size() - 1)
        m_SelectedGame++;

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

    for (size_t i = 0; i < m_GameNames.size(); i++)
    {
        std::string gameNameString; 
        Color textColor;
        int fontSize = BoardGame::convertCPToPixels(5.0f);

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
        
        int textWidth = MeasureText(gameNameString.c_str(), fontSize);

        DrawText(gameNameString.c_str(), GetScreenWidth()/2 - textWidth / 2, GetScreenHeight() / 2 - ((m_GameNames.size()/2 - i) * BoardGame::convertCPToPixels(10.0f)) - fontSize / 2, fontSize, textColor);
    }

    drawPlayerCountSelectMenu();

}


std::string BoardGame::StartMenu::getGameName()
{
    return m_GameNames[m_SelectedGame];
};