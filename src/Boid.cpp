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
	weight[0] = 1.5f;
	weight[1] = 1.f;
	weight[2] = 1.f;
	mDebug = true;

	triangle.setPointCount (3);
	triangle.setPoint (0, sf::Vector2f (radius, 0));
	triangle.setPoint (1, sf::Vector2f (radius * 0.5, radius * 1.866));
	triangle.setPoint (2, sf::Vector2f (radius * 1.5, radius * 1.866));
	triangle.setFillColor (sf::Color::Color (std::rand () % 255, std::rand () % 255, std::rand () % 255, 100));
	triangle.setOrigin (radius, radius);
	triangle.setPosition (mLocation);
}

// Method to update location
void Boid::update () {
	boundaries ();
	mVelocity += mAcceleration;
	NewVector::getInstance ().limit (mVelocity, mMaxSpeed);
	mLocation += mVelocity;
	mAcceleration = sf::Vector2f (0, 0);
	triangle.setPosition (mLocation);
	triangle.setRotation (NewVector::getInstance ().rotation (mVelocity));
}

// calculate velocity and bound back when hitting the edge of the screen
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

// We accumulate a new acceleration each time based on three rules
void Boid::flock (std::vector<Boid*>* const boids) {
	sf::Vector2f sep = separate (boids);		// Separation
	sf::Vector2f ali = align (boids);			// Alignment
	sf::Vector2f coh = cohesion (boids);		// Cohesion
										// Arbitrarily weight these forces
	sep *= weight[0];
	ali *= weight[1];
	coh *= weight[2];
	// Add the force vectors to acceleration
	applyForce (sep);
	applyForce (ali);
	applyForce (coh);
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
	mAcceleration += force;  // We could add mass here if we want A = F / M
}

// A method that calculates a steering force towards a target
sf::Vector2f Boid::arrive (sf::Vector2f target) {
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

	return steer;
}

// Separation: Method checks for nearby Boids and steers away
sf::Vector2f Boid::separate (std::vector<Boid*>* const Boids) {
	float desiredseparation = 25.0f;
	sf::Vector2f steer = sf::Vector2f (0, 0);
	int count = 0;
	// For every boid in the system, check if it's too close
	for (Boid *other : *Boids) {
		float d = NewVector::getInstance ().mag (mLocation - other->mLocation);
		// If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
		if ((d > 0) && (d < desiredseparation)) {
			// Calculate vector pointing away from neighbor
			sf::Vector2f diff = mLocation - other->mLocation;
			diff = NewVector::getInstance ().norm (diff);
			diff /= d;			// Weight by distance
			steer += diff;
			count++;            // Keep track of how many
		}
	}
	// Average -- divide by how many
	if (count > 0) {
		steer /= count * 1.f;
	}

	// As long as the vector is greater than 0
	if (NewVector::getInstance ().mag (steer) > 0) {
		// Implement Reynolds: Steering = Desired - Velocity
		steer = NewVector::getInstance ().norm (steer);
		steer *= mMaxSpeed;
		steer -= mVelocity;
		NewVector::getInstance ().limit (steer, mMaxForce);
	}

	return steer;
}

// Cohesion: For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
sf::Vector2f Boid::cohesion (std::vector<Boid*>* const Boids) {
	float neighbordist = 50;
	sf::Vector2f sum = sf::Vector2f (0, 0);   // Start with empty vector to accumulate all locations
	int count = 0;
	for (Boid *other : *Boids) {
		float d = NewVector::getInstance ().mag (mLocation - other->mLocation);
		if ((d > 0) && (d < neighbordist)) {
			sum += other->mLocation; // Add location
			count++;
		}
	}
	if (count > 0) {
		sum /= count * 1.f;
		return arrive (sum);  // Steer towards the location
	} else {
		return sf::Vector2f (0, 0);
	}
}

// Alignment: For every nearby boid in the system, calculate the average velocity
sf::Vector2f Boid::align (std::vector<Boid*>* const Boids) {
	float neighbordist = 50;
	sf::Vector2f sum = sf::Vector2f (0, 0);
	int count = 0;
	for (Boid *other : *Boids) {
		float d = NewVector::getInstance ().mag (mLocation - other->mLocation);
		if ((d > 0) && (d < neighbordist)) {
			sum += other->mVelocity;
			count++;
		}
	}
	if (count > 0) {
		sum /= count * 1.f;
		sum = NewVector::getInstance ().norm (sum);
		sum *= mMaxSpeed;
		sf::Vector2f steer = sum - mVelocity;
		NewVector::getInstance ().limit (steer, mMaxForce);
		return steer;
	} else {
		return sf::Vector2f (0, 0);
	}
}

