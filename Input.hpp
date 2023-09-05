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
                if ( !(positionSelection.x < 1)  ) {
                    positionSelection.x -= 1;
                }

                break;
            case 'a':
                if ( !(positionSelection.y < 1) ) {
                    positionSelection.y -= 1;
                }
                break;
            case 'd':
                if ( !(positionSelection.y > 6) ) {
                    positionSelection.y += 1;
                }
                break; 
            case 's':
                if ( !(positionSelection.x > 6) ) {
                    positionSelection.x += 1;
                }
                break; 
            case 'n':
                positionSelection.gameON = false;
                break;          
            default:
                break;
        }
    }
}

inline void Input::swapPosition() {
    auto tmpA = board[0][0];
    auto tmpB = board[4][0];

    board[0][0] = tmpB;
    board[4][0] = tmpA; 
    
}