// Difficulty level choices + red error highlight
// #include "UI.hpp"
// #include "Solver.hpp"
// #include "common.hpp"
// #include <iostream>
// #include <set>
// using namespace std;

// void drawGrid(sf::RenderWindow &window)
// {
//     for (int i = 0; i <= 9; i++)
//     {
//         sf::RectangleShape lineH(sf::Vector2f(540.f, (i % 3 == 0) ? 3.f : 1.f));
//         lineH.setPosition(30, 30 + i * 60);
//         lineH.setFillColor(sf::Color::Black);
//         window.draw(lineH);

//         sf::RectangleShape lineV(sf::Vector2f((i % 3 == 0) ? 3 : 1, 540));
//         lineV.setPosition(30 + i * 60, 30);
//         lineV.setFillColor(sf::Color::Black);
//         window.draw(lineV);
//     }
// }

// void drawBoard(sf::RenderWindow &window, const vector<vector<char>> &board, sf::Font &font, const set<pair<int, int>> &invalidCells)
// {
//     sf::Text text;
//     text.setFont(font);
//     text.setCharacterSize(24);
//     // text.setFillColor(sf::Color::Black);

//     for (int i = 0; i < 9; i++)
//     {
//         for (int j = 0; j < 9; j++)
//         {
//             if (board[i][j] != '.')
//             {
//                 if (invalidCells.count({i, j}))
//                 {
//                     text.setFillColor(sf::Color::Red);
//                 }
//                 else
//                 {
//                     text.setFillColor(sf::Color::Black);
//                 }

//                 text.setString(board[i][j]);
//                 text.setPosition(30 + j * 60 + 20, 30 + i * 60 + 10);
//                 window.draw(text);
//             }
//         }
//     }
// }

// void drawSelectedCell(sf::RenderWindow &window, int row, int col)
// {
//     if (row == -1 || col == -1)
//         return;
//     sf::RectangleShape highlight(sf::Vector2f(60.f, 60.f));
//     highlight.setPosition(30 + col * 60, 30 + row * 60);
//     highlight.setFillColor(sf::Color(200, 200, 255, 100));
//     window.draw(highlight);
// }

// void handleInput(sf::Event event, vector<vector<char>> &board, int &selectedRow, int &selectedCol, DifficultyLevel level, set<pair<int, int>>& invalidCells)
// {
//     if (event.type == sf::Event::MouseButtonPressed)
//     {
//         int x = event.mouseButton.x;
//         int y = event.mouseButton.y;
//         if (x >= 30 && x < 570 && y >= 30 && y < 570)
//         {
//             selectedCol = (x - 30) / 60;
//             selectedRow = (y - 30) / 60;
//         }
//     }

//     if (event.type == sf::Event::TextEntered && selectedRow != -1 && selectedCol != -1)
//     {
//         char entered = static_cast<char>(event.text.unicode);

//         if (entered >= '1' && entered <= '9')
//         {
//             if (level == DifficultyLevel::Beginner /*|| isValidEntry(board, selectedRow, selectedCol, entered)*/)
//             {
//                 if (isValidEntry(board, selectedRow, selectedCol, entered))
//                 {
//                     board[selectedRow][selectedCol] = entered;
//                     invalidCells.erase({selectedRow, selectedCol});
//                 }
//                 else
//                 {
//                     board[selectedRow][selectedCol] = entered;
//                     invalidCells.insert({selectedRow, selectedCol});
//                 }
//             }
//             else if (level == DifficultyLevel::Expert)
//             {
//                 if (isValidEntry(board, selectedRow, selectedCol, entered))
//                 {
//                     board[selectedRow][selectedCol] = entered;
//                 }
//             }
//             // else: block invalid input silently for Expert
//         }
//         else if (entered == '\b')
//         {
//             // Allow deletion only for Beginner
//             if (level == DifficultyLevel::Beginner)
//                 board[selectedRow][selectedCol] = '.';
//             invalidCells.erase({selectedRow, selectedCol});
//         }
//     }
// }

#include "UI.hpp"
#include "Solver.hpp"
#include "common.hpp"
#include <iostream>
#include <set>
using namespace std;

void drawGrid(sf::RenderWindow &window)
{
    for (int i = 0; i <= 9; i++)
    {
        sf::RectangleShape lineH(sf::Vector2f(540.f, (i % 3 == 0) ? 3.f : 1.f));
        lineH.setPosition(30, 30 + i * 60);
        lineH.setFillColor(sf::Color::Black);
        window.draw(lineH);

        sf::RectangleShape lineV(sf::Vector2f((i % 3 == 0) ? 3 : 1, 540));
        lineV.setPosition(30 + i * 60, 30);
        lineV.setFillColor(sf::Color::Black);
        window.draw(lineV);
    }
}

