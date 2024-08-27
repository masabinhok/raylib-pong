#include <iostream>
#include <raylib.h>

using namespace std;
const int screen_width = 1280;
const int screen_height = 800;

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
        
        //we could use GetScreenHeight() and GetScreenWidht() methods to obtain the screen height and width
        if(y + radius >= screen_height || y - radius <= 0){
            speed_y *= (-1);
        }

        if(x + radius >= screen_width || x - radius <= 0){
            speed_x *= (-1);
        }
    }
};


class Paddle {
    public: 
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangle(x, y, width, height, BLUE);
    }

    void Update() {
        if(IsKeyDown(KEY_UP)){
            y = y -speed;
        }

        if(IsKeyDown(KEY_DOWN)){
            y = y + speed;
        }

        if(y <= 0){
            y =0;
        }

        if(y + height >= GetScreenHeight()){
            y = GetScreenHeight() - 120;
        }
    }

};

Ball ball;
Paddle player;


int main () {
    cout<<"Starting the game"<<endl;
    //defining the screen resolution

    //initializing the game window
    InitWindow(screen_width, screen_height, "Pong Game");

    //setting the fps
    SetTargetFPS(60);

    ball.radius = 20;
    ball.speed_x=7;
    ball.speed_y=7;
    ball.x = screen_width/2;
    ball.y = screen_height/2;

    player.width = 25;
    player.height = 120;
    player.x = 10;
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;


    //Game loop
    while(WindowShouldClose() == false)
    {
        BeginDrawing();   //draw the canvas

            //updating 
            ball.Update();
            player.Update();

            //drawing
            ClearBackground(BLACK);
            DrawLine(screen_width/2 , 0 , screen_width/2 , screen_height, WHITE);
            ball.Draw();
            player.Draw();
            DrawRectangle((screen_width- 35), (screen_height/2 - 60), 25, 120, RED);

        EndDrawing();   //close the canvas
    }

    CloseWindow(); //close the window
    return 0;
}
