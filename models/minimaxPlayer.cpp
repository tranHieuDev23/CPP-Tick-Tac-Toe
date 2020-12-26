#include "player.h"
#include<bits/stdc++.h> 
using namespace std; 

struct Move 
{ 
    int row, col; 
}; 

class MinimaxPlayer: public Player {
    public: 
        pair<int, int> move(const Board &board, const int &whichPlayer) {
            pair <int, int> cell;
            Move bestMove = findBestMove(board, 1);
            if (bestMove.row == -1) {
                if (isMovesLeft(board)) {
                    for (int i = 0; i < board.getNumRow(); ++i)
                        for (int j = 0; j < board.getNumCol(); ++j)
                            if (board.getCell(i, j) == CELL_EMPTY) {
                                cell.first = i; 
                                cell.second = j;
                                return cell;
                            }
                }

            }
            cell.first = bestMove.row; 
            cell.second = bestMove.col;
            return cell;
        }
    
    private: 
        pair <int, int> getSize(const Board &board) {
            return make_pair(board.getNumRow(), board.getNumCol());
        }

        bool isMovesLeft(const Board &board) 
        { 
            int nRow = board.getNumRow();
            int nCol = board.getNumCol();

            for (int i = 0; i<nRow; i++) 
                for (int j = 0; j<nCol; j++) 
                    if (board.getCell(i, j) == CELL_EMPTY)
                        return true; 
            return false; 
        } 

        int evaluate(const Board &board, const int &whichPlayer) 
        { 
            pair<int, int> size = getSize(board);
            int nRow = size.first;
            int nCol = size.second;

            // Checking for Rows for X or O victory. 
            for (int row = 0; row<nRow; row++) 
            { 
                for (int col = 0; col < nCol-2; col++) {
                    if (board.getCell(row, col) == board.getCell(row, col+1) &&
                        board.getCell(row, col + 1) == board.getCell(row, col + 2))
                    {
                        if (board.getCell(row, col) == 1)
                            return 10 ;
                        else if (board.getCell(row, col) != CELL_EMPTY)
                            return -10 ;
                    }
                }
            } 
        
            // Checking for Columns for X or O victory. 
            for (int col = 0; col < nCol; col++) 
            { 
                for (int row = 0; row < nRow - 2; row++)
                {
                    if (board.getCell(row, col) == board.getCell(row+1, col) &&
                        board.getCell(row, col) == board.getCell(row+2, col))
                    {
                        if (board.getCell(row, col) == 1)
                            return 10 ;
                        else if (board.getCell(row, col) != CELL_EMPTY)
                            return -10 ;
                    }
                }
            } 
        

            for (int row = 0; row<nRow-2; row++) 
            { 
                for (int col = 0; col < nCol-2; col++) {
                    if (board.getCell(row, col) == board.getCell(row + 1, col + 1) &&
                        board.getCell(row, col) == board.getCell(row + 2, col + 2))
                    {
                        if (board.getCell(row, col) == 1)
                            return 10 ;
                        else if (board.getCell(row, col) != CELL_EMPTY)
                            return -10 ;
                    }
                }
            }

            for (int row = 0; row<nRow-2; row++) 
            { 
                for (int col = 0; col < nCol-2; col++) {
                    if (board.getCell(row + 2, col) == board.getCell(row + 1, col + 1) &&
                        board.getCell(row + 2, col) == board.getCell(row, col + 2))
                    {
                        if (board.getCell(row, col) == 1)
                            return 10;
                        else if (board.getCell(row, col) != CELL_EMPTY)
                            return -10;
                    }
                }
            }            
        
            return 0; 
        }

        int minimax(Board board, int depth, const int &whichPlayer) 
        { 
            pair<int, int> size = getSize(board);
            int nRow = size.first;
            int nCol = size.second;
            bool isMax = false;
            if (whichPlayer == 1)
                isMax = true;
            int score = evaluate(board, whichPlayer); 
        
            if (score == 10 || score == -10) 
                return score; 
        
            if (isMovesLeft(board)==false) 
                return 0; 
        
            // If this maximizer's move 
            if (isMax) 
            { 
                int best = -1000; 
        
                // Traverse all cells 
                for (int i = 0; i<nRow; i++) 
                { 
                    for (int j = 0; j<nCol; j++) 
                    { 
                        // Check if cell is empty 
                        if (board.getCell(i, j) == CELL_EMPTY) 
                        { 
                            // Make the move 
                            board.setCell(i, j, whichPlayer);
        
                            // Call minimax recursively and choose 
                            // the maximum value 
                            best = max( best, 
                                minimax(board, depth+1, whichPlayer + 1) ); 
        
                            // Undo the move 
                            board.setCell(i, j, CELL_EMPTY);
                        } 
                    } 
                } 
                return best; 
            } 
        
            // If this minimizer's move 
            else
            { 
                int best = 1000; 
        
                // Traverse all cells 
                for (int i = 0; i < nRow; i++) 
                { 
                    for (int j = 0; j < nCol; j++) 
                    { 
                        // Check if cell is empty 
                        if (board.getCell(i, j) == CELL_EMPTY) 
                        { 
                            // Make the move 
                            board.setCell(i, j, whichPlayer);
        
                            // Call minimax recursively and choose 
                            // the minimum value 
                            best = min(best, 
                                minimax(board, depth+1, whichPlayer - 1)); 
        
                            // Undo the move 
                            board.setCell(i, j, CELL_EMPTY);
                        } 
                    } 
                } 
                return best; 
            } 
        }


        Move findBestMove(Board board, const int &whichPlayer) 
        { 
            pair<int, int> size = getSize(board);
            int nRow = size.first;
            int nCol = size.second;

            int bestVal = -1000; 
            Move bestMove; 
            bestMove.row = -1; 
            bestMove.col = -1; 
         
            for (int i = 0; i < nRow; i++) 
            { 
                for (int j = 0; j < nCol; j++) 
                { 

                    if (board.getCell(i, j) == CELL_EMPTY) 
                    { 

                        board.setCell(i, j, whichPlayer);
         
                        int moveVal = minimax(board, 0, whichPlayer + 1); 
        
                        board.setCell(i, j, CELL_EMPTY);
        
                        if (moveVal > bestVal) 
                        { 
                            bestMove.row = i; 
                            bestMove.col = j; 
                            bestVal = moveVal; 
                        } 
                    } 
                } 
            } 
        
            printf("The value of the best Move is : %d\n\n", 
                    bestVal); 
        
            return bestMove; 
        }
};

// int main() 
// { 
//     int status[3][3] = 
//     { 
//         { -1, 1, 2}, 
//         { -1, 1, 1 }, 
//         { 2, -1, 2 } 
//     }; 
//     Board board(3, 3, 3);
//     for (int i = 0; i < 3; ++i) 
//         for (int j = 0; j < 3; ++j)
//             board.setCell(i, j, status[i][j]);

//     MinimaxPlayer player;
//     pair<int, int> bestMove = player.move(board, 1); 
  
//     printf("The Optimal Move is :\n"); 
//     printf("ROW: %d COL: %d\n\n", bestMove.first, 
//                                   bestMove.second ); 
//     return 0; 
// }