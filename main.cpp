#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <iostream>


int main()
{
    int windowWidth{384};
    int windowHeight{384};

    InitWindow(windowWidth, windowHeight, "ClassyClash");
    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.f, 0.f};
    const float mapScale{4.f};

    //knight instance
    Character knight(windowWidth, windowHeight);

    //prop instance
    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/log.png")},

    };

    //enemy instance
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
        };

    //slime enemy
    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
        };


    //enemy pointer array
    Enemy* enemies[] = {&goblin, &slime};

    //targeting for enemies to knight
    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }


    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //move the map in opposite direction when character moves
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f); //multiplying with -1 makes it opposite
        
        // draw the map
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);

        //draw props
        for(auto prop: props){
            prop.Render(knight.getWorldPos());
        }

        if(!knight.getAlive()) // knight is dead
        {
            DrawText("Game Over", 55.f, 45.f, 40.f, RED);
            EndDrawing();
            continue;
        }
        else // knight is alive
        {
            float barWidth = 100;
            float barHeight = 10;
            float healthPercentage = (float)knight.getHealth()/ 100.f;
            float currentBarWidth = barWidth * healthPercentage;
            DrawRectangle(knight.getScreenPos().x, knight.getScreenPos().y - 30, barWidth, barHeight, GRAY);
            DrawRectangle(knight.getScreenPos().x, knight.getScreenPos().y - 30, currentBarWidth, barHeight, GREEN);
            DrawRectangleLines(knight.getScreenPos().x, knight.getScreenPos().y - 30, barWidth, barHeight, BLACK);
        }

        //moves the character
        knight.tick(GetFrameTime());

        //moves the enemy
        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }
        
        //check if character is out of bounds of the map
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight >  map.height * mapScale)
            {
                knight.undoMovement();
            }

        //check if character collides with a prop
        for(auto prop : props){
            if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec())){
                knight.undoMovement();
            }
        }

        //collision check
        if(IsKeyPressed(KEY_SPACE))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
            {
                enemy->setAlive(false);
            }
            }
        }
        EndDrawing();
    }
    CloseWindow();
}