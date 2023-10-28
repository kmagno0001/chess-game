
#include "DrawingPieces.hpp"
#include "ChessBoard.hpp"
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

    inline Type fillBoard( size_t row, size_t col );
    inline void movement(); 
    inline void clearMovement();   
};

Logic::Logic():
    positionSelection{ true, SELECTPIECE, 0, 0, false, false, 100, 100, 200, 200,{
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
    } },
    draw{ board, positionSelection },
    input{ board, positionSelection }
{
    for ( size_t i=0; i < H; ++i ) {
        for ( size_t j=0; j < W; ++j ) {
            if ( (i == 0 || i == 1) ) {
                board[i][j].pieceName = Piece::WHITE;
                board[i][j].typeName = fillBoard( i, j);
            }
            else if ( (i == 6 || i == 7) ) {
                board[i][j].pieceName = Piece::BLACK;
                board[i][j].typeName = fillBoard( i, j);
            }
            else {
                board[i][j].pieceName = Piece::NONE;
                board[i][j].typeName = Type::ENPTY;
            }
        }
    }
}

inline void Logic::GameOn() {
    while( positionSelection.gameON ) {
        draw.clearScreen();
        draw.DrawingOnScreen();
        input.eventLoop();
        gameRound();
    }
}

inline void Logic::gameRound() {
    switch ( positionSelection.currentRound ) {
        case Round::SELECTPIECE:
            if (positionSelection.selectTarget == true && board[positionSelection.cusorX][positionSelection.cusorY].pieceName == WHITE) {
                positionSelection.currentRound = Round::MOVEPIECE;
                positionSelection.coordTargetX = positionSelection.cusorX;
                positionSelection.coordTargetY = positionSelection.cusorY;
            }

            break;

        case Round::MOVEPIECE:
            if (positionSelection.selectTarget == false && 
               ( positionSelection.cusorX == positionSelection.coordTargetX && positionSelection.cusorY == positionSelection.coordTargetY )) {
                positionSelection.currentRound = Round::SELECTPIECE;
                positionSelection.lockSelection = false;
                clearMovement();
                break;
            }

            positionSelection.lockSelection = true;
            movement();  

            if (positionSelection.selectTarget == false && positionSelection.lockSelection == true) {
                positionSelection.moveTargetX = positionSelection.cusorX;
                positionSelection.moveTargetY = positionSelection.cusorY;
                positionSelection.currentRound = Round::SWAPKILLPIECE;
                positionSelection.lockSelection = false;
                clearMovement();
            }  

            break;

        case  Round::SWAPKILLPIECE:
            if (board[positionSelection.moveTargetX][positionSelection.moveTargetY].pieceName == NONE) {
                std::swap(board[positionSelection.moveTargetX][positionSelection.moveTargetY], board[positionSelection.coordTargetX][positionSelection.coordTargetY]);
                positionSelection.currentRound = Round::SELECTPIECE;
            }

            break;       
    }
}

inline Type Logic::fillBoard( size_t row, size_t col) {
    Type retTy;
    switch ( col ) {
        case 0:
        case 7:
            retTy = TOWER;
            break;

        case 1:  
        case 6:
            retTy = KNIGHT;
            break;

        case 2: 
        case 5:
            retTy = BISHOP;
            break;

        case 3:
            retTy = QUEEN;
            break;

        case 4:
            retTy = KING;
            break;           
            
        default:
            break;
    }

    switch (row) {
        case 1:
        case 6:
            retTy = PAWN;
            break;
        
        default:
            break;
        }

    return retTy;
}

inline void Logic::movement() {
    switch ( board[positionSelection.coordTargetX][positionSelection.coordTargetY].typeName )
    {
        case TOWER:
            for ( size_t i=0; i < H; ++i) {
                for ( size_t j=0; j < W; ++j) {
                    if ( positionSelection.coordTargetX == i ) {
                        positionSelection.currentPosibleMoves[positionSelection.coordTargetX][j] = true;   
                    }

                    if ( positionSelection.coordTargetY == j ) {
                        positionSelection.currentPosibleMoves[i][positionSelection.coordTargetY] = true; 
                    }
                }
            } 
            break;

        case KNIGHT:
            break;
        case BISHOP:
            break;
        case QUEEN:
            break;
        case KING: 
            break;
        case PAWN:
            positionSelection.currentPosibleMoves[positionSelection.coordTargetX ][positionSelection.coordTargetY] = true; 
            positionSelection.currentPosibleMoves[positionSelection.coordTargetX + 1][positionSelection.coordTargetY] = true; 
            break;              
    default:
        break;
    }
}

inline void Logic::clearMovement() {
    for (size_t i=0; i < H; ++i) {
        for (size_t j=0; j < W; ++j) {
            positionSelection.currentPosibleMoves[i][j] = false;
        }
    }
}