#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    const int WindowDimensions[2]{384, 384};

    InitWindow(WindowDimensions[0], WindowDimensions[1], "Top Down Section");

    Texture2D map = LoadTexture("nature_tileset\\OpenWorldMap24x24.png");
    Vector2 mPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight(WindowDimensions[0], WindowDimensions[1]);

    Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature_tileset\\Rock.png")};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta Time
        const float dt{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        mPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mPos, 0.0, 4.0, WHITE);

        rock.render(knight.getWorldPos());

        knight.Tick(dt);
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + WindowDimensions[0] > map.width * mapScale ||
            knight.getWorldPos().y + WindowDimensions[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    };
    UnloadTexture(map);
    CloseWindow();
}