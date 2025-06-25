/* Basic model
#include <SFML/Graphics.hpp>
#include <variant>
#include <vector>
#include "Solver.hpp"
#include "UI.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sudoku Solver");

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        return -1; // handle error
    }

    std::vector<std::vector<char>> board(9, std::vector<char>(9, '.'));
    int selectedRow = -1, selectedCol = -1;
    
   // sf::Event event = {};
    while (window.isOpen()) {
        while (auto optEvent = window.pollEvent()) {
            auto& event = *optEvent;
            if (std::holds_alternative<sf::Event::Closed>(event)) {
                window.close();
            }

            handleInput(event, board, selectedRow, selectedCol);  // must match updated event types
        }

        window.clear(sf::Color::White);
        drawGrid(window);
        drawSelectedCell(window, selectedRow, selectedCol);
        drawBoard(window, board, font);
        window.display();
    }

    return 0;
}*/
//  Difficulty level + Red color highlights for beginners
// #include <SFML/Graphics.hpp>
// #include<set>
// #include <vector>
// #include "Solver.hpp"
// #include "UI.hpp"
// #include "common.hpp"
// #include <iostream>
// int main() {
//     sf::RenderWindow window(sf::VideoMode({800, 600}), "Sudoku Solver");
//     // Let’s assume beginner for now; later we can get user input
//     // DifficultyLevel level = DifficultyLevel::Beginner;
//     std::cout << "Select Difficulty Level:\n1. Beginner\n2. Expert\nChoice: ";
//     int choice;
//     std::cin >> choice;
//     DifficultyLevel level = (choice == 2) ? DifficultyLevel::Expert : DifficultyLevel::Beginner;



//     sf::Font font;
//     if (!font.loadFromFile("assets/fonts/arial.ttf")) {
//         return -1; // handle error
//     }

//     std::vector<std::vector<char>> board(9, std::vector<char>(9, '.'));
//     std::set<std::pair<int,int>> invalidCells; 
//     int selectedRow = -1, selectedCol = -1;

//     sf::Event event;
//     while (window.isOpen()) {
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }

//             handleInput(event, board, selectedRow, selectedCol, level, invalidCells);
//         }

//         window.clear(sf::Color::White);
//         drawGrid(window);
//         drawSelectedCell(window, selectedRow, selectedCol);
//         drawBoard(window, board, font, invalidCells);
//         window.display();
//     }

//     return 0;
// }


#include <SFML/Graphics.hpp>
#include<set>
#include <vector>
#include "Solver.hpp"
#include "UI.hpp"
#include "common.hpp"
#include <iostream>
int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Sudoku Solver");
    // Let’s assume beginner for now; later we can get user input
    // DifficultyLevel level = DifficultyLevel::Beginner;
    std::cout << "Select Difficulty Level:\n1. Beginner\n2. Expert\nChoice: ";
    int choice;
    std::cin >> choice;
    DifficultyLevel level = (choice == 2) ? DifficultyLevel::Expert : DifficultyLevel::Beginner;



    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        return -1; // handle error
    }

    std::vector<std::vector<char>> board(9, std::vector<char>(9, '.'));
    std::vector<std::vector<char>> originalBoard = board;
    std::set<std::pair<int,int>> invalidCells; 
    std::set<std::pair<int,int>> hintCells;

    int selectedRow = -1, selectedCol = -1;
    int hintCount = 0;

    sf::Clock clock;
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // // handleInput(event, board, selectedRow, selectedCol, level, invalidCells, hintCells, hintCount);
            // if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::H && hintCount < 2) {
            //     for (int i = 0; i < 9 && hintCount < 2; i++) {
            //         for (int j = 0; j < 9; j++) {
            //             if (board[i][j] == '.') {
            //                 for (char c = '1'; c <= '9'; c++) {
            //                     if (isValidEntry(board, i, j, c)) {
            //                         board[i][j] = c;
            //                         hintCells.insert({i, j});
            //                         hintCount++;
            //                         goto breakAll;
            //                     }
            //                 }
            //             }
            //         }
            //     }
            //     breakAll:;
            // }

            
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x, y = event.mouseButton.y;
                if (isInsideResetButton(x, y)) {
                    board = originalBoard;
                    invalidCells.clear();
                    hintCells.clear();
                    selectedRow = selectedCol = -1;
                    hintCount = 0;
                    clock.restart();
                }
            }

            handleInput(event, board, selectedRow, selectedCol, level, invalidCells, hintCells, hintCount);
        }

        window.clear(sf::Color::White);
        drawGrid(window);
        drawSelectedCell(window, selectedRow, selectedCol);
        drawBoard(window, board, font, invalidCells, hintCells);
        drawUI(window,font, clock);
        // // Draw "Press H for hint" note
        // sf::Text hintText;
        // hintText.setFont(font);
        // hintText.setCharacterSize(20);
        // hintText.setFillColor(sf::Color::Blue);
        // hintText.setString("Press H for hint (Max 2)");
        // hintText.setPosition(30,580);
        // window.draw(hintText);


        window.display();
    }

    return 0;
}

