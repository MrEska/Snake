#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Game.h"

class Menu {
private:
	int select;
	sf::RenderWindow menuWindow;
	sf::Font font;
	std::vector<sf::Text> mainMenu;

	void renderMenu();
	void handleInputMenu();

public:
	Menu();
	void runMenu();
	void up();
	void down();
	int selected();
};

