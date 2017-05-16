#include "../include/Flock.h"

Flock::Flock () {
	mCount = 0;
	weight[0] = 1.5f;
	weight[1] = 1.f;
	weight[2] = 1.f;
	gridWidth = gameWidth / COLUMNS;
	gridHeight = gameHeight / ROWS;
	isPath = false;
	path.setPath ();
}

Flock::~Flock () {
	mBoids.clear ();
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLUMNS; j++) {
			grid[i][j].clear ();
		}
}

void Flock::update () {
	for (auto boid : mBoids) {
		sf::Vector2i curBucket = getBucket (boid->getPosition());
		boid->update ();
		sf::Vector2i newBucket = getBucket (boid->getPosition ());
		
		if (curBucket != newBucket) {
			bucketRemove (curBucket, boid);
			bucketAdd (newBucket, boid);
		}

		if (isPath) {
			boid->applyForce (boid->follow (&path));
		}
		
		boid->flock (&grid[newBucket.x][newBucket.y]);
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

int Flock::getCount () {
	return mCount;
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
		return;
	} else {
		for (int target = mCount / 2; mCount > target; mCount--) {
			mBoids.pop_back ();
		}
	}
}

std::array<float, 3> Flock::getWeight () {
	return weight;
}

void Flock::updateWeight (int sep, int coh, int ali) {
	weight[0] += 0.1 * sep;
	weight[1] += 0.1 * coh;
	weight[2] += 0.1 * ali;

	for (auto boid : mBoids) {
		boid->setWeight (weight[0], weight[1], weight[2]);
	}
}

sf::Vector2i Flock::getBucket (sf::Vector2f pos) {
	return sf::Vector2i (pos.x / gridWidth, pos.y / gridHeight);
}

// remove obj from grid[bucket.x][bucket.y]
void Flock::bucketRemove (sf::Vector2i bucket, Boid* obj) {
	auto i = std::find (grid[bucket.x][bucket.y].begin (), grid[bucket.x][bucket.y].end (), obj);
	if (i != grid[bucket.x][bucket.y].end ()) {
		grid[bucket.x][bucket.y].erase (i);
	}
}

// add obj to grid[bucket.x][bucket.y]
void Flock::bucketAdd (sf::Vector2i bucket, Boid* obj) {
	grid[bucket.x][bucket.y].push_back (obj);
}
