#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
private:
protected:
    Texture2D texture{LoadTexture("characters\\knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters\\knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters\\knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // Animation variables
    float runningTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};

public:
    BaseCharacter();

    virtual void Tick(float deltaTime);

    Vector2 getWorldPos() { return worldPos; }

    void undoMovement();

    Rectangle getCollisionRec();
};

#endif