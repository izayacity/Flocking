#pragma once
#include <SFML/Graphics.hpp>
#include "Path.h"
#include <iostream>

class Boid : public sf::Drawable, public sf::Transformable {
private:
	sf::ConvexShape triangle;
	sf::Vector2f mLocation;
	sf::Vector2f mVelocity;
	sf::Vector2f mAcceleration;
	float radius;       // Additional variable for size
	float mMaxForce;    // Maximum steering force
	float mMaxSpeed;    // Maximum speed
	float mBoundaryWidth;
	float weight [3];
	const int gameWidth = 1280;
	const int gameHeight = 720;	
public:
	bool mDebug;
	sf::Vertex predict_line[2];
	sf::Vertex norm_line[2];

	Boid (sf::Vector2f loc);
	void update ();
	void applyForce (sf::Vector2f force);
	sf::Vector2f arrive (sf::Vector2f target);
	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f getPosition ();
	sf::Vector2f getVelocity ();	
	float getMaxSpeed ();
	void setSpeed (float speed);
	void boundaries ();
	void flock (std::vector<Boid*>* const boids);
	sf::Vector2f separate (std::vector<Boid*>* const boids);
	sf::Vector2f align (std::vector<Boid*>* const boids);
	sf::Vector2f cohesion (std::vector<Boid*>* const boids);
	void setWeight (float sep, float coh, float ali);
	sf::Vector2f follow (Path* const path);
};