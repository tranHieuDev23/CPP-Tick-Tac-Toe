#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "board.h"
#include "player.h"

#define NOT_STARTED_YET (-1);

class Game
{
private:
    Board board;
    std::vector<std::shared_ptr<Player>> players;
    int currentTurn;
    int winnerId;

public:
    Game(const Board &board, const std::vector<std::shared_ptr<Player>> &players) : board(board), players(players)
    {
        currentTurn = NOT_STARTED_YET;
    }

    Board getBoard()
    {
        return board;
    }

    void runNextTurn()
    {
        if (currentTurn + 1 == players.size())
        {
            currentTurn = 0;
        }
        else
        {
            currentTurn++;
        }
        auto moveCoordinate = players[currentTurn]->move(board, currentTurn);
        board.setCell(moveCoordinate.first, moveCoordinate.second, currentTurn);
    }

    const bool isGameOver()
    {
        return board.isGameOver();
    }

    const int getWinnerId()
    {
        return board.getWinnerId();
    }

    const int getPlayerCount() const
    {
        return players.size();
    }

    const int getCurrentPlayerId() const
    {
        return currentTurn;
    }
};

#endif