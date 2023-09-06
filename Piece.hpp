#pragma once

enum Piece : short { 
    NONE, 
    BLACK, 
    WHITE 
};

const size_t H = 8;
const size_t W = 8;
using Board = Piece[H][W];

struct Position {
    bool gameON;
    size_t x;
    size_t y;
};