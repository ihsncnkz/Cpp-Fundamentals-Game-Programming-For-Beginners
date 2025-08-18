#include "raylib.h"

int main()
{
    const int WindowDimensions[2]{384, 384};

    InitWindow(WindowDimensions[0], WindowDimensions[1], "Top Down Section");

    Texture2D map = LoadTexture("nature_tileset\\OpenWorldMap24x24.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta Time
        const float dt{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mPos{0.0, 0.0};
        DrawTextureEx(map, mPos, 0.0, 4.0, WHITE);

        EndDrawing();
    };
    UnloadTexture(map);
    CloseWindow();
}