void drawBoard(sf::RenderWindow &window, const vector<vector<char>> &board, sf::Font &font, const set<pair<int, int>> &invalidCells, const set<pair<int, int>> &hintCells)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    // text.setFillColor(sf::Color::Black);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                if (invalidCells.count({i, j}))
                {
                    text.setFillColor(sf::Color::Red);
                }
                else if (hintCells.count({i, j}))
                {
                    text.setFillColor(sf::Color(0, 128, 0));
                }
                else
                {
                    text.setFillColor(sf::Color::Black);
                }

                text.setString(board[i][j]);
                text.setPosition(30 + j * 60 + 20, 30 + i * 60 + 10);
                window.draw(text);
            }
        }
    }
}

void drawSelectedCell(sf::RenderWindow &window, int row, int col)
{
    if (row == -1 || col == -1)
        return;
    sf::RectangleShape highlight(sf::Vector2f(60.f, 60.f));
    highlight.setPosition(30 + col * 60, 30 + row * 60);
    highlight.setFillColor(sf::Color(200, 200, 255, 100));
    window.draw(highlight);
}

bool isInsideResetButton(int x, int y)
{
    return (x >= 600 && x <= 750 && y >= 100 && y <= 140);
}

void drawUI(sf::RenderWindow &window, sf::Font &font, sf::Clock &clock)
{
    // Hint label
    sf::Text hintLabel("Press H for hint (max 2)", font, 18);
    hintLabel.setFillColor(sf::Color::Blue);
    hintLabel.setPosition(600, 50);
    window.draw(hintLabel);

    // Timer
    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(18);
    timerText.setFillColor(sf::Color::Black);

    int seconds = static_cast<int>(clock.getElapsedTime().asSeconds());
    int minutes = seconds / 60;
    seconds %= 60;
    timerText.setString("Time: " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s");
    timerText.setPosition(600, 20);
    window.draw(timerText);

    // Reset button
    sf::RectangleShape resetButton(sf::Vector2f(150.f, 40.f));
    resetButton.setPosition(600, 100);
    resetButton.setFillColor(sf::Color(180, 180, 180));
    window.draw(resetButton);

    sf::Text resetLabel("Reset", font, 20);
    resetLabel.setFillColor(sf::Color::Black);
    resetLabel.setPosition(640, 105);
    window.draw(resetLabel);
}

void handleInput(sf::Event event, vector<vector<char>> &board, int &selectedRow, int &selectedCol, DifficultyLevel level, set<pair<int, int>> &invalidCells, set<pair<int, int>> &hintCells, int &hintCount)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        int row = (y - 30) / 60;
        int col = (x - 30) / 60;
        if (!hintCells.count({row, col}))
        {
            selectedRow = row;
            selectedCol = col;
        }
    }

    if (event.type == sf::Event::TextEntered && selectedRow != -1 && selectedCol != -1)
    {
        char entered = static_cast<char>(event.text.unicode);

        if (entered >= '1' && entered <= '9')
        {
            if (hintCells.count({selectedRow, selectedCol}))
                return;

            if (level == DifficultyLevel::Beginner /*|| isValidEntry(board, selectedRow, selectedCol, entered)*/)
            {
                if (isValidEntry(board, selectedRow, selectedCol, entered))
                {
                    board[selectedRow][selectedCol] = entered;
                    invalidCells.erase({selectedRow, selectedCol});
                }
                else
                {
                    board[selectedRow][selectedCol] = entered;
                    invalidCells.insert({selectedRow, selectedCol});
                }
            }
            else if (level == DifficultyLevel::Expert)
            {
                if (isValidEntry(board, selectedRow, selectedCol, entered))
                {
                    board[selectedRow][selectedCol] = entered;
                }
            }
            // else: block invalid input silently for Expert
        }
        else if (entered == '\b')
        {
            // Allow deletion only for Beginner
            if (level == DifficultyLevel::Beginner && !hintCells.count({selectedRow, selectedCol}))
            {
                board[selectedRow][selectedCol] = '.';
                invalidCells.erase({selectedRow, selectedCol});
            }
        }
        else if (entered == 'H' || entered == 'h')
        {
            if (hintCount >= 2)
                return;

            std::vector<std::vector<char>> copy = board;
            if (solveSudoku(copy))
            {
                for (int i = 0; i < 9 && hintCount < 2; i++)
                {
                    for (int j = 0; j < 9 && hintCount < 2; j++)
                    {
                        if (board[i][j] == '.')
                        {
                            board[i][j] = copy[i][j];
                            hintCells.insert({i, j});
                            hintCount++;
                        }
                    }
                }
            }
        }
    }
}
