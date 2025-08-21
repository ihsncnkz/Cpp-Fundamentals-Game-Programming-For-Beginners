#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    const int WindowDimensions[2]{384, 384};

    InitWindow(WindowDimensions[0], WindowDimensions[1], "Top Down Section");

    Texture2D map = LoadTexture("nature_tileset\\OpenWorldMap24x24.png");
    Vector2 mPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight(WindowDimensions[0], WindowDimensions[1]);

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset\\Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset\\Log.png")}};

    Enemy goblin{
        Vector2{0.f, 0.f},
        LoadTexture("characters\\goblin_idle_spritesheet.png"),
        LoadTexture("characters\\goblin_run_spritesheet.png")};

    goblin.setTarget(&knight);

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

        // Draw the props
        for (auto prop : props)
        {
            prop.render(knight.getWorldPos());
        }

        knight.Tick(dt);
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + WindowDimensions[0] > map.width * mapScale ||
            knight.getWorldPos().y + WindowDimensions[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        goblin.Tick(dt);

        EndDrawing();
    };
    UnloadTexture(map);
    CloseWindow();
}