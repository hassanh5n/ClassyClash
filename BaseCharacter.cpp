#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){};

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

// character collision rectangle
Rectangle BaseCharacter:: getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        scale * width,
        scale * height
        };
}

void BaseCharacter ::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.f;
        frame++;
        if (frame > maxFrames)
        {
            frame = 0;
        }
    }

    // move knight (direction magnitude)
    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + scaled normalized direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        // direction check
        velocity.x < 0 ? rightLeft = -1.0 : rightLeft = 1.0;

        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // draw character
    Rectangle source{(frame * width), 0, rightLeft * width, height}; // character on sprite sheet
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};       // character on the screen, we can also scale it
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0, WHITE);
}