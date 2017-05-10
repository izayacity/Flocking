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
				std::cout << "Mouse Loc: " << mouse.x << ", " << mouse.y << std::endl;
				std::cout << "Vehicle Loc: " << mVehicle->getPosition ().x << ", " << mVehicle->getPosition ().y << std::endl;				
				std::cout << "Vehicle Velocity: " << NewVector::getInstance ().mag (mVehicle->getVelocity ()) << std::endl;
				std::cout << "Max Speed: " << mVehicle->getMaxSpeed () << std::endl;
				std::cout << std::endl;
			}
		}				

		window.clear ();
		window.draw (*mVehicle);
		window.display ();
	}
	delete (mVehicle);

	return 0;
}