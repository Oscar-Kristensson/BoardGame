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

    std::filesystem::path gameDataPath = "assets/testGameData.txt";
    BoardGame::GameConfigData gameConfigData =  BoardGame::parser::readFile(gameDataPath);
    
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
        
    BoardGame::Game gameApp = BoardGame::Game(Vector2(gameConfigData.info.width, gameConfigData.info.height), gameConfigData.info.backgroundColor);
    BoardGame::StartMenu startMenu = BoardGame::StartMenu();


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

        switch (applicationState)
        {
        case StartMenu:
            startMenu.update();
            break;
        case Game:
            gameApp.update();
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
                gameApp.render();
                break;
            default:
                break;
            }
        EndDrawing();
    };

    // De-Initialization
    CloseWindow();

    return 0;
};
