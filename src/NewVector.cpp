#include "../include/NewVector.h"
#include <math.h>

float NewVector::mag (sf::Vector2f vec) {
	return std::sqrt (vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f NewVector::norm (sf::Vector2f vec) {
	return vec / std::sqrt (vec.x * vec.x + vec.y * vec.y);
}

void NewVector::limit (sf::Vector2f &vec, float limit) {
	float mag = std::sqrt (vec.x * vec.x + vec.y * vec.y);

	if (mag > limit) {
		vec = vec / mag * limit;
	}
}

float NewVector::lmap (float val, sf::Vector2f min, sf::Vector2f max) {
	return min.y + ((max.y - min.y) * (val - min.x)) / (max.x - min.x);
}

float NewVector::rotation (sf::Vector2f vec) {	
	if (vec.y <= 0) {
		return asin (vec.x / std::sqrt (vec.x * vec.x + vec.y * vec.y)) * 180.f / PI;
	} else {
		if (vec.x == 0) {
			return 180.f;
		} else if (vec.x > 0) {
			return atan (vec.y / vec.x) * 180.f / PI + 90.f;
		} else if (vec.x < 0) {
			return atan (vec.y / vec.x) * 180.f / PI - 90.f;
		}
	}
}

float NewVector::dot (sf::Vector2f vec1, sf::Vector2f vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

// A function to get the normal point from a point (p) to a line segment (a-b)
// This function could be optimized to make fewer new Vector objects
sf::Vector2f NewVector::getNormalPoint (sf::Vector2f p, sf::Vector2f a, sf::Vector2f b) {	
	sf::Vector2f ab = b - a;  // Vector from a to b
	ab = ab / std::sqrt (ab.x * ab.x + ab.y * ab.y);

	// Project vector "diff" onto line by using the dot product
	ab *= dot (p - a, ab);
	return a + ab;
}