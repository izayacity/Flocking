#include "../include/Flock.h"

Flock::Flock () {

}

Flock::~Flock () {
	mBoids.clear ();
}

void Flock::update () {
	for (Boid *b : mBoids) {
		b->update ();
	}
}

void Flock::addBoid (sf::Vector2f loc) {
	Boid *mBoid = new Boid (loc);
	mBoids.push_back (mBoid);
}

// Apply the transform and draw the vertext array
void Flock::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform ();
	states.texture = NULL;

	for (auto p : mBoids) {
		target.draw (*p, states);
	}
}