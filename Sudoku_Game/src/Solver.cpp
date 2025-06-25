// For : Difficulty level choice + red error highlights

// #include "Solver.hpp"
// using namespace std;

// bool isValid(vector<vector<char>>& board, int row, int col, char c) {
//     for (int i = 0; i < 9; i++) {
//         if (board[i][col] == c || board[row][i] == c)
//             return false;
//         if (board[3*(row/3)+i/3][3*(col/3)+i%3] == c)
//             return false;
//     }
//     return true;
// }

// bool isValidEntry(const std::vector<std::vector<char>>& board, int row, int col, char val) {
//     for (int i = 0; i < 9; i++) {
//         if (board[row][i] == val || board[i][col] == val)
//             return false;
//     }

//     int startRow = row - row % 3;
//     int startCol = col - col % 3;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             if (board[startRow + i][startCol + j] == val)
//                 return false;
//         }
//     }

//     return true;
// }


// bool solveSudoku(vector<vector<char>>& board) {
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             if (board[i][j] == '.') {
//                 for (char c = '1'; c <= '9'; c++) {
//                     if (isValid(board, i, j, c)) {
//                         board[i][j] = c;
//                         if (solveSudoku(board))
//                             return true;
//                         board[i][j] = '.';
//                     }
//                 }
//                 return false;
//             }
//         }
//     }
//     return true;
// }

#include "Solver.hpp"
using namespace std;

bool isValid(vector<vector<char>>& board, int row, int col, char c) {
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == c || board[row][i] == c)
            return false;
        if (board[3*(row/3)+i/3][3*(col/3)+i%3] == c)
            return false;
    }
    return true;
}

bool isValidEntry(const std::vector<std::vector<char>>& board, int row, int col, char val) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == val || board[i][col] == val)
            return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[startRow + i][startCol + j] == val)
                return false;
        }
    }

    return true;
}


bool solveSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;
                        if (solveSudoku(board))
                            return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
    }
    return true;
}
