#include "include/raylib.h"
#include <stdlib.h>
#include "keyboard.h"
#include <string.h>

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Camera3D camera = { 0 };
    camera.position = (Vector3) { 0.0f, 7.0f, 10.0f };
    camera.target = (Vector3) { 0.0f, 0.0f , 0.0f };
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.5f, 0.5f, 0.5f };

    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Update
        UpdateCamera(&camera);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

            BeginMode3D(camera);

                DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, BLUE);
                DrawCubeWires(cubePosition, 1.0f, 1.0f, 1.0f, WHITE);

                DrawGrid(100, 1.0f);

            EndMode3D();

            DrawText("3d is this easy", 10, 40, 20, GREEN);

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