#include "../include/raylib.h"
#include <vector>
#include <array>
#include <string>
#include "../include/structs.h"
#include "../include/consts.h"
#include "../include/rectangles.h"
#include "../include/enums.h"

using namespace std;

vector<vector<string>> board(3 , vector<string>(3 , ""));

Font customFont ;
size_t turn = 0;
int canClick = 1 ;


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



GameState checkState(){
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

        string a_result = board[ax][ay];
        string b_result = board[bx][by];
        string c_result = board[cx][cy];

        if (a_result != "" &&
            a_result == b_result &&
            b_result == c_result) {

            if(board[ax][ay] == "X"){
                return GameState::WIN;
            }
            else{
                return GameState::LOSE;
            }
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
        return GameState::TIE;
    }
    else{
        return GameState::NOTENDED;
    }
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

Move miniMax(int depth , bool isMaximizing){
    GameState result = checkState();
    if(depth == 0 || result != GameState::NOTENDED){
        int score;
        
        if (result == GameState::WIN) score = -10;
        else if (result == GameState::LOSE) score = 10; 
        else score = 0;

        return {-1 ,-1 , score};
    };

    Move bestMove;

    if (isMaximizing){
        bestMove.score = -1000;

        for (int i = 0 ; i < row_size ; i++){
            for (int j = 0; j < col_size; j++) {

                if (board[i][j] == ""){

                    board[i][j] = "O";

                    Move move = miniMax(depth-1, !isMaximizing);

                    board[i][j] = "";

                    if (move.score > bestMove.score){
                        bestMove = {i , j , move.score };
                    }
                }
            }
        }
    }
    else{
        bestMove.score = 1000;

        for (int i = 0 ; i < row_size ; i++){
            for (int j = 0; j < col_size; j++) {

                if (board[i][j] == ""){

                    board[i][j] = "X";

                    Move move = miniMax(depth-1, !isMaximizing);

                    board[i][j] = "";

                    if (move.score < bestMove.score){
                        bestMove = {i , j , move.score };
                    }

                }
            }
        }
    }
    return bestMove;
}


int main(){
    InitWindow(WIDTH , HEIGHT, "XO game");
    InitAudioDevice();

    SetTargetFPS(60);

    Music bgMusic = LoadMusicStream("../audios/toby fox - UNDERTALE Soundtrack - 04 Fallen Down.ogg");
    customFont = LoadFontEx("../fonts/DeterminationMonoWebRegular-Z5oq.ttf", 80, 0  , 0);

    PlayMusicStream(bgMusic);



    while(!WindowShouldClose()) {
        UpdateMusicStream(bgMusic);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(customFont , (players[turn] + " Turn").c_str(), {180, 12}, 40, 2 , WHITE);

        DrawBoard();

        if (turn == 1 && canClick) {
            Move aiMove = miniMax(9 , true);
            board[aiMove.i][aiMove.j] = "O";
            turn = 0;
        }

        Vector2 mousePoint = GetMousePosition();


        handleClick(mousePoint);



        GameState state = checkState();
        string stateString{};

        if(state != GameState::NOTENDED){
            canClick = 0;
        }

        if (state == GameState::WIN){
            stateString = "X Won";
            turn = 0;
        }
        else if (state == GameState::LOSE){
            stateString = "O Won";
            turn = 0;
        }
        else if (state == GameState::TIE){
            stateString = "Draw";
            turn = 0;
        }
        

        if(!canClick){
            DrawTextEx(customFont , stateString.c_str(), {200, HEIGHT-70}, 40, 2 , GREEN);
            DrawRectangleLines(175, 55, 157, 25, WHITE);
            DrawTextEx(customFont, "Restart", {205 , 54} , 25, 2, WHITE);
        }


        EndDrawing();
    }


    UnloadFont(customFont);
    UnloadMusicStream(bgMusic);
    CloseAudioDevice();

    return 0;
}
