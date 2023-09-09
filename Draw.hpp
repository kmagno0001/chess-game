
class Draw {
public:
    ~Draw();
    Draw( Board& boardref, Position& select );

    inline void DrawingOnScreen();
    inline void clearScreen();
private:
    Board& board;
    char* frame;
    Position& PositionSelection;

    inline void DrawingPiece();
    inline void insertSelectDraw();
};

Draw::~Draw() {
    delete frame;
}

Draw::Draw( Board& boardref, Position& select ):
    board{ boardref },
    frame{ new char[44000] },
    PositionSelection{ select }
{}

inline void Draw::DrawingPiece() {
    size_t counter = 0;
    
    for ( size_t i=0; i < H; ++i ) {
        for ( size_t par=0; par < P; ++par ) {
            for ( size_t j=0; j < W; ++j ) {

                if ( PositionSelection.currentPosibleMoves[i][j] == true ) {
                    strcpy(frame + counter, "\u001b[30m" );
                    counter += 5;
                }

                else if ( PositionSelection.cusorX == i && PositionSelection.cusorY == j && PositionSelection.selectTarget == true ) {
                    strcpy(frame + counter, "\u001b[36m" );
                    counter += 5;
                }
            
                else if ( PositionSelection.cusorX == i && PositionSelection.cusorY  == j ) {
                    strcpy(frame + counter, "\u001b[34m" );
                    counter += 5;
                } 
               
                else if ( board[i][j].pieceName == WHITE ) {
                    strcpy(frame + counter, "\u001b[32m" );
                    counter += 5;
                }
                else if ( board[i][j].pieceName == BLACK ) {
                    strcpy(frame + counter, "\u001b[31m" );
                    counter += 5;
                }

                {
                    switch (board[i][j].typeName) {
                        case TOWER:
                            strcpy(frame + counter, tower[par]);
                            counter += 31; 
                            break;    
                        case KNIGHT:
                            strcpy(frame + counter, knight[par]);
                            counter += 31;   
                            break;
                        case BISHOP:
                            strcpy(frame + counter, bishop[par]);
                            counter += 31;   
                            break;
                        case QUEEN:
                            strcpy(frame + counter, queen[par]);
                            counter += 31;   
                            break;
                        case KING:
                            strcpy(frame + counter, king[par]);
                            counter += 31;   
                            break;
                        case PAWN:
                            strcpy(frame + counter, pawn[par]);
                            counter += 31;   
                            break;                       
                        case ENPTY:
                            strcpy(frame + counter, enpty[par]);
                            counter += 31;            
                            break;   
                        default:
                            break;
                    }
                }

                if (i != 7) {
                    strcpy(frame + counter, "\u001b[0m" );
                    counter += 4;
                } 
            }
            frame[counter] = '\n';
            counter += 1;
        }

        frame[counter] = '\n';
        counter += 1;
    }
}

inline void Draw::DrawingOnScreen() {
    std::thread thread (&Draw::DrawingPiece, this);
    thread.join();
   
    std::cout << frame;
}

inline void Draw::clearScreen() {
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

inline void Draw::insertSelectDraw() {
    
}