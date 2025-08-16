#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // Update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }

    return data;
}

int main()
{
    // Window Dimansions
    int WindowDimensions[2]{512, 380};

    // initialize the window
    InitWindow(WindowDimensions[0], WindowDimensions[1], "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    // Nebula Variables
    Texture2D nebula = LoadTexture("textures\\12_nebula_spritesheet.png");

    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.x = WindowDimensions[0] + (i * 300);
        nebulae[i].pos.y = WindowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0,
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].runningTime = 0.0;
    }

    // Nebula X velocty (pixels/second)
    int nebVel{-200};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures\\scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = WindowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = WindowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // is ractangle in air?
    bool isInAir{false};

    // jump velocity (pixels/s)
    const int jumpVel{-600};

    int velocity{0};

    Texture2D background = LoadTexture("textures\\far-buildings.png");
    float bgX{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta Time (time since last frame)
        const float dt{GetFrameTime()};

        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20 * dt;

        // Draw the backgorund
        Vector2 bgPos{bgX, 0.0};
        DrawTextureEx(background, bgPos, 0.0, 2.0, WHITE);

        // Perform ground check
        if (isOnGround(scarfyData, WindowDimensions[1]))
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

        // Update nebula position of each nebula
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebVel * dt;
        }

        // update scarfy position
        scarfyData.pos.y += velocity * dt;

        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dt, 5);
        }

        // Update nebula running time of each nebula
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dt, 7);
        }

        // Draw Nebula of each nebula
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // Rectangle Draw
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // End Drawing
        EndDrawing();
    }
    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    UnloadTexture(background);
    CloseWindow();
}