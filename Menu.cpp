#include "Menu.h"

Menu::Menu() : menuWindow(sf::VideoMode({ 800, 600 }), "Snake"), font("ARIAL.ttf") {

	//Play
	sf::Text text(font);
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString("PLAY");
	text.setCharacterSize(70);
	text.setPosition({ 300, 100 });
	mainMenu.push_back(text);

	//Leaderboard
	text.setString("LEADERBOARD");
	text.setPosition({ 120, 200 });
	mainMenu.push_back(text);

	//Exit
	text.setString("Exit");
	text.setPosition({ 300, 300 });
	mainMenu.push_back(text);

	select = 1;
}

void Menu::up() {
	if (select - 1 >= -1) {
		mainMenu[select].setFillColor(sf::Color::White);

		select--;
		if (select == -1) {
			select = 2;
		}
		mainMenu[select].setFillColor(sf::Color::Green);
	}
}

void Menu::down() {
	if (select + 1 <= 3) {
		mainMenu[select].setFillColor(sf::Color::White);

		select++;
		if (select == 3) {
			select = 0;
		}
		mainMenu[select].setFillColor(sf::Color::Green);
	}
}

int Menu::selected() {
	return select;
}

void Menu::handleInputMenu() {
	while (const std::optional event = menuWindow.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			menuWindow.close();
		}
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
				up();
				break;

			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
				down();
				break;
			}
			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
				int x = selected();

				if (x == 0) {
					Game game(menuWindow);
					game.run();
				}
			}
		}
	}
}

void Menu::renderMenu() {
	menuWindow.clear();
	for (int i = 0; i < 3; ++i) {
		menuWindow.draw(mainMenu[i]);
	}
	menuWindow.display();
}

void Menu::runMenu() {
	while (menuWindow.isOpen()) {
		handleInputMenu();
		renderMenu();
	}
}