#include "models/game.h"
#include "views/console_view.h"

class ConsolePlayer : public Player
{
public:
    std::pair<int, int> move(const Board &board, const int &whichPlayer)
    {
        int x;
        int y;
        while (true)
        {
            std::cout << "Player " << whichPlayer << "'s turn! Please input x y:" << std::endl;
            std::cin >> x >> y;
            if (board.getCell(x, y) != CELL_EMPTY)
            {
                std::cout << "Invalid cell!" << std::endl;
            }
            else
            {
                break;
            }
        }
        return std::make_pair(x, y);
    }
};

int main(int argc, char const *argv[])
{
    Board board(3, 3, 3);
    std::vector<std::shared_ptr<Player>> players{
        std::make_shared<ConsolePlayer>(ConsolePlayer()),
        std::make_shared<ConsolePlayer>(ConsolePlayer())};
    Game game(board, players);
    ConsoleView view;
    view.drawView(game);
    while (!game.isGameOver())
    {
        game.runNextTurn();
        view.drawView(game);
    }
    std::cout << "The winner is " << game.getWinnerId() << std::endl;
    return 0;
}
