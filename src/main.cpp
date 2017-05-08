#include <SFML/Graphics.hpp>
#include "../include/Vehicle.h"

int main () {
	const int gameWidth = 800;
	const int gameHeight = 600;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window (sf::VideoMode (gameWidth, gameHeight), "Flocking", sf::Style::Default, settings);
	Vehicle v_vehicle (sf::Vector2f (gameWidth / 2, gameHeight / 2));

	while (window.isOpen ()) {
		sf::Event event;
		while (window.pollEvent (event)) {
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				window.close ();
			}
		}

		window.clear ();
		window.draw (v_vehicle);
		window.display ();
	}

	return 0;
}