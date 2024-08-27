#include <iostream>
#include <raylib.h>

using namespace std;

class Ball {
    public :
    float x, y;
    int speed_x, speed_y, radius;

    void Draw () {
        DrawCircle(x, y , radius, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;
    }
};

Ball ball;


int main () {
    cout<<"Starting the game"<<endl;
    //defining the screen resolution
    const int screen_width = 1280;
    const int screen_height = 800;

    //initializing the game window
    InitWindow(screen_width, screen_height, "Pong Game");

    //setting the fps
    SetTargetFPS(60);

    ball.radius = 20;
    ball.speed_x=7;
    ball.speed_y=7;
    ball.x = screen_width/2;
    ball.y = screen_height/2;

    //Game loop
    while(WindowShouldClose() == false)
    {
        BeginDrawing();   //draw the canvas

            //updating 
            ball.Update();

            //drawing
            ClearBackground(BLACK);
            DrawLine(screen_width/2 , 0 , screen_width/2 , screen_height, WHITE);
            ball.Draw();
            DrawRectangle(10, (screen_height/2 - 60), 25, 120, BLUE);
            DrawRectangle((screen_width- 35), (screen_height/2 - 60), 25, 120, RED);

        EndDrawing();   //close the canvas
    }

    CloseWindow(); //close the window
    return 0;
}
