#pragma once
#include <array>
#include "Boid.h"

class Flock : public sf::Drawable, public sf::Transformable {
	std::vector<Boid*>	mBoids;
	int mCount;
	std::array<float, 3> weight;
public:
	Flock ();
	~Flock ();
	int getCount ();
	void update ();
	void addBoid (sf::Vector2f loc);
	void reduceBoid ();
	std::array<float, 3> getWeight ();
	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
	void updateWeight (int sep, int coh, int ali);
};