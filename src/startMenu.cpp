#include "game.h"
#include "startMenu.h"
#include <iostream>
#include <filesystem>


BoardGame::StartMenu::StartMenu(Color backgroundColor)
    :m_BackgroundColor(backgroundColor), m_GameNames(getGames()), m_SelectedGame(0)
{
    std::cout << "bg:" << backgroundColor.r << "," << backgroundColor.b << "," << backgroundColor.g << std::endl;

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
    std::string path = "assets"; 

    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            std::cout << entry.path() << std::endl;

            std::filesystem::path relativePath = std::filesystem::relative(entry.path(), "assets");
            games.push_back(relativePath.string());
            std::cout << relativePath.string() << std::endl;
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

	ClearBackground(m_BackgroundColor);
	DrawText("Start menu :)", 16, 16, 32, LIGHTGRAY);
}


std::string BoardGame::StartMenu::getGameName()
{
    return m_GameNames[m_SelectedGame];
};