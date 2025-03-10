#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Snake");
    window.setFramerateLimit(60);
    
    std::vector<sf::RectangleShape> snake;
    sf::RectangleShape head(sf::Vector2f(20.f, 20.f));
    head.setFillColor(sf::Color::Green);
    head.setPosition({ 800 / 2.0f, 600 / 2.0f });
    for (int i = 0; i < 7; i++) snake.push_back(head);

    sf::CircleShape point(10.f);
    float width = rand() % 790, height = rand() % 590;
    point.setPosition({width, height});

    sf::Vector2f direction(0.f, 0.f);
    float speed = 3.f;
    sf::Clock clock;

    bool isAlive = true;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

                if (keyPressed->scancode == sf::Keyboard::Scancode::W && direction.y == 0) {
                    direction = { 0.f, -speed };
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A && direction.x == 0) {                  
                    direction = { -speed, 0.f };                
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::S && direction.y == 0) {                 
                    direction = { 0.f, speed };                
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D && direction.x == 0) {                   
                    direction = { speed, 0.f };
                }             
            }
        }

        if (isAlive && clock.getElapsedTime().asMilliseconds() > 30) {            
            for (size_t i = snake.size() - 1 ; i > 0; i--) {
                sf::Vector2f lastSegPosition = snake[i - 1].getPosition();                                                            
                snake[i].setPosition(lastSegPosition);
            }
            clock.restart();
        }
        if (isAlive) {
            snake[0].move(direction);
        }

        for (int i = 7; i < snake.size(); i++) {
            if (snake[0].getGlobalBounds().findIntersection(snake[i].getGlobalBounds())) {
                isAlive = false;
            }
        }

        if (snake[0].getGlobalBounds().findIntersection(point.getGlobalBounds())) {           
            height = std::rand() % 590, width = std::rand() % 790;
            point.setPosition({ width, height });

            sf::RectangleShape newSegment(sf::Vector2f(20.f, 20.f));
            newSegment.setFillColor(sf::Color::Green);

            sf::Vector2f lastSegPosition = snake.back().getPosition();

            if (direction.x > 0) lastSegPosition.x -= 20.f;
            if (direction.x < 0) lastSegPosition.x += 20.f;
            if (direction.y > 0) lastSegPosition.y -= 20.f;
            if (direction.y < 0) lastSegPosition.y += 20.f;

            newSegment.setPosition(lastSegPosition);
            snake.push_back(newSegment);
        }               

        window.clear();

        window.draw(point);
        for (const auto segment : snake) {
            window.draw(segment);
        }

        window.display();
    }
}