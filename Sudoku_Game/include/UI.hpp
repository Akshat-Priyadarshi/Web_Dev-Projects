#ifndef UI_HPP
#define UI_HPP

#include <SFML/Graphics.hpp>
#include "common.hpp"
#include <vector>
#include <set>
#include <utility>

void drawGrid(sf::RenderWindow &window);
void drawBoard(sf::RenderWindow &window, const std::vector<std::vector<char>> &board, sf::Font &font, const std::set<std::pair<int, int>> &invalidCells, const std::set<std::pair<int, int>> &hintCells);
void drawSelectedCell(sf::RenderWindow &window, int row, int col);
void handleInput(sf::Event event, std::vector<std::vector<char>> &board, int &selectedRow, int &selectedCol, DifficultyLevel level, std::set<std::pair<int, int>> &invalidCells, std::set<std::pair<int, int>> &hintCells, int& hintCount);
bool isSolveButtonClicked(); // keep this if you plan to use buttons
bool isInsideResetButton(int x,int y);
void drawUI(sf::RenderWindow& window, sf::Font& font, sf::Clock& clock);

#endif
