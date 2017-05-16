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

	const float PI = 3.14;
	std::map <float, float> sin_table;
	std::map <float, float> cos_table;

	NewVector (NewVector const&) = delete;
	void operator=(NewVector const&) = delete;

	float mag (sf::Vector2f vec);
	sf::Vector2f norm (sf::Vector2f vec);
	void limit (sf::Vector2f &vec, float limit);
	float lmap (float val, sf::Vector2f min, sf::Vector2f max);
	float rotation (sf::Vector2f vec);
	float dot (sf::Vector2f vec1, sf::Vector2f vec2);
	sf::Vector2f getNormalPoint (sf::Vector2f p, sf::Vector2f a, sf::Vector2f b);
};