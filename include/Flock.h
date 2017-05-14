#pragma once

#include "Boid.h"

class Flock : public sf::Drawable, public sf::Transformable {
	std::vector<Boid*>	mBoids;

public:
	Flock ();
	~Flock ();
	void update ();
	void addBoid (sf::Vector2f loc);
	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
};