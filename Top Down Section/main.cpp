#include "raylib.h"
#include "raymath.h"

class Character
{
private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / 12.f};

public:
    Vector2 getWorldPos() { return worldPos; }

    void setWorldPos(Vector2 value) { worldPos = value; }
};

int main()
{
    const int WindowDimensions[2]{384, 384};

    InitWindow(WindowDimensions[0], WindowDimensions[1], "Top Down Section");

    Texture2D map = LoadTexture("nature_tileset\\OpenWorldMap24x24.png");
    Vector2 mPos{0.0, 0.0};
    const float speed{4.0};

    // Knight Idle
    Texture2D knight = LoadTexture("characters\\knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)WindowDimensions[0] / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)WindowDimensions[1] / 2.0f - 4.0f * (0.5f * (float)knight.height)};

    // Knight Run
    Texture2D knight_run = LoadTexture("characters\\knight_run_spritesheet.png");
    Texture2D knight_idle = LoadTexture("characters\\knight_idle_spritesheet.png");

    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};

    // Animation variables
    float runningTime{};
    int frame{};
    const int maxFrame{6};
    const float updateTime{1.f / 12.f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta Time
        const float dt{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

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
            // set mapPos = mapPos - direction
            mPos = Vector2Subtract(mPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }

        // Draw the map
        DrawTextureEx(map, mPos, 0.0, 4.0, WHITE);

        // Update Animation frame
        runningTime += dt;
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrame)
                frame = 0;
        }

        // Draw the chracter
        Rectangle source{frame * (float)knight.width / 6.0f, 0.f, rightLeft * (float)knight.width / 6.0f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    };
    UnloadTexture(map);
    CloseWindow();
}