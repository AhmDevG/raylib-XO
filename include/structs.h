#include "raylib.h"

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

struct Move {
    int i , j;
    int score;
};

struct Cell {
    Rectangle rect;
    int i, j;
};

