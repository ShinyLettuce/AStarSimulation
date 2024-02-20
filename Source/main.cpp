#include "raylib.h"
#include "level.h"

int main(void)
{    
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    Level level;

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        level.update();
        level.render();

        EndDrawing();
    }
    

    CloseWindow();

    return 0;
}