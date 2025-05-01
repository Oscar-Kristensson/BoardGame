#include <iostream>
#include "raylib.h"
#include "game.h"

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

    const unsigned int windowWidth = 1280;
    const unsigned int windowHeight = 720;
    const unsigned int targetFPS = 60;
    
    InitWindow(windowWidth, windowHeight, "BoardGame");

    SetTargetFPS(targetFPS);
        
    // Testing code
    Rectangle player = {400 ,280, 40, 40};

    Texture2D mapTestImage = LoadTexture("assets/map.png");
    Camera2D testCamera = { 0 };
    testCamera.target = Vector2(2.0f, 2.0f);
    testCamera.offset = Vector2( windowWidth / 2.0f, windowHeight / 2.0f );
    testCamera.rotation = 0.0f;
    testCamera.zoom = 0.5f;


    while (!WindowShouldClose())
    {
        // Update game
        
        // Player movement
        if (IsKeyDown(KEY_RIGHT)) player.x += 2;
        else if (IsKeyDown(KEY_LEFT)) player.x -= 2;


        if (IsKeyDown(KEY_DOWN)) player.y += 2;
        else if (IsKeyDown(KEY_UP)) player.y -= 2;

        // Camera zoom controls
        // Uses log scaling to provide consistent zoom speed
        testCamera.zoom = expf(logf(testCamera.zoom) + ((float)GetMouseWheelMove() * 0.1f));

        if (testCamera.zoom > 3.0f) testCamera.zoom = 3.0f;
        else if (testCamera.zoom < 0.1f) testCamera.zoom = 0.1f;

        // Move camera to player
        testCamera.target = Vector2( player.x + 20, player.y + 20 );


        // Drawing
        BeginDrawing();
        {
            ClearBackground(WHITE);

            BeginMode2D(testCamera);

                DrawTexture(mapTestImage, 0, 0, WHITE);
                DrawRectangleRec(player, RED);


            EndMode2D();


            DrawText("Hello from Raylib", 128, 128, 32, BLACK);

        };
        EndDrawing();
    };

    // De-Initialization
    CloseWindow();

    return 0;
};