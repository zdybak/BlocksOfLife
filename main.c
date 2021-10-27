//blocks of life, a conway's game of life implementation in C rendered with raylib

#include "include/raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//offset the grid coords from origin
#define XCOORD -10.0f
#define YCOORD -10.0f
#define HALFCUBE 0.5f

//set size of the living matrix
#define LIFESIZE 400
#define LIFEWIDTH 20
#define LIFEHEIGHT 20
#define SPEED 1.0

bool* seedLife()
{
    static bool life[LIFESIZE];
    int i;

    srand( (unsigned)time(NULL) );

    for(i=0; i < LIFESIZE; i++) {
        life[i] = ((rand()%2) == 1);
    }

    return life;
}

bool* copyLife(bool *life)
{
    static bool lifeCopy[LIFESIZE];
    int i;

    for(i=0; i < LIFESIZE; i++) {
        lifeCopy[i] = life[i];
    }

    return lifeCopy;
}

void drawLife(float x, float y, Color col)
{
    Vector3 cubePosition;
    float finalX = x+XCOORD;
    float finalY = y+YCOORD;
    
    if(finalX >= 0 && finalY >= 0){
        cubePosition = (Vector3){ finalX-HALFCUBE, 0.5f, finalY-HALFCUBE };
    } else if (finalX <= 0 && finalY >= 0) {
        cubePosition = (Vector3){ finalX+HALFCUBE, 0.5f, finalY-HALFCUBE };
    } else if (finalX <= 0 && finalY <= 0) {
        cubePosition = (Vector3){ finalX+HALFCUBE, 0.5f, finalY+HALFCUBE };
    } else {
        cubePosition = (Vector3){ finalX-HALFCUBE, 0.5f, finalY+HALFCUBE };
    }
    DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, col);
    DrawCubeWires(cubePosition, 1.0f, 1.0f, 1.0f, WHITE);
}

void drawAllLife(bool *life)
{
    int x;
    int y;

    for(x=0; x <= LIFEWIDTH; x++) {
        for(y=0; y <= LIFEHEIGHT; y++){
            if( life[(x*LIFEWIDTH)+y] ){
                Color col = BLUE;
                if(x==0){
                    col = RED;
                }
                if(y==0){
                    col = ORANGE;
                }
                if(x==LIFEWIDTH){
                    col = PURPLE;
                }
                if(y==LIFEHEIGHT){
                    col = GREEN;
                }
                drawLife((float) x,(float) y, col);
            }
        }
    }
}

bool checkCycle(double *cycleTime)
{
    double lifeTime = GetTime();
    if(lifeTime - *cycleTime > SPEED){
        *cycleTime = lifeTime;
        return true;
    }

    return false;
}

bool* updateLife(bool *life)
{
    int x;
    int y;

    bool* newLife = copyLife(life);

    for(x=0; x <= LIFEWIDTH; x++) {
        for(y=0; y <= LIFEHEIGHT; y++){
            //begin neighbor check
            int neighbors = 0;
            
            if(x > 0) {
                //check north
                if(life[((x-1)*LIFEWIDTH)+y]){
                    neighbors++;
                }
                //check northwest
                if(y > 0) {
                    if(life[((x-1)*LIFEWIDTH)+(y-1)]){
                        neighbors++;
                    }
                }
                //check northeast
                if(y < LIFEHEIGHT) {
                    if(life[((x-1)*LIFEWIDTH)+(y+1)]){
                        neighbors++;
                    }
                }
            }

            if(y > 0){
                //check west
                if(life[(x*LIFEWIDTH)+(y-1)]){
                    neighbors++;
                }
            }

            if(y < LIFEHEIGHT){
                //check east
                if(life[(x*LIFEWIDTH)+(y+1)]){
                    neighbors++;
                }
            }

            if(x < LIFEWIDTH){
                //southwest
                if(y > 0){
                    if(life[((x+1)*LIFEWIDTH)+(y-1)]){
                        neighbors++;
                    }
                }
                //south
                if(life[((x+1)*LIFEWIDTH)+y]){
                    neighbors++;
                }
                //southeast
                if(y < LIFEHEIGHT-1){
                    if(life[((x+1)*LIFEWIDTH)+(y+1)]){
                        neighbors++;
                    }
                }
            }
            //end neighbor checks
            int cind = (x*LIFEWIDTH)+y;
            bool cell = life[cind];

            //any live cell with less than 2 neighbors dies from underpop
            if(cell && neighbors < 2){
                newLife[cind] = false;
            } else if (cell && neighbors > 3) {
                newLife[cind] = false;
            } else if (!cell && neighbors == 3) {
                newLife[cind] = true;
            }
        }
    }
    return newLife;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "Blocks Of Life");

    Camera3D camera = { 0 };
    camera.position = (Vector3) { -6.0f, 20.0f, -22.0f };
    camera.target = (Vector3) { 0.0f, 0.0f , 0.0f };
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    char cameraText[1024];
    char cycleText[1024];

    SetCameraMode(camera, CAMERA_FREE);

    //life array
    bool *life = seedLife();

    //time
    double cycleTime = 0.0;
    double *cycleTimePtr;
    cycleTimePtr = &cycleTime;
  
    //int cycles = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Update
        UpdateCamera(&camera);
        snprintf(cameraText, sizeof(cameraText), "Camera X: %f Y: %f Z: %f", camera.position.x, camera.position.y, camera.position.z);

        if(checkCycle(cycleTimePtr)){
            //spawn new life cycle
            life = updateLife(life);
        }
        snprintf(cycleText, sizeof(cycleText), "Cycle Time: %.0f seconds", cycleTime);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

            BeginMode3D(camera);

                drawAllLife(life);
                               
                DrawGrid(20, 1.0f);

            EndMode3D();

            
            DrawText(cameraText, 10, 40, 20, GREEN);
            DrawText(cycleText, 10, 60, 20, GREEN);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}