#include "PointMass.hpp"



PointMass::PointMass(float radius, float mass, sf::Vector2f position, sf::Vector2f velocity) : mMass(mass), mVelocity(velocity)
{
	mShape.setRadius(radius);
	mShape.setFillColor(sf::Color::White);
	mShape.setPosition(position);
}

//Operation Overloads
bool PointMass::operator == (const PointMass obj) {
	return mMass == obj.mMass && mShape.getPosition() == obj.mShape.getPosition() && mShape.getRadius() == obj.mShape.getRadius();
}

//Getters & Setters
float PointMass::getMass() const { return mMass; }
sf::Vector2f PointMass::getPosition() const { return mShape.getPosition(); }

//Calculations
void PointMass::calcAcceleration(const std::vector<PointMass>& objects) {
   sf::Vector2f acceleration = sf::Vector2f(0.f, 0.f);

    for (const PointMass& object : objects) {
        if (*this == object) { continue; }
            sf::Vector2f direction = object.getPosition() - this->getPosition();
            float distanceSquared = direction.x * direction.x + direction.y * direction.y;
            float distance = std::sqrt(distanceSquared);
            float forceMagnitude = (G * object.getMass()) / distanceSquared; 

            sf::Vector2f force = (forceMagnitude / distance) * direction;
            acceleration += force / mMass; 
        }
    mVelocity += acceleration;
}

//Rendering
void PointMass::draw(sf::RenderWindow& window) { window.draw(mShape); }
void PointMass::move()
{
	sf::Vector2f newPosition = mShape.getPosition();
	newPosition.x += mVelocity.x;
	newPosition.y += mVelocity.y;

	mShape.setPosition(newPosition);
}



