class Input {
public:
    Input( Board& boardref, Position& select );

    inline void eventLoop();
    inline void swapPosition();
private:
    Board& board;
    Position& positionSelection;
};

Input::Input(  Board& boardref, Position& select ):
    board{ boardref },
    positionSelection{ select }
{}

inline void Input::eventLoop() {
    while( kbhit() ) {
        switch ( getch() ) {
            case 'w':
                if ( !(positionSelection.cusorX < 1) && positionSelection.lockSelection == false ) {
                    positionSelection.cusorX -= 1;
                } else if (positionSelection.currentPosibleMoves[(!(positionSelection.cusorX < 1) ? positionSelection.cusorX : positionSelection.cusorX - 1 )][positionSelection.cusorY] == true) {
                    positionSelection.cusorX -= 1;
                }

                break;

            case 'a':
                if ( !(positionSelection.cusorY < 1) && positionSelection.lockSelection == false ) {
                    positionSelection.cusorY -= 1;
                } else if (positionSelection.currentPosibleMoves[positionSelection.cusorX][(!(positionSelection.cusorY < 1) ? positionSelection.cusorY : positionSelection.cusorY + 1 )] == true) {
                    positionSelection.cusorY -= 1;
                }
                break;

            case 'd':
                if ( !(positionSelection.cusorY > 6) && positionSelection.lockSelection == false ) {
                    positionSelection.cusorY += 1;
                } else if (positionSelection.currentPosibleMoves[positionSelection.cusorX][(!(positionSelection.cusorY < 1) ? positionSelection.cusorY : positionSelection.cusorY - 1 )] == true) {
                    positionSelection.cusorY += 1;
                }
                break;

            case 's':
                if ( !(positionSelection.cusorX > 6) && positionSelection.lockSelection == false ) {
                    positionSelection.cusorX += 1;
                } else if (positionSelection.currentPosibleMoves[(!(positionSelection.cusorX < 1) ? positionSelection.cusorX : positionSelection.cusorX + 1 )][positionSelection.cusorY] == true) {
                    positionSelection.cusorX += 1;
                }
                break;

            case 'n':
                positionSelection.gameON = false;
                break;

            case 13:
                if ( positionSelection.selectTarget == false) positionSelection.selectTarget = true;
                else positionSelection.selectTarget = false;
                break;

            default:
                break;
        }
    }
}

inline void Input::swapPosition() {
    
}