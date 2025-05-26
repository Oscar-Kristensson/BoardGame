#include <iostream>
#include "raylib.h"
#include "game.h"
#include "app.h"

#define DEBUG 1


#if DEBUG
#include <filesystem>
#endif








int main()
{
    
#if DEBUG
    
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << "Current working directory: " << cwd << std::endl;

#endif


    enum ApplicationState
    {
        StartMenu = 0,
        Game = 1
    };

    ApplicationState applicationState = StartMenu;

    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;
    const unsigned int targetFPS = 60;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);  
    InitWindow(windowWidth, windowHeight, "BoardGame");

    SetTargetFPS(targetFPS);
        
    BoardGame::Game* gameApp = nullptr;
        
        /*BoardGame::Game(
        Vector2(gameConfigData.info.width, gameConfigData.info.height),
        gameConfigData.info.backgroundColor,
        gameConfigData.entities
    );*/

    BoardGame::StartMenu startMenu = BoardGame::StartMenu({134, 231, 134, 255});


    while (!WindowShouldClose())
    {
        // Update game

        if (IsKeyDown(KEY_Q))
        {
            if (IsKeyDown(KEY_M))
                applicationState = StartMenu;
            else if (IsKeyDown(KEY_G))
                applicationState = Game;
        }


        // Start a game (Note: This code should be moved to a separate function)
        if (IsKeyDown(KEY_ENTER) && applicationState == StartMenu)
        {
            std::string gameName = startMenu.getGameName();

            std::filesystem::path gameDataPath = BoardGame::paths::gamesDirPath 
                / std::filesystem::path(gameName)
                / BoardGame::paths::gameDataTextFilePath;


            if (!std::filesystem::exists(gameDataPath))
            {
                return 0; // This should be improved
            };

            BoardGame::GameConfigData gameConfigData = BoardGame::parser::loadGameData(gameDataPath);
            delete gameApp;
            gameApp = new BoardGame::Game(
                Vector2(gameConfigData.info.width, gameConfigData.info.height),
                gameConfigData.info.backgroundColor,
                gameConfigData.entities
            );

            applicationState = Game;

            std::string windowName = "BoardGame: " + gameName;
            SetWindowTitle(windowName.c_str());
        }


        switch (applicationState)
        {
        case StartMenu:
            startMenu.update();
            break;
        case Game:
            if (gameApp != nullptr)
            gameApp->update();
            break;
        default:
            break;
        }
        

        // Drawing
        BeginDrawing();
            switch (applicationState)
            {
            case StartMenu:
                startMenu.render();
                break;
            case Game:
                gameApp->render();
                break;
            default:
                break;
            }
        EndDrawing();
    };

    // De-Initialization
    CloseWindow();
    delete gameApp;
    return 0;
};
