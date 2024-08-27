#include <iostream>
#include <raylib.h>

using namespace std;
Color Green = {38, 185, 154, 255};
Color Dark_Green = {20, 160, 133, 255};
Color Light_Green = {129, 204, 184, 255};
Color Yellow = {243, 213, 91, 255};

const int screen_width = 1280;
const int screen_height = 800;
int player_score = 0;
int cpu_score = 0;

class Ball {
    public :
    float x, y;
    int speed_x, speed_y, radius;

    void Draw () {
        DrawCircle(x, y , radius, Yellow);
    }

    void Update() {
        x += speed_x;
        y += speed_y;
        
        //we could use GetScreenHeight() and GetScreenWidht() methods to obtain the screen height and width
        if(y + radius >= screen_height || y - radius <= 0){
            speed_y *= (-1);
        }

        if(x + radius >= screen_width){
            cpu_score++;

            ResetGame();

        }
        if( x - radius <= 0){
            player_score++;
            ResetGame();
        }
    }
    
    void ResetGame() {
        x = screen_width/2;
        y = screen_height/2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];

    }
};


class Paddle {

    protected: 

    void limitMovement() {
        if(y <= 0){
            y = 0;
        }

        if(y + height >= GetScreenHeight()){
            y = GetScreenHeight() - 120;
        }
    }

    public: 
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Update() {
        if(IsKeyDown(KEY_UP)){
            y = y -speed;
        }

        if(IsKeyDown(KEY_DOWN)){
            y = y + speed;
        }

        limitMovement();
    }
};


class CpuPaddle: public Paddle {
    public: 
    void Update(int ball_y) {
        
        if(y + height/2 > ball_y)
        {
            y = y -speed;
        }

        if(y + height /2 < ball_y){
            y = y + speed;
        }

        limitMovement();
    }
};   




Ball ball;
Paddle player;
CpuPaddle cpu;


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

    cpu.width = 25;
    cpu.height= 120;
    cpu.x = screen_width - cpu.width - 10;
    cpu.y = screen_height/2 - screen_width/2;
    cpu.speed = 6;




    //Game loop
    while(WindowShouldClose() == false)
    {
        BeginDrawing();   //draw the canvas

            //updating 
            ball.Update();
            player.Update();
            cpu.Update(ball.y);

            //check for collision 
            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y},ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
                ball.speed_x *= -1;
            }

            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y},ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
                ball.speed_x *= -1;
            }


            //drawing
            ClearBackground(Dark_Green);
            DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, Green);
            DrawCircle(screen_width/2, screen_height/2, 100, Light_Green);
            DrawLine(screen_width/2 , 0 , screen_width/2 , screen_height, WHITE);
            ball.Draw();
            player.Draw();
            cpu.Draw();
            DrawText(TextFormat("%i", player_score), 3* screen_width/4, 10, 80, WHITE);
            DrawText(TextFormat("%i", cpu_score), screen_width/4, 10, 80, WHITE);
            

        EndDrawing();   //close the canvas
    }

    CloseWindow(); //close the window
    return 0;
}