void Boid::setWeight (float sep, float coh, float ali) {
	weight[0] = sep;
	weight[1] = coh;
	weight[2] = ali;
}

// http://www.red3d.com/cwr/steer/PathFollow.html
sf::Vector2f Boid::follow (Path* const path) {
	// Predict location 25 (arbitrary choice) frames ahead
	sf::Vector2f predict = sf::Vector2f (mVelocity);
	predict = NewVector::getInstance ().norm (predict);
	predict *= 25.f;
	sf::Vector2f predictLoc = mLocation + predict;	

	// Now we must find the normal to the path from the predicted location
	// We look at the normal for each line segment and pick out the closest one
	sf::Vector2f normal;
	sf::Vector2f target;
	float worldRecord = 1000000.0;  // Start with a very high record distance that can easily be beaten

	// Loop through all points of the path
	for (int i = 0; i < path->mPoints.size () - 1; i++) {
		// Look at a line segment and get the normal point to that line
		sf::Vector2f a = path->mPoints[i];
		sf::Vector2f b = path->mPoints[i + 1];
		sf::Vector2f normalPoint = NewVector::getInstance ().getNormalPoint (predictLoc, a, b);

		// This only works because we know our path goes from left to right
		// We could have a more sophisticated test to tell if the point is in the line segment or not
		if (normalPoint.x < a.x || normalPoint.x > b.x) {
			// This is something of a hacky solution, but if it's not within the line segment
			// consider the normal to just be the end of the line segment (point b)
			normalPoint = b;
		}

		// How far away are we from the path?
		float distance = NewVector::getInstance ().mag (predictLoc - normalPoint);

		// find the closest line segment for distance
		if (distance < worldRecord) {
			worldRecord = distance;
			// If so the target we want to steer towards is the normal
			normal = normalPoint;

			// Look at the direction of the line segment so we can seek a little bit ahead of the normal
			sf::Vector2f dir = b - a;
			dir = NewVector::getInstance ().norm (dir);
			// This is an oversimplification
			// Should be based on distance to path & velocity
			dir *= 10.f;
			target = normalPoint;
			target += dir;
		}
	}

	// check the last gap
	sf::Vector2f a = path->mPoints[path->mPoints.size () - 1];
	sf::Vector2f b = path->mPoints[0];
	sf::Vector2f normalPoint = NewVector::getInstance ().getNormalPoint (predictLoc, a, b);

	// This only works because we know our path goes from left to right
	// We could have a more sophisticated test to tell if the point is in the line segment or not
	if (normalPoint.x < a.x || normalPoint.x > b.x) {
		// This is something of a hacky solution, but if it's not within the line segment
		// consider the normal to just be the end of the line segment (point b)
		normalPoint = b;
	}

	// How far away are we from the path?
	float distance = NewVector::getInstance ().mag (predictLoc - normalPoint);

	// find the closest line segment for distance
	if (distance < worldRecord) {
		worldRecord = distance;
		// If so the target we want to steer towards is the normal
		normal = normalPoint;

		// Look at the direction of the line segment so we can seek a little bit ahead of the normal
		sf::Vector2f dir = b - a;
		dir = NewVector::getInstance ().norm (dir);
		// This is an oversimplification
		// Should be based on distance to path & velocity
		dir *= 10.f;
		target = normalPoint;
		target += dir;
	}

	// Only if the distance is greater than the path's radius do we bother to steer
	if (worldRecord > path->mRadius) {
		return arrive (target);
	}

	// Draw the debugging stuff
	//if (mDebug) {
	//	// Draw predicted future location
	//	predict_line[2] = {
	//		mLocation,
	//		predictLoc
	//	};

	//	// Draw normal location
	//	norm_line[2] = {
	//		predictLoc,
	//		normal
	//	};
	//}
}

// render on screen
void Boid::draw (sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform ();
	states.texture = NULL;
	target.draw (triangle, states);

	/*if (mDebug) {
		target.draw (predict_line, 2, sf::Lines, states);
		target.draw (norm_line, 2, sf::Lines, states);
	}*/
}