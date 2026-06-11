#include <iostream>
#include "include/raylib.h"
#include <random>
#include <utility>
#include <vector>
#include <string>
#include <map>

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

vector<string> players {"X" , "O"};
vector<vector<string>> board(3 , vector<string>(3 , ""));
int row_size = 3;
int col_size = 3;

Font customFont ;

random_device rd;
mt19937 gen(rd());

uniform_int_distribution<size_t> dist(0 , players.size() - 1);

size_t turn = dist(gen);


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
};




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

                //DrawTextEx(customFont , (players[turn] + " Turn").c_str(), {180, 15}, 40, 2 , WHITE);
            }

            DrawLine(90 , position, board_size, position, WHITE) ;
            DrawLine(position, 90 , position, board_size, WHITE);
        }
    }
}

Positions positions ;

void handleClick(Vector2 &mousePoint){
        if(CheckCollisionPointRec(mousePoint, top_left)){
           if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.TOPLEFT.x;
               int j = positions.TOPLEFT.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
           }
        }
        if(CheckCollisionPointRec(mousePoint, top_middle)){
           if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.TOPMID.x;
               int j = positions.TOPMID.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
           }
        }
        if(CheckCollisionPointRec(mousePoint, top_right)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.TOPRIGHT.x;
               int j = positions.TOPRIGHT.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
            }
        }

        if(CheckCollisionPointRec(mousePoint, middle_left)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.MIDLEFT.x;
               int j = positions.MIDLEFT.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
            }
        }
        if(CheckCollisionPointRec(mousePoint, center)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.CENTER.x;
               int j = positions.CENTER.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
            }
        }
        if(CheckCollisionPointRec(mousePoint, middle_right)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.MIDRIGHT.x;
               int j = positions.MIDRIGHT.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
            }
        }


        if(CheckCollisionPointRec(mousePoint, bottom_left)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.BOTTOMLEFT.x;
               int j = positions.BOTTOMLEFT.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
            }
        }
        if(CheckCollisionPointRec(mousePoint, bottom_mid)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.BOTTOMMID.x;
               int j = positions.BOTTOMMID.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
            }
        }
        if(CheckCollisionPointRec(mousePoint, bottom_right)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
               int i = positions.BOTTOMRIGHT.x;
               int j = positions.BOTTOMRIGHT.y;

               if (board[i][j] != "") return;
               board[i][j] = players[turn];

                if (turn == 1) turn = 0;
                else turn = 1;
            }
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
        DrawTextEx(customFont , (players[turn] + " Turn").c_str(), {180, 15}, 40, 2 , WHITE);

        DrawBoard();

        Vector2 mousePoint = GetMousePosition();
        handleClick(mousePoint);




        EndDrawing();
    }


    UnloadFont(customFont);

    return 0;
}
