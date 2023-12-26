// Source code by Alija Alispahic "Project 1G" , enjoy!

#include <cstring>
#include <string>
#include "raylib.h"
#include "raymath.h"

enum GameState
{
    MainMenu,
    StartGame,
    GameOver
};

void ToggleFullScreenWindow(int WindowWidth, int WindowHeight)
{
    if (!IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
    }
    else
    {
        ToggleFullscreen();
        SetWindowSize(WindowWidth, WindowHeight);
    }
}
int GetDisplayWidth()
{
    if (IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        return GetMonitorWidth(monitor);
    }
    else
    {
        return GetScreenWidth();
    }
}

int GetDisplayHeight()
{
    if (IsWindowFullscreen())
    {
        int monitor = GetCurrentMonitor();
        return GetMonitorHeight(monitor);
    }
    else
    {
        return GetScreenHeight();
    }
}

int main()
{
    int screenWidth = 1920;
    int screenHeight = 1080;
    float speed{4.0};

    Vector2 mapPos{0.0, 0.0};

    // Set Up Window
    InitWindow(screenWidth, screenHeight, "Project1G");
    ToggleFullScreenWindow(1920, 1080);
    InitAudioDevice();

    //GAME INITIALIZATION FEATURES
    Sound fxWav = LoadSound("Assets/1G Music.wav");
    Texture2D map = LoadTexture("Assets/Level0.png");
    Texture2D knight = LoadTexture("Assets/Heroes/Knight/Idle/Idle-Sheet.png");
    Vector2 knightPos = {(float)screenWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 4.0f), (float)screenHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};
    Rectangle source{0.f, 0.f, (float)knight.width / 4.f, (float)knight.height};
    Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.f, 4.0f * (float)knight.height};
    float RightLeft = 1.f;

    // Fps
    SetTargetFPS(60);

    GameState gameState = MainMenu;
    // Game loop
    PlaySound(fxWav);

    while (!WindowShouldClose())
    {
        switch (gameState)
        {
        case MainMenu:
            // Update the main menu state
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                float mouseX = static_cast<float>(GetMouseX());
                float mouseY = static_cast<float>(GetMouseY());

                if (CheckCollisionPointRec({mouseX, mouseY}, {static_cast<float>(screenWidth / 2 - 100), 200, 200, 50}))
                {
                    gameState = StartGame;
                }
            }
            break;

        case StartGame:
            // Game logic goes here
            Vector2 direction{};
            if (IsKeyDown(KEY_A))
                direction.x -= 1.0;
            if (IsKeyDown(KEY_D))
                direction.x += 1.0;
            if (IsKeyDown(KEY_W))
                direction.y -= 1.0;
            if (IsKeyDown(KEY_S))
                direction.y += 1.0;

            if (Vector2Length(direction) != 0.0)
            {
                mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            }

            // Transition to GameOver state
            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = GameOver;
            }
            break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (gameState)
        {
        case MainMenu:
            // Draw the main menu
            DrawText("Project 1G", screenWidth / 2 - MeasureText("Project 1G", 40) / 2, 80, 40, BLACK);
            DrawRectangle(screenWidth / 2 - 100, 200, 200, 50, BLUE);
            DrawText("Start Game", screenWidth / 2 - MeasureText("Start Game", 20) / 2, 210, 20, WHITE);
            break;

        case StartGame:
            // Draw the game

            DrawTextureEx(map, mapPos, 0.0, 8.0, WHITE);

            // Draw character
            DrawTexturePro(knight, source, dest, Vector2{},0.f,WHITE);

                break;
        }

        EndDrawing();
    }

    // De-Initialization
    UnloadSound(fxWav);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
