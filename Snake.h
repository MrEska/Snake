#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Snake {
public:
	std::vector<sf::RectangleShape> body;
	sf::Vector2f direction;
	float speed;

	Snake();
	void move();
	void grow();
	bool checkCollRec(const sf::RectangleShape& obj);
	bool checkCollCir(const sf::CircleShape& obj);
};

