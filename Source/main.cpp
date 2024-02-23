#include "raylib.h"
#include "simManager.h"

int main(void)
{    
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    SimManager simulation;

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        simulation.update();
        simulation.render();
       
        EndDrawing();
    }
    

    CloseWindow();

    return 0;
}