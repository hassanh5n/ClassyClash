#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    // spritesheet calcs
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 2.5f;
}

void Enemy::tick(float deltaTime)
{
    /*AI for enemy psudocode
      *********************
      1. get ToTarget
      2. normalize toTarget
      3. Multiply ToTarget by speed
      4. Move enemy (set worldPos)
      */
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius)
    {
        velocity = {};
    }

    if(!getAlive())
    { 
        return;
    }

    BaseCharacter::tick(deltaTime);
    //collision for damage
    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

// setting enemy position on screen
Vector2 Enemy ::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}