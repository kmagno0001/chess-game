#pragma once

enum Round {
    SELECTPIECE,
    MOVEPIECE,
    SWAPKILLPIECE
};

enum Piece { 
    NONE, 
    BLACK, 
    WHITE 
};

enum Type {
    ENPTY,
    TOWER,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    PAWN
};

struct ChessBoard {
    Piece pieceName {NONE};
    Type typeName {ENPTY};
};


const size_t H = 8;
const size_t W = 8;
const size_t P = 15;

using Board = ChessBoard[H][W];
