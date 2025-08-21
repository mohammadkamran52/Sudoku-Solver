#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "sudoku_solver.h"

const int CELL_SIZE = 80;
const int GRID_SIZE_PX = CELL_SIZE * GRID_SIZE;
const int WINDOW_WIDTH = GRID_SIZE_PX + 120; 
const int WINDOW_HEIGHT = GRID_SIZE_PX;

int grid[GRID_SIZE][GRID_SIZE] = {0};
int selectedRow = -1, selectedCol = -1;

void drawGrid(sf::RenderWindow& window, sf::Font& font) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
            cell.setPosition(col * CELL_SIZE, row * CELL_SIZE);
            cell.setFillColor((row == selectedRow && col == selectedCol) ? sf::Color(220, 220, 255) : sf::Color::White);
            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(2);
            window.draw(cell);

            if (grid[row][col] != 0) {
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(grid[row][col]));
                text.setCharacterSize(36);
                text.setFillColor(sf::Color::Black);
                text.setPosition(col * CELL_SIZE + 25, row * CELL_SIZE + 15);
                window.draw(text);
            }
        }
    }
}

void drawSolveButton(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape button(sf::Vector2f(100, 40));
    button.setPosition(GRID_SIZE_PX + 10, 20);
    button.setFillColor(sf::Color(200, 255, 200));
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2);
    window.draw(button);

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Solve");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(GRID_SIZE_PX + 25, 25);
    window.draw(buttonText);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "5x5 Sudoku Solver");
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) { 
        std::cerr << "Could not load font. Try using a system font or change path.\n";
        return 1;
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                if (mouseX < GRID_SIZE_PX && mouseY < GRID_SIZE_PX) {
                    selectedCol = mouseX / CELL_SIZE;
                    selectedRow = mouseY / CELL_SIZE;
                }

                if (mouseX >= GRID_SIZE_PX + 10 && mouseX <= GRID_SIZE_PX + 110 &&
                    mouseY >= 20 && mouseY <= 60) {
                    solveSudoku(grid);
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (selectedRow != -1 && selectedCol != -1) {
                    char entered = static_cast<char>(event.text.unicode);
                    if (entered >= '1' && entered <= '5') {
                        grid[selectedRow][selectedCol] = entered - '0';
                    }
                    else if (entered == '0' || entered == '\b') {
                        grid[selectedRow][selectedCol] = 0;
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        drawGrid(window, font);
        drawSolveButton(window, font);
        window.display();
    }

    return 0;
}
