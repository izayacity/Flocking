#include "../include/NewVector.h"

float NewVector::mag (sf::Vector2f vec) {
	return std::sqrt (vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f NewVector::norm (sf::Vector2f vec) {
	return vec / mag (vec);
}

void NewVector::limit (sf::Vector2f &vec, float limit) {
	if (mag (vec) > limit) {
		vec = norm (vec) * limit;
	}
}

float NewVector::lmap (float val, sf::Vector2f min, sf::Vector2f max) {
	return min.y + ((max.y - min.y) * (val - min.x)) / (max.x - min.x);
}