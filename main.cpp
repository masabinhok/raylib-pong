#include <iostream>
#include <raylib.h>

using namespace std;

int main () {
    cout<<"Starting the game"<<endl;
    //defining the screen resolution
    const int screen_width = 1280;
    const int screen_height = 800;

    //initializing the game window
    InitWindow(screen_width, screen_height, "Pong Game");

    //setting the fps
    SetTargetFPS(60);

    //Game loop
    while(WindowShouldClose() == false)
    {
        BeginDrawing();   //draw the canvas
            //drawing
            DrawCircle(screen_width/2, screen_height/2 , 20, WHITE);
            DrawRectangle(10, (screen_height/2 - 60), 25, 120, BLUE);
            DrawRectangle((screen_width- 35), (screen_height/2 - 60), 25, 120, RED);
            DrawLine(screen_width/2 , 0 , screen_width/2 , screen_height, WHITE);
        EndDrawing();   //close the canvas
    }

    CloseWindow(); //close the window
    return 0;
}
