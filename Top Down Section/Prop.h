#include "raylib.h"

class Prop
{
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};

public:
    Prop(Vector2 vec, Texture2D text);
    void render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);
};