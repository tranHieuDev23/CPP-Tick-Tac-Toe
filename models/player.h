#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include "board.h"

class Player
{
public:
    virtual std::pair<int, int> move(const Board &board, const int &whichPlayer) = 0;
};

#endif