#pragma once

#include "Boid.h"

class Flock : public sf::Drawable, public sf::Transformable {
	std::vector<Boid*>	mBoids;
	int mCount;
public:
	Flock ();
	~Flock ();
	int getCount ();
	void update ();
	void addBoid (sf::Vector2f loc);
	void reduceBoid ();
	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
};