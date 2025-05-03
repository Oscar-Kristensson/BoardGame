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
    BoardGame::parser::readFile(gameDataPath);
    
#if DEBUG
    
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << "Current working directory: " << cwd << std::endl;

#endif

    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;
    const unsigned int targetFPS = 60;
    
    InitWindow(windowWidth, windowHeight, "BoardGame");

    SetTargetFPS(targetFPS);
        
    BoardGame::Game gameApp = BoardGame::Game();


    while (!WindowShouldClose())
    {
        // Update game

        gameApp.update();
        
        // Player movement
        // Camera zoom controls
        // Uses log scaling to provide consistent zoom speed



        // Move camera to player


        // Drawing
        BeginDrawing();
            ClearBackground(WHITE);

            gameApp.render();
        EndDrawing();
    };

    // De-Initialization
    CloseWindow();

    return 0;
};
