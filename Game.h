#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Point.h"

class Game {
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text scoreText;
    std::vector<sf::RectangleShape> borders;
    Snake snake;
    Point point;
    int score;
    sf::Clock clock;
    bool isAlive;

    void updateScoreText();
    void handleInput();
    void update();
    void render();

public:
    Game(sf::RenderWindow& menuWindow);
    void run();
};


