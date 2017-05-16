#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

class Path : public sf::Drawable, public sf::Transformable {
public:
	static const int gameWidth = 1280;
	static const int gameHeight = 720;

	Path ();
	~Path ();
	// A Path is line between two points (Vec2f objects)
	//sf::Vector2f mStart, mEnd;
	// A path has a radius, i.e how far is it ok for the boid to wander off
	float mRadius;
	// A Path is a vector of points (Vec2f objects)
	std::vector<sf::Vector2f> mPoints;
	std::vector<std::array<sf::Vertex, 2>> lines;

	void addPoint (sf::Vector2f pt);
	void setPath ();
	sf::Vector2f getStart ();
	sf::Vector2f getEnd ();
	virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const;
};
