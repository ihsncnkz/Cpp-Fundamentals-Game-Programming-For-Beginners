#include "raylib.h"

int main()
{
    // Window Dimansions
    const int Windowweight = 512;
    const int Windowheight = 380;

    // initialize the window
    InitWindow(Windowweight, Windowheight, "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures\\scarfy.png");
    Rectangle scarfyRac;
    scarfyRac.width = scarfy.width / 6;
    scarfyRac.height = scarfy.height;
    scarfyRac.x = 0;
    scarfyRac.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = Windowweight / 2 - scarfyRac.width / 2;
    scarfyPos.y = Windowheight - scarfyRac.height;

    // is ractangle in air?
    bool isInAir{false};
    // jump velocity (pixels/s)
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta Time (time since last frame)
        const float dt{GetFrameTime()};

        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check
        if (scarfyPos.y >= Windowheight - scarfyRac.height)
        {
            // rectabgle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // Rectangle is in the air
            velocity += gravity * dt;
            isInAir = true;
        }

        // Jump Check
        if (IsKeyPressed(KEY_SPACE) and !isInAir)
        {
            velocity += jumpVel;
        }

        // update position
        scarfyPos.y += velocity * dt;

        // Rectangle Draw
        DrawTextureRec(scarfy, scarfyRac, scarfyPos, WHITE);

        // End Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}