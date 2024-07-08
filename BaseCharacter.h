#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos;}
    virtual void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // direction change
    //  1 : facing right, -1 : facing left
    float rightLeft{1.0f};
    // animation variables
    float runningTime{};
    float updateTime{1.f / 20.f};
    int frame{};
    int maxFrames{6};
    float speed{5.f};
    int width{};
    int height{};
    float scale{4.f};
    Vector2 velocity{};
    bool alive{true};
};

#endif