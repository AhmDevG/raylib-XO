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


void DrawBoard(vector<vector<string>> &board){
    int row_size = board.size();
    int col_size = board[0].size();
    for (int i = 0 ; i <= row_size ; i++){
        for (int j = 0; j <= col_size; j++) {
            int position = 90 + (BUTTON_SIZE * i);
            int board_size =  90 + (BUTTON_SIZE * 3);

            if (i < row_size && j < col_size && board[i][j] != ""){
                int x_position = 90 + (BUTTON_SIZE * j);
                int y_position = 90 + (BUTTON_SIZE * i);                                                 
                DrawText(board[i][j].c_str(), x_position + 30, y_position + 20, 80 , WHITE);             
            }

            DrawLine(90 , position, board_size, position, WHITE) ;
            DrawLine(position, 90 , position, board_size, WHITE);
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
    //
    // board[1][0] = "X";
    // board[1][1] = "X";
    // board[1][2] = "X";
    //
    //
    // board[2][0] = "O";
    // board[2][1] = "O";
    // board[2][2] = "O";
    
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<size_t> dist(0 , players.size() - 1);

    size_t randomIndex = dist(gen);


    SetTargetFPS(60);


    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText((players[randomIndex] + " Turn").c_str(), 180, 15, 40, WHITE);

        DrawBoard(board) ;
        

        EndDrawing();
    }



    return 0;
}
