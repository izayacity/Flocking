#pragma once
#include <SFML/Graphics.hpp>

class NewVector {
private:
	NewVector () {}

public:
	static NewVector& getInstance () {
		static NewVector instance;
		return instance;
	}

	NewVector (NewVector const&) = delete;
	void operator=(NewVector const&) = delete;

	float mag (sf::Vector2f vec);
	sf::Vector2f norm (sf::Vector2f vec);
	void limit (sf::Vector2f &vec, float limit);
	float lmap (float val, sf::Vector2f min, sf::Vector2f max);
};