#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
public:
    Character(int winWidth, int windHeight);

    virtual void Tick(float deltaTime) override;
};

#endif