#include "Game.h"

Game::Game(sf::RenderWindow& menuWindow) : window(menuWindow), score(0), isAlive(true), exit(false), font("ARIAL.ttf"), 
          scoreText(font), infoText(font) {
    window.setFramerateLimit(60);
    srand(static_cast<unsigned>(time(nullptr)));

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ 10, 10 });
    updateScoreText();

    infoText.setFont(font);
    infoText.setCharacterSize(40);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition({ 180, 200 });
    updateInfoText(isAlive);

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

void Game::updateInfoText(bool isAlive) {
    if (isAlive) {
        infoText.setString("Press W, A, S or D to start");
    }
    else {
        infoText.setPosition({ 250, 200 });
        infoText.setString("Game Over\nPoints: " + std::to_string(score) + "\nPress Esc to leave");
    }
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
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                exit = true;
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
            updateInfoText(isAlive);
        }
    }

    for (auto& border : borders) {
        if (snake.checkCollRec(border)) {
            isAlive = false;
            updateInfoText(isAlive);
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
    if (isAlive && snake.direction.x == 0.f && snake.direction.y == 0.f) {
        window.draw(infoText);
    }
    else if (!isAlive) {
        window.draw(infoText);
    }
    window.display();
}

void Game::run() {
    while (window.isOpen() && !exit) {
        handleInput();
        update();
        render();
    }
}
