#include "Game.h"

Game::Game(sf::RenderWindow& menuWindow) : window(menuWindow), score(0), isAlive(true), font("ARIAL.ttf"), scoreText(font) {
    window.setFramerateLimit(60);
    srand(static_cast<unsigned>(time(nullptr)));

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ 10, 10 });
    updateScoreText();

    sf::RectangleShape border(sf::Vector2f(800.f, 10.f));
    border.setFillColor(sf::Color::White);
    for (int i = 0; i < 4; i++) borders.push_back(border);
    borders[0].setPosition({ 0, 0 });
    borders[1].setPosition({ 800, 0 });
    borders[1].rotate(sf::degrees(90));
    borders[2].setPosition({ 0, 590 });
    borders[3].setPosition({ 10, 1 });
    borders[3].rotate(sf::degrees(90));

    point.locate();
}

void Game::updateScoreText() {
    scoreText.setString("Points: " + std::to_string(score));
}

void Game::handleInput() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::W && snake.direction.y == 0) {
                snake.direction = { 0.f, -snake.speed };
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::A && snake.direction.x == 0) {
                snake.direction = { -snake.speed, 0.f };
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::S && snake.direction.y == 0) {
                snake.direction = { 0.f, snake.speed };
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::D && snake.direction.x == 0) {
                snake.direction = { snake.speed, 0.f };
            }
        }
    }
}

void Game::update() {
    if (isAlive && clock.getElapsedTime().asMilliseconds() > 30) {
        clock.restart();
    }
    if(isAlive)
    snake.move();

    for (int i = 9; i < snake.body.size(); i++) {
        if (snake.checkCollRec(snake.body[i])) {
            isAlive = false;          
        }
    }

    for (auto& border : borders) {
        if (snake.checkCollRec(border)) {
            isAlive = false;
        }
    }

    if (snake.checkCollCir(point.pt)) {
        point.locate();
        snake.grow();
        score++;
        updateScoreText();
    }
}

void Game::render() {
    window.clear();
    window.draw(point.pt);
    for (const auto& segment : snake.body) {
        window.draw(segment);
    }
    for (const auto& border : borders) {
        window.draw(border);
    }
    window.draw(scoreText);
    window.display();
}

void Game::run() {
    while (window.isOpen() && isAlive) {
        handleInput();
        update();
        render();
    }
}
