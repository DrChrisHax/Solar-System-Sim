#pragma once

#include <SFML/Graphics.hpp>

//const float G = 6.674e-11f;
const float G = 0.1f;

class PointMass {
public:
	PointMass(float radius, float mass, sf::Vector2f position, sf::Vector2f velocity);

	//Operation Overloads
	bool operator == (const PointMass);

	//Getters & Setters
	float getMass() const;
	sf::Vector2f getPosition() const;

	//Calculations
	void calcAcceleration(const std::vector<PointMass>&);

	//Rendering
	void draw(sf::RenderWindow& window);
	void move();
private:
	float mMass;
	sf::Vector2f mVelocity;
	sf::CircleShape mShape;
};