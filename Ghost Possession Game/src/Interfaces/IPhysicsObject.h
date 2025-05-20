#pragma once

#include <SFML/graphics.hpp>

#include "../Visual.h"

class IPhysicsObject
{
public:

	IPhysicsObject() = default;

	void updateGravity(float dt)
	{
		m_velocity += m_gravity*dt;
	}

	void haltX() { m_velocity.x = 0; }

	void haltY() { m_velocity.y = 0; }

	void setVelocity(float x, float y)
	{
		m_velocity = { x, y };
	}
	void setVelocity(sf::Vector2f vec)
	{
		m_velocity = vec;
	}

	void addVelocity(float x, float y) { m_velocity += sf::Vector2f(x, y); }
	void addVelocity(sf::Vector2f vec) { m_velocity += vec; }

	void setGravity(float x, float y)
	{
		m_gravity = { x, y };
	}
	void setGravity(sf::Vector2f vec)
	{
		m_gravity = vec;
	}

	virtual sf::Vector2f outsideCollision(Visual& moving_obj, const Visual& static_obj);

private:

	sf::Vector2f shortestOffset(const sf::FloatRect& rect_1, const sf::FloatRect& rect_2);

protected:

	sf::Vector2f m_velocity = {0,0};
	sf::Vector2f m_gravity = {0,0};
};