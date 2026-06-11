#include <iostream>
#include "include/raylib.h"
#include <random>
#include <vector>
#include <array>
#include <string>

using namespace std;

// compile commands
// g++ main.cpp -Iinclude -Llib -lraylib -lgdi32 -lwinmm -lopengl32 -o main.exe && main.exe

const int WIDTH = 500;
const int HEIGHT = 500;
const int BUTTON_SIZE = 110;
Rectangle top_left     = { 90,  90, 110, 110};
Rectangle top_middle   = {200,  90, 110, 110};
Rectangle top_right    = {310,  90, 110, 110};

Rectangle middle_left  = { 90, 200, 110, 110};
Rectangle center       = {200, 200, 110, 110};
Rectangle middle_right = {310, 200, 110, 110};

Rectangle bottom_left  = { 90, 310, 110, 110};
Rectangle bottom_mid   = {200, 310, 110, 110};
Rectangle bottom_right = {310, 310, 110, 110};

Rectangle restart_button = {175, 55, 157, 25};

vector<string> players {"X" , "O"};
vector<vector<string>> board(3 , vector<string>(3 , ""));
int row_size = 3;
int col_size = 3;

Font customFont ;

random_device rd;
mt19937 gen(rd());

uniform_int_distribution<size_t> dist(0 , players.size() - 1);

size_t turn = dist(gen);
int canClick = 1 ;


struct Positions {
    Vector2 TOPLEFT = {0 , 0};
    Vector2 TOPMID = {0 , 1};
    Vector2 TOPRIGHT = {0 , 2};

    Vector2 MIDLEFT = {1 , 0};
    Vector2 CENTER = {1 , 1};
    Vector2 MIDRIGHT = {1 , 2};


    Vector2 BOTTOMLEFT = {2 , 0};
    Vector2 BOTTOMMID = {2 , 1};
    Vector2 BOTTOMRIGHT = {2 , 2};

    Vector2 RESTART_BUTTON = {175, 55};
};

struct Cell {
    Rectangle rect;
    int i, j;
};

Cell cells[] = {
    {top_left, 0, 0},
    {top_middle, 0, 1},
    {top_right, 0, 2},

    {middle_left, 1, 0},
    {center, 1, 1},
    {middle_right, 1, 2},

    {bottom_left, 2, 0},
    {bottom_mid, 2, 1},
    {bottom_right, 2, 2},
};

string checkWin(){
    vector<array<int,3>> lines = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6}, 
        {1, 4, 7}, 
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}  
    };

    for (int i = 0; i < lines.size(); i++) {
        int a = lines[i][0];
        int b = lines[i][1];
        int c = lines[i][2];

        int ax = a / 3, ay = a % 3;
        int bx = b / 3, by = b % 3;
        int cx = c / 3, cy = c % 3;

        if (board[ax][ay] != "" &&
            board[ax][ay] == board[bx][by] &&
            board[bx][by] == board[cx][cy]) {

            return board[ax][ay] + " Won";
        }
    }

    bool draw = true;


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ""){
               draw = false;
               break;
            }
        }
        if(!draw) break;
    }

    if(draw){
        return "Draw!";
    }


    return "";
}

void DrawBoard(){
    int row_size = board.size();
    int col_size = board[0].size();
    for (int i = 0 ; i <= row_size ; i++){
        for (int j = 0; j <= col_size; j++) {
            int position = 90 + (BUTTON_SIZE * i);
            int board_size =  90 + (BUTTON_SIZE * 3);

            if (i < row_size && j < col_size && board[i][j] != ""){
                float x_position = 90 + (BUTTON_SIZE * j) + 35 ;
                float y_position = 90 + (BUTTON_SIZE * i) + 15;                                                 
                DrawTextEx(customFont , board[i][j].c_str(), {x_position , y_position}  , 80 , 2 ,  WHITE);             
            }

            DrawLine(90 , position, board_size, position, WHITE) ;
            DrawLine(position, 90 , position, board_size, WHITE);
        }
    }
}

Positions positions ;

void handleClick(Vector2 &mousePoint){
    if (canClick) {
        for (auto &cell : cells) {

            if (CheckCollisionPointRec(mousePoint, cell.rect) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                int i = cell.i;
                int j = cell.j;

                if (board[i][j] != "") return;

                board[i][j] = players[turn];
                turn = !turn;

                return;
            }
        }
    }
    if (!canClick &&
        CheckCollisionPointRec(mousePoint, restart_button) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        for (auto &row : board)
            for (auto &cell : row)
                cell = "";

        canClick = 1;
        return;
    }
}


int main(){
    InitWindow(WIDTH , HEIGHT, "XO game");


    // for testing
    // board[0][0] = "X";
    // board[0][1] = "X";
    // board[0][2] = "X";
    //
    //
    // board[1][0] = "X";
    // board[1][1] = "X";
    // board[1][2] = "X";
    //
    //
    // board[2][0] = "O";
    // board[2][1] = "O";
    // board[2][2] = "O";
    


    SetTargetFPS(60);

    customFont = LoadFontEx("fonts/DeterminationMonoWebRegular-Z5oq.ttf", 80, 0  , 0);




    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(customFont , (players[turn] + " Turn").c_str(), {180, 12}, 40, 2 , WHITE);

        DrawBoard();

        Vector2 mousePoint = GetMousePosition();
        handleClick(mousePoint);


        string won_string = checkWin();

        if(won_string != ""){
            canClick = 0;
        }

        if(!canClick){
            DrawTextEx(customFont , won_string.c_str(), {200, HEIGHT-70}, 40, 2 , GREEN);
            DrawRectangleLines(175, 55, 157, 25, WHITE);

            DrawTextEx(customFont, "Restart", {205 , 54} , 25, 2, WHITE);
        }


        EndDrawing();
    }


    UnloadFont(customFont);

    return 0;
}
