/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PLAYER_SPEED 10.0f
#define HITBOX 50


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
typedef struct{
    Vector2 position;

    Vector2 direction;
    Vector2 velocity;

    float speed;
    float acceleration;
    float friction;
    float rotation;
} Player;

Player player = {0};
//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
void PlayerMovement(Player * player, float delta);
void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, float delta, int width, int height);
void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, float delta, int width, int height);
//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1067;                           // Get specified monitor width (current video mode used by monitor)
    const int screenHeight =600;

    //define player stat
    player.position = (Vector2){300,300};
    player.speed = 600;
    player.acceleration = 300;
    player.friction = 1.01;
    player.rotation = 0;

    //define camera
    Camera2D camera = {0};
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //define wall
    Rectangle wall[] = {
        {100,100,1000,100},
        {100,400,1300,100},
        {100,200,100,200},
        {1300,-900,100,1300},
        {1000,-600,100,600},
        {100,-900,100,1000},
        {200,-900,1100,100},
        {550,-200,100,100},
        {550,-600,100,100},
        {350,-400,100,100},
        {750,-400,100,100}
    };
    int sizeWall = sizeof(wall)/sizeof(wall[0]);

    InitWindow(screenWidth, screenHeight, "physics_game");

    //Texture2D playerSprite = LoadTexture("sprite/player.png");

    bool collision = false;
    Rectangle boxCollision = {0};
    Rectangle playerHitbox = {0};
    char *collisionText = malloc(256);
    strcpy(collisionText,"collision");
    
    //--------------------------------------------------------------------------------------
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();

        PlayerMovement(&player,deltaTime);
        UpdateCameraPlayerBoundsPush(&camera,&player,deltaTime,screenWidth,screenHeight);

        //Toggle fullscreen
        //----------------------------------------------------------------------------------
        if(IsKeyPressed(KEY_F)){
            if(IsWindowFullscreen()){
                SetWindowSize(screenWidth,screenHeight);
            }
            else if(!IsWindowFullscreen()){
                 SetWindowSize(GetMonitorWidth(GetCurrentMonitor()),GetMonitorHeight(GetCurrentMonitor()));
            }
            ToggleFullscreen();
        }

        //Check collision
        int hitboxOffset = HITBOX/2;
        Vector2 normal = {0};
        
        for(int i = 0 ; i<sizeWall;i++){
            playerHitbox = (Rectangle){player.position.x-hitboxOffset,player.position.y-hitboxOffset,HITBOX,HITBOX};
            collision = CheckCollisionRecs(wall[i],playerHitbox);
            if(collision){
                boxCollision = GetCollisionRec(wall[i],playerHitbox);
                //find collision side
                Vector2 hitCenter = {boxCollision.x+boxCollision.width/2,boxCollision.y+boxCollision.height/2};
                Vector2 hitOffset = Vector2Subtract(player.position,hitCenter);

                if(abs(hitOffset.x)>abs(hitOffset.y)){
                    //Collision left ou right
                    if(hitCenter.x<player.position.x){
                        //Collision left
                        strcpy(collisionText,"left");
                        normal = (Vector2){-1,0};
                    }
                    else{
                        //Collision right
                        strcpy(collisionText,"right");
                        normal = (Vector2){1,0};
                    }
                }
                else if(abs(hitOffset.x)<abs(hitOffset.y)){
                    //Collision up ou down
                    if(hitCenter.y<player.position.y){
                        //Collision up
                        strcpy(collisionText,"up");
                        normal = (Vector2){0,1};
                    }
                    else{
                        //Collision down
                        strcpy(collisionText,"down");
                        normal = (Vector2){0,-1};
                    }
                }
                

                //find angle of incidence

                //change velocity according to angle of reflection
                player.velocity =Vector2Add(Vector2Scale(normal,-2*Vector2DotProduct(normal,player.velocity)),player.velocity);
            }
        }

            

        // String
        //----------------------------------------------------------------------------------
        char buffer[100];
        char buffery[100];
        int playerx = player.position.x;
        int playery = player.position.y;

        snprintf(buffer, 100, "Player: %d", playerx); // puts string into buffer
        snprintf(buffery, 100, ",%d", playery); // puts string into buffer

        strcat(buffer,buffery);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(WHITE);
            BeginMode2D(camera);
                //DrawTextureEx(playerSprite,(Vector2){player.position.x-cos(player.rotation/360)*30,player.position.y+cos(player.rotation/360)*30},player.rotation,1,RED);
                DrawPoly(player.position,4,30,player.rotation+45,RED);
                //DrawRectangle(player.position.x-hitboxOffset,player.position.y-hitboxOffset,HITBOX,HITBOX,ORANGE);
                for(int i = 0; i<sizeWall;i++)DrawRectangleRec(wall[i],GRAY);

                DrawLine(player.position.x, player.position.y, player.velocity.x +player.position.x, player.velocity.y +player.position.y,BLUE);
                DrawLine(player.position.x, player.position.y, (player.direction.x * 50)+player.position.x, (player.direction.y * 50)+player.position.y,GREEN);
                
            EndMode2D();
            DrawText(buffer,10,550,20,DARKGREEN);
            DrawText(collisionText,500,550,20,DARKGREEN);
            DrawFPS(10, 10);
            DrawGrid(1000, 1.0f);
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void UpdateCameraCenterSmoothFollow(Camera2D *camera, Player *player, float delta, int width, int height){
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    Vector2 diff = Vector2Subtract(player->position, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
    }
}

void PlayerMovement(Player * player, float delta){
    player->direction.x=0;
    player->direction.y=0;

    //Horizontal direction
    if(IsKeyDown(KEY_A)){
        player->direction.x =-1;
    } 
    if(IsKeyDown(KEY_D)){
        player->direction.x = 1;
    } 
    //Verical direction
    if(IsKeyDown(KEY_W)){
        player->direction.y = -1;
    } 
    if(IsKeyDown(KEY_S)){
        player->direction.y =1;
    } 

    if(player->direction.x!=0 || player->direction.y!=0){

        player->velocity = Vector2Add(player->velocity,Vector2Scale(player->direction,player->acceleration*delta));
    }
    player->velocity = Vector2Divide(player->velocity,(Vector2){player->friction,player->friction});
    if (Vector2Length(player->velocity)< 1){
        player->velocity.x = 0;
        player->velocity.y = 0;
    }

    player->position = Vector2Add(player->position,Vector2Scale(player->velocity,delta));

    //Player rotation
    if((player->velocity.x + player->velocity.y)> 1){
        player->rotation = player->rotation+ Vector2Length(player->velocity)*delta;
    }
    else if((player->velocity.x + player->velocity.y)< 1){
        player->rotation = player->rotation - Vector2Length(player->velocity)*delta;
    }
}

void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player *player, float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = (Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
    if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
    if (player->position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
    if (player->position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
}

