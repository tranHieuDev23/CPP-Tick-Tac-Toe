#ifndef CONSOLE_VIEW_H
#define CONSOLE_VIEW_H

#include <iostream>
#include "../models/game.h"

class ConsoleView
{
public:
    void drawView(Game game)
    {
        Board board = game.getBoard();
        for (int x = 0; x < board.getNumRow(); x++)
        {
            for (int y = 0; y < board.getNumCol(); y++)
            {
                const int value = board.getCell(x, y);
                switch (value)
                {
                case 0:
                    std::cout << 'x';
                    break;
                case 1:
                    std::cout << 'o';
                    break;
                default:
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
    }
};

#endif