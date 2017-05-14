#include "../include/Flock.h"

Flock::Flock () {
	mCount = 0;
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
	mCount++;
}

void Flock::reduceBoid () {
	if (mCount <= 0) {
		return;
	} else if (mCount == 1) {
		mBoids.pop_back ();
		mCount--;
	} else {
		for (int target = mCount / 2; mCount > target; mCount--) {
			mBoids.pop_back ();
		}
	}
}

// Apply the transform and draw the vertext array
void Flock::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform ();
	states.texture = NULL;

	for (auto p : mBoids) {
		target.draw (*p, states);
	}
}