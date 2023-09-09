
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
};

Logic::Logic():
    positionSelection{ true, WHITEROUND, NULL, NULL, false, false},
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
    switch ( positionSelection.currentRound )
    {
    case WHITEROUND:
        if ( positionSelection.selectTarget == true ) {
            positionSelection.coordTargetX = positionSelection.cusorX;
            positionSelection.coordTargetY = positionSelection.cusorY;
            positionSelection.lockSelection = true;
        } else {

            if ((positionSelection.coordTargetX == positionSelection.cusorX && positionSelection.coordTargetY == positionSelection.cusorY) 
            || (positionSelection.coordTargetX == NULL && positionSelection.coordTargetY == NULL)) {
                positionSelection.lockSelection = false;
                return;
            }

            size_t x = positionSelection.cusorX;
            size_t y = positionSelection.cusorY;

            auto tmp = board[x][y];
            board[x][y] = board[positionSelection.coordTargetX][positionSelection.coordTargetY];
            board[positionSelection.coordTargetX][positionSelection.coordTargetY] = tmp;
        }

        break;

    case BLACKROUND:
        if ( positionSelection.selectTarget == true ) {
            positionSelection.coordTargetX = positionSelection.cusorX;
            positionSelection.coordTargetY = positionSelection.cusorY;
            positionSelection.lockSelection = true;
        }

        break;
    
    default:
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

    switch (row){
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
    memset(positionSelection.currentPosibleMoves, false, 64);

    switch ( board[positionSelection.coordTargetX][positionSelection.coordTargetY].typeName )
    {
        case TOWER:
            for ( size_t i=0; i < H; ++i) {
                for ( size_t j=0; j < W; ++j) {
                    if ( positionSelection.coordTargetX == i ) {
                        positionSelection.currentPosibleMoves[i][j] = true; 
                      
                    }
                    if (positionSelection.coordTargetY == j ) {
                        positionSelection.currentPosibleMoves[i][j] = true; 
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
            positionSelection.currentPosibleMoves[positionSelection.coordTargetX + 1][positionSelection.coordTargetY] = true; 
            break;              
    default:
        break;
    }
}