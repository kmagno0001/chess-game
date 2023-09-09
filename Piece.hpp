#pragma once

struct Position {
    bool gameON;
    Round currentRound;
    size_t cusorX;
    size_t cusorY;
    bool selectTarget;
    bool lockSelection;
    size_t coordTargetX;
    size_t coordTargetY;
    bool currentPosibleMoves[H][W];
};