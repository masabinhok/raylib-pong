#include <iostream>
#include <raylib.h>

using namespace std;

// colors
Color colorOverlay = GRAY;   
Color colorBackground = BLACK; 
Color colorCourt = WHITE; 
Color colorBall =  {243, 213, 91, 255}; 
Color colorPlayerPaddle = {0, 0, 255, 255}; 
Color colorCpuPaddle = {255, 0, 0, 255};   

// screen dimensions
const int screen_width = 1280;
const int screen_height = 800;
int player_score = 0;
int cpu_score = 0;
int FPS = 60;

//sound handle garna
class SoundManager {
public:
    Sound ballHitSound;
    Sound scoreSound;

    SoundManager() {
        InitAudioDevice(); 
        ballHitSound = LoadSound("resources/ballhit.mp3");
        scoreSound = LoadSound("resources/score.mp3");
    }

    ~SoundManager() {
        UnloadSound(ballHitSound);
        UnloadSound(scoreSound);
        CloseAudioDevice(); 
    }

    void playBallHitSound() {
        PlaySound(ballHitSound);
    }

    void playScoreSound() {
        PlaySound(scoreSound);
    }
};

// Ball class
class Ball {
public:
    float x, y;
    int speed_x, speed_y, radius;
    SoundManager* soundManager;

    void Draw() {
        DrawCircle(x, y, radius, colorBall );
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= screen_height || y - radius <= 0) {
            speed_y *= -1;
        }

        if (x + radius >= screen_width) {
            player_score++;
            soundManager->playScoreSound();
            ResetGame();
        }
        if (x - radius <= 0) {
            cpu_score++;
            soundManager->playScoreSound();
            ResetGame();
        }
    }

    void ResetGame() {
        x = screen_width / 2;
        y = screen_height / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

// Paddle class
class Paddle {
protected:
    void limitMovement() {
        if (y <= 0) {
            y = 0;
        }

        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;
    Color color;
    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, color);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }

        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }

        limitMovement();
    }
};

// CpuPaddle class
class CpuPaddle : public Paddle {
public:
    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y -= speed;
        }

        if (y + height / 2 < ball_y) {
            y += speed;
        }

        limitMovement();
    }
};

// Game objects
Ball ball;
Paddle player;
CpuPaddle cpu;
SoundManager soundManager;

int main() {
    cout << "Starting the game" << endl;

    InitWindow(screen_width, screen_height, "Pong Game");
    SetTargetFPS(FPS);

    ball.radius = 20;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.soundManager = &soundManager;

    player.width = 25;
    player.height = 120;
    player.x = 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;
    player.color = colorPlayerPaddle;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = screen_width - cpu.width - 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;
    cpu.color = colorCpuPaddle;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            soundManager.playBallHitSound();
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            soundManager.playBallHitSound();
            ball.speed_x *= -1;
        }

        ClearBackground(colorBackground);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, colorOverlay);
        DrawCircle(screen_width / 2, screen_height / 2, 150, colorCourt);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i", player_score),  screen_width / 4, 10, 80, BLUE);
        DrawText(TextFormat("%i", cpu_score), 3 * screen_width / 4, 10, 80, RED);
        DrawText(TextFormat("%i", FPS), 2 * screen_width / 4 - 40, 20, 40, WHITE);
        


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
