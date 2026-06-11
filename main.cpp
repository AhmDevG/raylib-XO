#include <iostream>
#include "include/raylib.h"
#include <random>
#include <vector>
#include <string>

using namespace std;

// compile commands
// g++ main.cpp -Iinclude -Llib -lraylib -lgdi32 -lwinmm -lopengl32 -o main.exe && main.exe

const int WIDTH = 500;
const int HEIGHT = 500;
const int BUTTON_SIZE = 110;
const int OFFSET = 10 + BUTTON_SIZE;


void DrawBoard(vector<vector<string>> &board){
    int row_size = board.size();
    int col_size = board[0].size();
    for (int i = 0 ; i < row_size ; i++){
        for (int j = 0; j < col_size; j++) {
            int x_position = 95 + (OFFSET * j) ;
            int y_position = 95 + (OFFSET * i) ;

            // DrawRectangle(x_position , y_position , BUTTON_SIZE, BUTTON_SIZE, GRAY);
            // DrawText(board[i][j].c_str() , 28 + x_position , 10 + y_position , 80  , WHITE);
        }
    }
}


int main(){
    InitWindow(WIDTH , HEIGHT, "XO game");

    vector<string> players {"X" , "O"};
    vector<vector<string>> board(3 , vector<string>(3 , ""));

    // for testing
    // board[0][0] = "X";
    // board[0][1] = "X";
    // board[0][2] = "X";
    //
    // board[0][0] = "O";
    // board[1][0] = "O";
    // board[2][0] = "O";

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<size_t> dist(0 , players.size() - 1);

    size_t randomIndex = dist(gen);


    SetTargetFPS(60);


    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText((players[randomIndex] + " Turn").c_str(), 180, 15, 40, WHITE);
        //DrawBoard(board);
        // 95 + (OFFSET * j) ;
        // 95 + (OFFSET * i) ;
        // 90 + 2
        
        // x - AXIS 
        DrawLine(90,  90,  420,  90 ,  WHITE);
        DrawLine(90,  BUTTON_SIZE + 90     ,  420 ,  90 + BUTTON_SIZE ,  WHITE); 
        DrawLine(90,  BUTTON_SIZE * 2 + 90 ,  420 ,  90 + BUTTON_SIZE*2 ,  WHITE);
        DrawLine(90,  BUTTON_SIZE * 3 + 90 ,  420,  90 + BUTTON_SIZE*3 ,  WHITE);

        // Y - AXIS
        DrawLine(90,  90,  90,  90 + BUTTON_SIZE*3 ,  WHITE);
        DrawLine(90 + BUTTON_SIZE,  90,  90 + BUTTON_SIZE,  90 + BUTTON_SIZE*3 ,  WHITE);
        DrawLine(90 + BUTTON_SIZE*2,  90,  90 + BUTTON_SIZE*2,  90 + BUTTON_SIZE*3 ,  WHITE);
        DrawLine(90 + BUTTON_SIZE*3,  90,  90 + BUTTON_SIZE*3 ,  90 + BUTTON_SIZE*3 ,  WHITE);

        EndDrawing();
    }



    return 0;
}
