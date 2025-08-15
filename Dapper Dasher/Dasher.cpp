#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Window Dimansions
    const int Windowweight = 512;
    const int Windowheight = 380;

    // initialize the window
    InitWindow(Windowweight, Windowheight, "Dapper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    // Nebula Variables
    Texture2D nebula = LoadTexture("textures\\12_nebula_spritesheet.png");

    // AnimData for NebDate
    AnimData nebData{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},
        {Windowweight, Windowheight - nebula.height / 8},
        0,
        1.0 / 12.0,
        0.0};

    AnimData neb2Data{
        {0.0, 0.0, nebula.width / 8, nebula.height / 8},
        {Windowweight + 300, Windowheight - nebula.height},
        0,
        1.0 / 16.0,
        0.0};
    Rectangle nebulaRac{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebulaPos{Windowweight, Windowheight - nebulaRac.height};

    Rectangle nebula2Rac{0.0, 0.0, nebula.width / 8, nebula.height / 8};
    Vector2 nebula2Pos{Windowheight + 300, Windowheight - nebulaRac.height};

    // Nebula X velocty (pixels/second)
    int nebVel{-200};

    // Nebula Frame
    int nebFrame{};
    int neb2Frame{};

    // Amount of time before we update the animation frame for nebula
    const float nebUpdateTime(1.0 / 12.0);
    float nebRunningTime{};

    const float neb2UpdateTime(1.0 / 16.0);
    float neb2RunningTime{};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures\\scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = Windowweight / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = Windowheight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    Rectangle scarfyRac;
    scarfyRac.width = scarfy.width / 6;
    scarfyRac.height = scarfy.height;
    scarfyRac.x = 0;
    scarfyRac.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = Windowweight / 2 - scarfyRac.width / 2;
    scarfyPos.y = Windowheight - scarfyRac.height;

    // Animation Frame
    int frame{};

    // Amount of time before we update the animation frame
    const float updateTime{1.0 / 12.0};
    float RunningTime{};

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

        // Update nebula position
        nebulaPos.x += nebVel * dt;

        // Update nebula 2 position
        nebula2Pos.x += nebVel * dt;

        // update scarfy position
        scarfyPos.y += velocity * dt;

        if (!isInAir)
        {
            // Update running time
            RunningTime += dt;
            if (RunningTime >= updateTime)
            {
                RunningTime = 0.0;

                // Update Animation Frame
                scarfyRac.x = frame * scarfyRac.width;
                frame++;
                if (frame >= 5)
                {
                    frame = 0;
                }
            }
        }

        // Update nebula running time
        nebRunningTime += dt;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebulaRac.x = nebFrame * nebulaRac.width;
            nebFrame++;
            if (nebFrame >= 7)
            {
                nebFrame = 0;
            }
        }

        // Update nebula running time
        neb2RunningTime += dt;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            nebula2Rac.x = neb2Frame * nebula2Rac.width;
            neb2Frame++;
            if (neb2Frame >= 7)
            {
                neb2Frame = 0;
            }
        }

        // Draw Nebula
        DrawTextureRec(nebula, nebulaRac, nebulaPos, WHITE);
        // Draw Nebula 2
        DrawTextureRec(nebula, nebula2Rac, nebula2Pos, RED);

        // Rectangle Draw
        DrawTextureRec(scarfy, scarfyRac, scarfyPos, WHITE);

        // End Drawing
        EndDrawing();
    }
    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    CloseWindow();
}