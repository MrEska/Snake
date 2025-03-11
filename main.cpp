#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Snake");
    window.setFramerateLimit(60);
    
    //snake body
    std::vector<sf::RectangleShape> snake;
    sf::RectangleShape head(sf::Vector2f(20.f, 20.f));
    head.setFillColor(sf::Color::Green);
    head.setPosition({ 400, 300 });
    for (int i = 0; i < 7; i++) snake.push_back(head);

    //point
    sf::CircleShape point(10.f);
    float width = rand() % 750, height = rand() % 550;
    point.setPosition({width, height});

    //map's borders
    std::vector<sf::RectangleShape> borders;
    sf::RectangleShape border(sf::Vector2f(800.f, 10.f));
    border.setFillColor(sf::Color::White);
    for (int i = 0; i < 4; i++) borders.push_back(border);
    borders[0].setPosition({ 0, 1 });
    borders[1].setPosition({ 800, 0 });
    borders[1].rotate(sf::degrees(90));
    borders[2].setPosition({ 0, 590 });
    borders[3].setPosition({ 10, 1});
    borders[3].rotate(sf::degrees(90));

    //points counter
    sf::Font font("ARIAL.ttf");
    sf::Text text(font);
    int counter = 0;
    text.setString("Points: " + std::to_string(counter));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition({ 20, 10 });

    //variables
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
                //controls
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

        //movement
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

        //hit check
        for (int i = 7; i < snake.size(); i++) {
            if (snake[0].getGlobalBounds().findIntersection(snake[i].getGlobalBounds())) {
                isAlive = false;
            }        
        }
        for (int j = 0; j < 4; j++) {
            if (snake[0].getGlobalBounds().findIntersection(borders[j].getGlobalBounds())) {
                isAlive = false;
            }
        }

        //collect point check
        if (snake[0].getGlobalBounds().findIntersection(point.getGlobalBounds())) {           
            height = std::rand() % 550, width = std::rand() % 750;
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

            counter++;
            text.setString("Points: " + std::to_string(counter));           
        }               

        window.clear();

        window.draw(point);
        for (const auto segment : snake) {
            window.draw(segment);
        }
        for (const auto bor : borders) {
            window.draw(bor);
        }
        window.draw(text);

        window.display();
    }
}