#include "../include/Vehicle.h"

Vehicle::Vehicle (sf::Vector2f loc) {
	mAcceleration = sf::Vector2f (0.0, 0.0);
	mVelocity = sf::Vector2f (0.0, -2.0);
	mLocation = loc;
	radius = 10;
	mMaxSpeed = 4.0;
	mMaxForce = 0.1;

	triangle.setPointCount (3);
	triangle.setPoint (0, sf::Vector2f (radius, 0));
	triangle.setPoint (1, sf::Vector2f (radius * 0.5, radius * 1.866));
	triangle.setPoint (2, sf::Vector2f (radius * 1.5, radius * 1.866));
	triangle.setFillColor (sf::Color::Green);
	triangle.setOrigin (radius, radius);
	triangle.setPosition (mLocation);
}

// Method to update location
//void Vehicle::update () {
//	// Update velocity
//	mVelocity += mAcceleration;
//	// Limit speed
//	mVelocity.limit (mMaxSpeed);
//	mLocation += mVelocity;
//	// Reset accelerationelertion to 0 each cycle
//	mAcceleration = sf::Vector2f::zero ();
//}
//
//void Vehicle::applyForce (sf::Vector2f force) {
//	// We could add mass here if we want A = F / M
//	mAcceleration += force;
//}
//
//// A method that calculates a steering force towards a target
//// STEER = DESIRED MINUS VELOCITY
//void Vehicle::seek (sf::Vector2f target) {
//	sf::Vector2f desired = target - mLocation;  // A vector pointing from the location to the target
//										 // Scale to maximum speed
//										 // set mag are these 2 functions combined into 1 function
//	desired.normalize ();
//	desired *= mMaxSpeed;
//
//	// Steering = Desired minus velocity
//	sf::Vector2f steer = desired - mVelocity;
//	steer.limit (mMaxForce);  // Limit to maximum steering force
//
//	applyForce (steer);
//}

void Vehicle::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform ();
	states.texture = NULL;
	target.draw (triangle, states);
}