#include "../include/Vehicle.h"
#include "../include/NewVector.h"

Vehicle::Vehicle (sf::Vector2f loc) {
	mAcceleration = sf::Vector2f (0.0, 0.0);
	mVelocity = sf::Vector2f (0.0, 0.0);
	mLocation = loc;
	mRotation = 0.f;
	radius = 10;
	mMaxSpeed = 1.0;
	mMaxForce = 0.1;

	triangle.setPointCount (3);
	triangle.setPoint (0, sf::Vector2f (radius, 0));
	triangle.setPoint (1, sf::Vector2f (radius * 0.5, radius * 1.866));
	triangle.setPoint (2, sf::Vector2f (radius * 1.5, radius * 1.866));
	triangle.setFillColor (sf::Color::Green);
	triangle.setOrigin (radius, radius);
	triangle.setPosition (mLocation);
	triangle.setRotation (mRotation);
}

// Method to update location
void Vehicle::update () {
	// Update velocity
	mVelocity += mAcceleration;
	// Limit speed
	NewVector::getInstance ().limit (mVelocity, mMaxSpeed);
	mLocation += mVelocity;
	// Reset accelerationelertion to 0 each cycle
	mAcceleration = sf::Vector2f (0, 0);
	// Important to render the transform location and rotation
	triangle.setPosition (mLocation);
	triangle.setRotation (mRotation);
}

float Vehicle::getRotation () {
	return triangle.getRotation ();
}

sf::Vector2f Vehicle::getPosition () {
	return mLocation;
}

sf::Vector2f Vehicle::getVelocity () {
	return mVelocity;
}

float Vehicle::getMaxSpeed () {
	return mMaxForce;
}

void Vehicle::applyForce (sf::Vector2f force) {
	// We could add mass here if we want A = F / M
	mAcceleration += force;
}

// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
// set desired velocity angle as rotation
void Vehicle::arrive (sf::Vector2f target) {
	sf::Vector2f desired = target - mLocation;  // A vector pointing from the location to the target
	float distanceX = NewVector::getInstance ().mag (desired);
	desired = NewVector::getInstance ().norm (desired);

	// Scale with arbitrary damping within 100 pixels
	if (distanceX < 100.0) {
		desired *= NewVector::getInstance ().lmap (distanceX, sf::Vector2f (0, 0), sf::Vector2f (100.f, mMaxSpeed));
	} else {
		desired *= mMaxSpeed;
	}
	// set desired velocity angle as rotation
	mRotation = NewVector::getInstance ().rotation (desired);

	// Steering = Desired minus velocity
	sf::Vector2f steer = desired - mVelocity;
	NewVector::getInstance ().limit (steer, mMaxForce);  // Limit to maximum steering force

	applyForce (steer);
}

void Vehicle::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform ();
	states.texture = NULL;
	target.draw (triangle, states);
}