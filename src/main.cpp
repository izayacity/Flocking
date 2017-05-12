#include <SFML/Graphics.hpp>
#include "../include/Vehicle.h"
#include "../include/NewVector.h"
#include <iostream>

int main () {
	const int gameWidth = 800;
	const int gameHeight = 600;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window (sf::VideoMode (gameWidth, gameHeight), "Flocking", sf::Style::Default, settings);
	Vehicle *mVehicle = new Vehicle (sf::Vector2f (gameWidth / 2, gameHeight / 2));

	while (window.isOpen ()) {
		sf::Event event;
		sf::Vector2i mouse = sf::Mouse::getPosition (window);		
		mVehicle->arrive (window.mapPixelToCoords (mouse));
		mVehicle->update ();

		while (window.pollEvent (event)) {
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
				window.close ();
			}

			else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::P)) {
				//std::cout << std::endl;
			}
		}				

		window.clear ();
		window.draw (*mVehicle);
		window.display ();
	}
	delete (mVehicle);

	return 0;
}