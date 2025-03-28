#include "Snake.h"

Snake::Snake() : direction(0.f, 0.f), speed(6.f) {
    sf::RectangleShape segment(sf::Vector2f(25.f, 25.f));
    segment.setFillColor(sf::Color::Green);
    segment.setPosition({ 400, 300 });
    for (int i = 0; i < 9; i++) body.push_back(segment);
}

void Snake::move() {
    for (size_t i = body.size() - 1; i > 0; i--) {
        sf::Vector2f lastSegPosition = body[i - 1].getPosition();
        body[i].setPosition(lastSegPosition);
    }
    body[0].move(direction);
}

void Snake::grow() {
    sf::RectangleShape newSegment(sf::Vector2f(25.f, 25.f));
    newSegment.setFillColor(sf::Color::Green);

    sf::Vector2f lastSegPosition = body.back().getPosition();

    if (direction.x > 0) lastSegPosition.x -= 20.f;
    if (direction.x < 0) lastSegPosition.x += 20.f;
    if (direction.y > 0) lastSegPosition.y -= 20.f;
    if (direction.y < 0) lastSegPosition.y += 20.f;

    newSegment.setPosition(lastSegPosition);
    body.push_back(newSegment);
}

bool Snake::checkCollRec(const sf::RectangleShape& obj) {
    return body[0].getGlobalBounds().findIntersection(obj.getGlobalBounds()).has_value();
}

bool Snake::checkCollCir(const sf::CircleShape& PT) {
    return body[0].getGlobalBounds().findIntersection(PT.getGlobalBounds()).has_value();
}
