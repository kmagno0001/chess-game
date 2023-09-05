const char* WPiece[8] = 
{"      ###       ",
"    ########     ",
"  ############   ",
" ###### #######  ",
" ####### ######  ",
"  ############   ",
"   #########     ",
"      ###        "};

const char* BPiece[8] = 
{"     @@@        ",
"   @@@@@@@@@    ",
"  @@@@@@@@@@@@  ",
" @@@@@@ @@@@@@@ ",
" @@@@@@ @@@@@@@ ",
"  @@@@@@@@@@@@  ",
"   @@@@@@@@@    ",
"      @@@       "};

const char* NPiece[8] = 
{" ************** ",
" *            * ",
" *            * ",
" *            * ",
" *            * ",
" *            * ",
" *            * ",
" ************** "};

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
    frame{ new char[12444] },
    PositionSelection{ select }
{}

inline void Draw::DrawingPiece() {
    size_t counter = 0;
    
    for ( size_t i=0; i < H; ++i ) {
        for ( size_t par=0; par < H; ++par ) {
            for ( size_t j=0; j < W; ++j ) {

                if ( PositionSelection.x == i && PositionSelection.y == j ) {
                    strcpy(frame + counter, "\u001b[34m " );
                    counter += 6;
                } else {
                    strcpy(frame + counter, "\u001b[0m " );
                    counter += 5;
                }

                {
                    switch (board[i][j]) {
                        case WHITE:
                            strcpy(frame + counter, WPiece[par]);
                            counter += 16; 
                            break;    
                        case BLACK:
                            strcpy(frame + counter, BPiece[par]);
                            counter += 16;   
                            break;   
                        case NONE:
                            strcpy(frame + counter, NPiece[par]);
                            counter += 16;            
                            break;   
                        default:
                            break;
                    }
                }
            }
            frame[counter] = '\n';
            counter += 1;
        }
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