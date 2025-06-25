#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>

bool isValid(std::vector<std::vector<char>>& board, int row, int col, char c);

bool solveSudoku(std::vector<std::vector<char>> & board);

bool isValidEntry(const std::vector<std::vector<char>>& board, int row, int col, char val);


#endif