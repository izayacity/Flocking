#pragma once
#include <array>
#include <algorithm>
#include "Boid.h"

class Flock : public sf::Drawable, public sf::Transformable {
	const int gameWidth = 1280;
	const int gameHeight = 720;
	static const int COLUMNS = 10;
	static const int ROWS = 10;
	int gridWidth;
	int gridHeight;
	std::vector<Boid*>	mBoids;
	std::vector<Boid*> grid[ROWS][COLUMNS];
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
	sf::Vector2i getBucket (sf::Vector2f pos);
	void bucketRemove (sf::Vector2i bucket, Boid* obj);
	void bucketAdd (sf::Vector2i bucket, Boid* obj);
};