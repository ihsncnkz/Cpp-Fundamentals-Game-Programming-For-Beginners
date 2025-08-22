#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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
        Vector2{800.f, 300.f},
        LoadTexture("characters\\goblin_idle_spritesheet.png"),
        LoadTexture("characters\\goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters\\slime_idle_spritesheet.png"),
        LoadTexture("characters\\slime_run_spritesheet.png"),
    };

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

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

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
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

        for (auto enemy : enemies)
        {
            enemy->Tick(dt);
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    };
    UnloadTexture(map);
    CloseWindow();
}