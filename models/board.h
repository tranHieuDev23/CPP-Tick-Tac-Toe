#ifndef BOARD_H
#define BOARD_H

#include <vector>

#define CELL_INVALID (-2)
#define CELL_EMPTY (-1)
#define NO_WINNER_YET (-1)

class Board
{
private:
    const int numRow;
    const int numCol;
    const int winCondition;
    std::vector<std::vector<int>> status;
    int winnerId;

    const bool isStartOfWinningStreak(const int &x, const int &y) const
    {
        const int value = getCell(x, y);
        bool matchRow = true;
        bool matchCol = true;
        bool matchMainDiag = true;
        bool matchSecondaryDiag = true;
        for (int i = 1; i < winCondition; i++)
        {
            matchRow &= getCell(x, y + i) == value;
            matchCol &= getCell(x + i, y) == value;
            matchMainDiag &= getCell(x + i, y + i) == value;
            matchSecondaryDiag &= getCell(x - i, y + i) == value;
        }
        return matchRow || matchCol || matchMainDiag || matchSecondaryDiag;
    }

public:
    Board(const int &numRow, const int &numCol, const int &winCondition) : numRow(numRow), numCol(numCol), winCondition(winCondition)
    {
        status = std::vector<std::vector<int>>(numRow);
        for (int x = 0; x < numRow; x++)
        {
            status[x] = std::vector<int>(numCol);
            for (int y = 0; y < numCol; y++)
            {
                status[x][y] = CELL_EMPTY;
            }
        }
        winnerId = NO_WINNER_YET;
    }

    const int getNumRow() const { return numRow; }

    const int getNumCol() const { return numCol; }

    const int getCell(const int &x, const int &y) const
    {
        if (x < 0 || y < 0 || x >= numRow || y >= numCol)
        {
            return CELL_INVALID;
        }
        return status[x][y];
    }

    void setCell(const int &x, const int &y, const int &player)
    {
        if (x < 0 || y < 0 || x >= numRow || y >= numCol || player <= CELL_EMPTY)
        {
            return;
        }
        status[x][y] = player;
    }

    const bool isGameOver()
    {
        return getWinnerId() != NO_WINNER_YET;
    }

    const int getWinnerId()
    {
        if (winnerId != NO_WINNER_YET)
        {
            return winnerId;
        }
        for (int x = 0; x < numRow; x++)
        {
            for (int y = 0; y < numCol; y++)
            {
                if (isStartOfWinningStreak(x, y))
                {
                    winnerId = getCell(x, y);
                    return winnerId;
                }
            }
        }
        return NO_WINNER_YET;
    }
};

#endif