#include "../include/Path.h"


Path::Path () {
	// Arbitrary radius of 40
	mRadius = 40.0;
}

Path::~Path () {
	lines.clear ();
	mPoints.clear ();
}

// Add a point to the path
void Path::addPoint (sf::Vector2f pt) {
	mPoints.push_back (pt);
}

sf::Vector2f Path::getStart () {
	return mPoints[0];
}

sf::Vector2f Path::getEnd () {
	return mPoints[mPoints.size () - 1];
}

// Draw the path
void Path::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform ();
	states.texture = NULL;

	for (auto obj : lines) {
		sf::Vertex line[2];
		line[0] = obj[0];
		line[1] = obj[1];
		target.draw (line, 2, sf::Lines, states);
	}
}

void Path::setPath () {
	mPoints.push_back (sf::Vector2f (640.f, 160.f));
	mPoints.push_back (sf::Vector2f (940.f, 360.f));
	mPoints.push_back (sf::Vector2f (640.f, 560.f));
	mPoints.push_back (sf::Vector2f (340.f, 360.f));
	
	for (unsigned int i = 0; i <= mPoints.size () - 2; i++) {
		std::array<sf::Vertex, 2> line = {
			mPoints[i],
			mPoints[i + 1]
		};

		lines.push_back (line);
	}

	// close the last gap
	std::array<sf::Vertex, 2> line = {
		mPoints[mPoints.size () - 1],
		mPoints[0]
	};

	lines.push_back (line);
}