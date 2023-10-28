#pragma once

struct Position {
    bool gameON = false;
    Round currentRound = Round::SELECTPIECE;
    size_t cusorX = 0;
    size_t cusorY = 0;
    bool selectTarget = false;
    bool lockSelection = false;
    size_t coordTargetX = 100;
    size_t coordTargetY = 100;
    size_t moveTargetX = 200;
    size_t moveTargetY = 200;
    bool currentPosibleMoves[H][W];
};