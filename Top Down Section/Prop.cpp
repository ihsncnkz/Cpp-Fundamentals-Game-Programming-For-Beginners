#include "Prop.h"
#include "raylib.h"
#include "raymath.h"

Prop::Prop(Vector2 vec, Texture2D text) : worldPos(vec), texture(text) {};

void Prop::render(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0.0, scale, WHITE);
}