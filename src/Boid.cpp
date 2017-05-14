#include "../include/Boid.h"
#include "../include/NewVector.h"

Boid::Boid (sf::Vector2f loc) {
	mAcceleration = sf::Vector2f (0.0, 0.0);
	mVelocity = sf::Vector2f ((std::rand () % 200 - 100) * 0.01, (std::rand () % 200 - 100) * 0.01);
	mLocation = loc;
	radius = 10;
	mMaxSpeed = 1.0;
	mMaxForce = 0.1;
	mBoundaryWidth = 25.0;

	triangle.setPointCount (3);
	triangle.setPoint (0, sf::Vector2f (radius, 0));
	triangle.setPoint (1, sf::Vector2f (radius * 0.5, radius * 1.866));
	triangle.setPoint (2, sf::Vector2f (radius * 1.5, radius * 1.866));
	triangle.setFillColor (sf::Color::Green);
	triangle.setOrigin (radius, radius);
	triangle.setPosition (mLocation);
}

// Method to update location
void Boid::update () {
	// calculate velocity
	boundaries ();
	// Update velocity
	mVelocity += mAcceleration;
	// Limit speed
	NewVector::getInstance ().limit (mVelocity, mMaxSpeed);
	mLocation += mVelocity;
	// Reset accelerationelertion to 0 each cycle
	mAcceleration = sf::Vector2f (0, 0);
	// Important to render the transform location and rotation
	triangle.setPosition (mLocation);
	triangle.setRotation (NewVector::getInstance ().rotation (mVelocity));
}

void Boid::setSpeed (float speed) {
	mMaxSpeed = speed;
}

sf::Vector2f Boid::getPosition () {
	return mLocation;
}

sf::Vector2f Boid::getVelocity () {
	return mVelocity;
}

float Boid::getMaxSpeed () {
	return mMaxForce;
}

void Boid::applyForce (sf::Vector2f force) {
	// We could add mass here if we want A = F / M
	mAcceleration += force;
}

// A method that calculates a steering force towards a target
// STEER = DESIRED MINUS VELOCITY
void Boid::arrive (sf::Vector2f target) {
	sf::Vector2f desired = target - mLocation;  // A vector pointing from the location to the target
	float distanceX = NewVector::getInstance ().mag (desired);
	desired = NewVector::getInstance ().norm (desired);

	// Scale with arbitrary damping within 100 pixels
	if (distanceX < 100.0) {
		desired *= NewVector::getInstance ().lmap (distanceX, sf::Vector2f (0, 0), sf::Vector2f (100.f, mMaxSpeed));
	} else {
		desired *= mMaxSpeed;
	}

	// Steering = Desired minus velocity
	sf::Vector2f steer = desired - mVelocity;
	NewVector::getInstance ().limit (steer, mMaxForce);  // Limit to maximum steering force
	applyForce (steer);
}

void Boid::boundaries () {
	sf::Vector2f desired = sf::Vector2f (0, 0);

	if (mLocation.x < mBoundaryWidth) {
		desired = sf::Vector2f (mMaxSpeed, mVelocity.y);
	} else if (mLocation.x > gameWidth - mBoundaryWidth) {
		desired = sf::Vector2f (-mMaxSpeed, mVelocity.y);
	}

	if (mLocation.y < mBoundaryWidth) {
		desired = sf::Vector2f (mVelocity.x, mMaxSpeed);
	} else if (mLocation.y > gameHeight - mBoundaryWidth) {
		desired = sf::Vector2f (mVelocity.x, -mMaxSpeed);
	}

	if (desired != sf::Vector2f (0, 0)) {
		desired = NewVector::getInstance ().norm (desired);
		desired *= mMaxSpeed;		
		sf::Vector2f steer = desired - mVelocity;
		NewVector::getInstance ().limit (steer, mMaxForce);
		applyForce (steer);
	}
}

void Boid::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform ();
	states.texture = NULL;
	target.draw (triangle, states);
}