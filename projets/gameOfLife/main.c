/*******************************************************************************************
*
*   raylib [core] example - 2d camera mouse zoom
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2024 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define ROWS 100
#define COLS 100

const int screenWidth = 600;
const int screenHeight = 600;

const int cellWidth =  screenWidth / COLS;
const int cellHeight = screenHeight / ROWS;
int cells[ROWS][COLS];
int cells2[ROWS][COLS];

int gameState = 0;

bool tabSwitch = false;

void calcNextGen(int currentGen[ROWS][COLS],int nextGen[ROWS][COLS]);
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main ()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "game of life");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cells[i][j]=0;
            cells2[i][j]=0;
        } 
    }
    
    SetTargetFPS(10);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){   //Switch between edit and play
            if(gameState==0){
                gameState=1;
            }
            else if(gameState==1){
                gameState=0;
            }
        }
       
        if(gameState==0){       //Edit mode
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                int indiceY = GetMouseX() / cellHeight;
                int indiceX = GetMouseY() / cellWidth;
                if(cells[indiceY][indiceX]==0){
                    cells[indiceY][indiceX]=1;
                }
                else if(cells[indiceY][indiceX]==1){
                    cells[indiceY][indiceX]=0;
                }
            }  
        }

        if(gameState==1){       //Play mode
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLS; j++)
                {
                    cells2[i][j]=cells[i][j];
                }
                
            }
            calcNextGen(cells2,cells);   
        }
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(WHITE);

            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLS; j++)
                {
                    if(cells[i][j]==0){
                        DrawRectangle(i * cellWidth, j * cellHeight,cellWidth,cellHeight,GRAY);
                    }
                    else if(cells[i][j]==1){
                        DrawRectangle(i * cellWidth, j * cellHeight,cellWidth,cellHeight,WHITE);
                    }                  
                }
            }
            if(gameState==0){
                DrawText("EDIT",10,10,20,WHITE);
            }
            else if(gameState==1){
                DrawText("PLAY",10,10,20,WHITE);
            }
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}

void calcNextGen(int currentGen[ROWS][COLS],int nextGen[ROWS][COLS]){    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int livingCells = 0;

            if(i-1>=0 && j-1>=0 && i+1<100 && j+1<100){
                if(currentGen[i-1][j-1]==1){livingCells++;}
                if(currentGen[i][j-1]==1){livingCells++;}
                if(currentGen[i+1][j-1]==1){livingCells++;}
                if(currentGen[i-1][j]==1){livingCells++;}
                if(currentGen[i+1][j]==1){livingCells++;}
                if(currentGen[i-1][j+1]==1){livingCells++;}
                if(currentGen[i][j+1]==1){livingCells++;}
                if(currentGen[i+1][j+1]==1){livingCells++;}

                if(currentGen[i][j]==1){
                    if(livingCells ==0 || livingCells ==1 || livingCells ==4 ||livingCells ==5 ||livingCells ==6 || livingCells ==7 ||livingCells ==8 ){
                        nextGen[i][j]=0;
                    }
                    else if(livingCells == 2 ||livingCells == 3){
                        nextGen[i][j]=1;
                    }
                }
                else if(currentGen[i][j]==0){
                    if(livingCells==3){
                        nextGen[i][j]=1;
                    }
                }
            } 
        }          
    }
}
