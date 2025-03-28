#include "Point.h"
#include <cstdlib>

Point::Point() {
	pt.setRadius(10.f);
	pt.setFillColor(sf::Color::White);
}

void Point::locate() {
	pt.setPosition({ static_cast<float>(rand() % 750), static_cast<float>(rand() % 550)});
}
