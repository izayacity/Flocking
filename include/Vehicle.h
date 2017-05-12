#pragma once
#include <SFML/Graphics.hpp>

class Vehicle : public sf::Drawable, public sf::Transformable {
private:
	sf::ConvexShape triangle;
	sf::Vector2f mLocation;
	sf::Vector2f mVelocity;
	sf::Vector2f mAcceleration;
	float mRotation;
	float radius;       // Additional variable for size
	float mMaxForce;    // Maximum steering force
	float mMaxSpeed;    // Maximum speed

public:
	Vehicle (sf::Vector2f loc);
	void update ();
	void applyForce (sf::Vector2f force);
	void arrive (sf::Vector2f target);
	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition ();
	sf::Vector2f getVelocity ();
	float getMaxSpeed ();
	float getRotation ();
};