#pragma once
#include "Piece.hpp"
#include "Draw.hpp"
#include "Input.hpp"

class Logic {
public:
    Logic();
    inline void GameOn();
    inline void gameRound();

private:
    Position positionSelection;
    Board board;
    Draw draw;
    Input input;
    
};

Logic::Logic():
    positionSelection{ true, 0, 0 },
    draw{ board, positionSelection },
    input{ board, positionSelection }
{
    for ( size_t i=0; i < H; ++i ) {
        for ( size_t j=0; j < W; ++j ) {
            if ( (i == 0 || i == 1) ) {
                board[i][j] = Piece::WHITE;
            }
            else if ( (i == 6 || i == 7) ) {
                board[i][j] = Piece::BLACK;
            }
            else {
                board[i][j] = Piece::NONE;
            }
        }
    }
}

inline void Logic::GameOn() {
    while( positionSelection.gameON ) {
        draw.clearScreen();
        draw.DrawingOnScreen();
        gameRound();
        input.eventLoop();
    }
}

inline void Logic::gameRound() {

}